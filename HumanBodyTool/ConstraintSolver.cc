/*
 * Copyright (c) 2008 Cyrille Berger <cberger@cberger.net>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation; version 2 of the License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include "ConstraintSolver.h"

#include <kdebug.h>

#include "HumanBody.h"
#include "HumanBodyLink.h"
#include "HumanBodyNode.h"
#include "HumanBodyPelvis.h"
#include "Utils.h"

#include <QMap>
#include <QPointF>

struct ConstraintSolver::Private {
    bool constraintLength;
};

ConstraintSolver::ConstraintSolver() : d(new Private)
{
    d->constraintLength = true;
}

ConstraintSolver::~ConstraintSolver()
{
    delete d;
}

void ConstraintSolver::setConstraintLength(bool v)
{
    d->constraintLength = v;
}

QPointF ConstraintSolver::findBestNewPosition( const QPointF& posN1, const QPointF& posN2, double l)
{
    double x1 = posN1.x();
    double y1 = posN1.y();
    // In order to respect the constraint, the new position of n2 is on a circle
    // center on n1 (x1,y1) and of radius l
    // We choose as the new position (x,y) of n2, the closest point on that circle to the
    // old position (x2,y2)
    // It's the step of the line between n2 and the new position of n1
    if( posN2.x() == x1 ) x1 += 1e-3;
    double a = ( posN2.y() - y1 ) / (posN2.x() - x1);
    // Given u = x - x1
    double u = sqrt(l * l / ( a * a + 1));
    // y = a * u + y1
    QPointF sol1( u + x1, a * u + y1);
    u = -u;
    QPointF sol2( u + x1, a * u + y1);
    return norm2( sol1 - posN2) < norm2( sol2 - posN2 ) ? sol1 : sol2;
}

void ConstraintSolver::moveNodeTo(HumanBody* _body, HumanBodyNode* _node, const QPointF& _point)
{
    kDebug() << "ConstraintSolver::moveNodeTo : start";
    QMap< HumanBodyNode*, QPointF> newPosition_;
    newPosition_[ _node ] = _point;
    
    if(d->constraintLength)
    {
        QList<HumanBodyNode*> waitingList;
        waitingList.push_back(_node);
        bool pelvisDone = false;
        HumanBodyPelvis* pelvis_ = _body->pelvis();
        // Solve the constraint in position
        while( not waitingList.isEmpty())
        {
            HumanBodyNode* n1 = waitingList.takeFirst ();
            const QPointF& posN1 = newPosition_[ n1 ];
            QList<HumanBodyLink*> links = _body->linksForNode( n1 );
            foreach( HumanBodyLink* link, links)
            {
                HumanBodyNode* n2 = link->node1() == n1 ? link->node2() : link->node1();
                if( pelvis_->contains( n2 ) and pelvis_->contains( n1 ) )
                {
                    if( not newPosition_.contains(n2) and not pelvisDone )
                    {
                        HumanBodyNode* pelvisTop = pelvis_->pelvisTop();
                        HumanBodyNode* n3 = 0;
                        if( n1 != pelvisTop and n2 != pelvisTop )
                        { // The pelvis get a higher priority than the other two nodes and need to be either n1 or n2
                            n3 = n2;
                            n2 = pelvisTop;
                        } else {
                            n3 = ( n1 == pelvis_->leftCheek() or n2 == pelvis_->leftCheek()) ? pelvis_->rightCheek() : pelvis_->leftCheek();
                        }
                        Q_ASSERT( n1 != n3);
                        Q_ASSERT( n2 != n3);
                        Q_ASSERT( n1 != n2);
                        Q_ASSERT( pelvis_->contains( n1 ) );
                        Q_ASSERT( pelvis_->contains( n2 ) );
                        Q_ASSERT( pelvis_->contains( n3 ) );
                        Q_ASSERT( n1 == pelvisTop or n2 == pelvisTop);
                        QPointF posN2 = findBestNewPosition( posN1, n2->position(), norm2( n1->position() - n2->position() ) );
                        newPosition_[ n2 ] = posN2;
                        waitingList.push_back( n2 );
                        // n3 must be moved to the intersection of a circle center on n1 and one n2 (well to the
                        // closest interesection
                        // The equations for circle intersection are detailed in 'CircleIntersection.kalculus'
                        // Don't try to understand the code here, it's a copy paste of the output of a solve call
                        double tx = posN1.x() - posN2.x();
                        double ty = posN1.y() - posN2.y();
                        double l1 = norm2( n1->position() - n3->position() ) ;
                        double l2 = norm2( n2->position() - n3->position() ) ;
                        QPointF sol1, sol2;
                        // First solution
                        {
                            double u = ( (  - ( pow(l2, 2) - ( pow(l1, 2) + pow(tx, 2) + pow(ty, 2)) )  * 2 * tx)  / pow(2 * ty, 2) - ( 2 * tx * ( pow(l2, 2) - ( pow(l1, 2) + pow(tx, 2) + pow(ty, 2)) ) )  / pow(2 * ty, 2) + sqrt(pow(( 2 * tx * ( pow(l2, 2) - ( pow(l1, 2) + pow(tx, 2) + pow(ty, 2)) ) )  / pow(2 * ty, 2) - (  - ( pow(l2, 2) - ( pow(l1, 2) + pow(tx, 2) + pow(ty, 2)) )  * 2 * tx)  / pow(2 * ty, 2), 2) - -4 * ( pow(2 * tx, 2) / pow(2 * ty, 2) + 1)  * ( pow(l1, 2) - pow(pow(l2, 2) - ( pow(l1, 2) + pow(tx, 2) + pow(ty, 2)) , 2) / pow(2 * ty, 2)) ))  / ( -2 * ( pow(2 * tx, 2) / pow(2 * ty, 2) + 1) );
                            sol1 = QPointF( u + posN1.x(), ( pow(l2, 2) - ( pow(l1, 2) + 2 * tx * u + pow(tx, 2) + pow(ty, 2)) )  / ( 2 * ty) + posN1.y());
                            kDebug() << u;
                        }
                        // Second solution
                        {
                            double u = ( (  - ( pow(l2, 2) - ( pow(l1, 2) + pow(tx, 2) + pow(ty, 2)) )  * 2 * tx)  / pow(2 * ty, 2) - ( 2 * tx * ( pow(l2, 2) - ( pow(l1, 2) + pow(tx, 2) + pow(ty, 2)) ) )  / pow(2 * ty, 2) - sqrt(pow(( 2 * tx * ( pow(l2, 2) - ( pow(l1, 2) + pow(tx, 2) + pow(ty, 2)) ) )  / pow(2 * ty, 2) - (  - ( pow(l2, 2) - ( pow(l1, 2) + pow(tx, 2) + pow(ty, 2)) )  * 2 * tx)  / pow(2 * ty, 2), 2) - -4 * ( pow(2 * tx, 2) / pow(2 * ty, 2) + 1)  * ( pow(l1, 2) - pow(pow(l2, 2) - ( pow(l1, 2) + pow(tx, 2) + pow(ty, 2)) , 2) / pow(2 * ty, 2)) ))  / ( -2 * ( pow(2 * tx, 2) / pow(2 * ty, 2) + 1) );
                            sol2 = QPointF( u + posN1.x(), ( pow(l2, 2) - ( pow(l1, 2) + 2 * tx * u + pow(tx, 2) + pow(ty, 2)) )  / ( 2 * ty) + posN1.y());
                            kDebug() << u;
                        }
                        QPointF posN3 = n3->position();
                        newPosition_[ n3 ] = norm2( sol1 - posN3) < norm2( sol2 - posN3 ) ? sol1 : sol2;
                        waitingList.push_back( n3 );
                        pelvisDone = true;
                    }
                } else if( n2 != _node and not newPosition_.contains(n2) ) // Never try to solve constraints by moving the node that got edited and never try to compute a new position for a node we allready have move
                {
                    waitingList.push_back(n2);
                    newPosition_[ n2 ] = findBestNewPosition( posN1, n2->position(), link->length() );
                }
            }
        }
    }
    // Now record the position
    foreach( HumanBodyNode* node, newPosition_.keys() )
    {
        node->setPosition( newPosition_[node] );
    }
    kDebug() << "ConstraintSolver::moveNodeTo : done";
}
