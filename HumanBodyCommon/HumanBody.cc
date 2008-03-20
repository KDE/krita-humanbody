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

#include "HumanBody.h"

#include <math.h>

#include <QMap>
#include <QPainter>
#include <QPointF>

#include <klocale.h>

#include "HumanBodyHead.h"
#include "HumanBodyLink.h"
#include "HumanBodyMuscle.h"
#include "HumanBodyNode.h"
#include "HumanBodyParameters.h"

#include "Utils.h"

struct HumanBody::Private {
    QMap<QString, HumanBodyNode*> nodes;
    QMap<QString, HumanBodyLink*> links;
    HumanBodyParameters parameters;
};

template< class _T_  >
void HumanBody::createNode( const QString& id, const QString& name, const QPointF& pos)
{
    _T_ * node = new _T_ (id, name, this);
    node->setPosition( pos );
    d->nodes[ node->id() ] = node;
}

template< class _T_  >
void HumanBody::createLink( const QString& id, const QString& name, const QString& nodeId1, const QString& nodeId2)
{
    _T_* link = new _T_(id, name, d->nodes[nodeId1], d->nodes[nodeId2]);
    d->links[ link->id() ] = link;
}

HumanBody::HumanBody() : d(new Private)
{
    // Create human nodes
    createNode<HumanBodyHead>("head", i18n("Head"), QPointF( 0, d->parameters.referenceSize() /4 ) );
    createNode<HumanBodyNode>("neck", i18n("Neck"), QPointF( 0, d->parameters.referenceSize() ) );
    createNode<HumanBodyNode>("leftShoulder", i18n("Left shoulder"),
                              QPointF( d->parameters.referenceSize(), d->parameters.referenceSize() ) );
    createNode<HumanBodyNode>("leftElbow", i18n("Left elbow"),
                              QPointF( d->parameters.referenceSize(), 2.5 * d->parameters.referenceSize() ) );
    createNode<HumanBodyNode>("leftWrist", i18n("Left wrist"),
                              QPointF( d->parameters.referenceSize(), 4 * d->parameters.referenceSize()) ); 
    createNode<HumanBodyNode>("leftHand", i18n("Left hand"),
                              QPointF( d->parameters.referenceSize() + 1, 4 * d->parameters.referenceSize()) ); 
    createNode<HumanBodyNode>("rightShoulder", i18n("Right shoulder"),
                              QPointF( -10, d->parameters.referenceSize() ) );
    createNode<HumanBodyNode>("rightElbow", i18n("Right elbow"),
                              QPointF(-d->parameters.referenceSize(), 2.5 * d->parameters.referenceSize() ) );
    createNode<HumanBodyNode>("rightWrist", i18n("Right wrist"),
                              QPointF(-d->parameters.referenceSize(), 4 * d->parameters.referenceSize() ) ); 
    createNode<HumanBodyNode>("rightHand", i18n("Right hand"),
                              QPointF(-d->parameters.referenceSize() - 1, 4 * d->parameters.referenceSize() ) ); 
    
    createNode<HumanBodyNode>("pelvis", i18n("Pelvis"),
                              QPointF(0, 3 * d->parameters.referenceSize() ) );
    createNode<HumanBodyNode>("leftCheek", i18n("Left cheek"),
                              QPointF( d->parameters.headProportion() * d->parameters.referenceSize(), 4 * d->parameters.referenceSize() ) );
    createNode<HumanBodyNode>("leftKnee", i18n("Left knee"),
                              QPointF( d->parameters.headProportion() * d->parameters.referenceSize(), 6 * d->parameters.referenceSize() ) );
    createNode<HumanBodyNode>("leftAnkle", i18n("Left ankle"),
                              QPointF( d->parameters.headProportion() * d->parameters.referenceSize(), 8 * d->parameters.referenceSize() ) );
    createNode<HumanBodyNode>("leftFoot", i18n("Left foot"),
                              QPointF( d->parameters.headProportion() * d->parameters.referenceSize() + 1, 8 * d->parameters.referenceSize() ) );
    createNode<HumanBodyNode>("rightCheek", i18n("Right cheek"),
                              QPointF(-d->parameters.headProportion() * d->parameters.referenceSize(), 4 * d->parameters.referenceSize() ) );
    createNode<HumanBodyNode>("rightKnee", i18n("Right knee"),
                              QPointF(-d->parameters.headProportion() * d->parameters.referenceSize(), 6 * d->parameters.referenceSize() ) );
    createNode<HumanBodyNode>("rightAnkle", i18n("Right ankle"),
                              QPointF(-d->parameters.headProportion() * d->parameters.referenceSize(), 8 * d->parameters.referenceSize() ) );
    createNode<HumanBodyNode>("rightFoot", i18n("Right foot"),
                              QPointF(-d->parameters.headProportion() * d->parameters.referenceSize() - 1, 8 * d->parameters.referenceSize() ) );

    // Create human links (muscles and so)
    createLink<HumanBodyLink>("neck", i18n("Neck"), "neck", "head");
    createLink<HumanBodyLink>("leftShoulder", i18n("Left shoulder"), "leftShoulder", "neck");
    createLink<HumanBodyMuscle>("leftForeArm", i18n("Left forearm"), "leftShoulder", "leftElbow");
    createLink<HumanBodyMuscle>("leftArm", i18n("Left arm"), "leftElbow", "leftWrist");
    createLink<HumanBodyLink>("rightShoulder", i18n("Right shoulder"), "rightShoulder", "neck");
    createLink<HumanBodyMuscle>("rightForeArm", i18n("Right forearm"), "rightShoulder", "rightElbow");
    createLink<HumanBodyMuscle>("rightArm", i18n("Right arm"), "rightElbow", "rightWrist");
    
    createLink<HumanBodyLink>("trunk", i18n("Trunk"), "neck", "pelvis");
    createLink<HumanBodyLink>("pelvisToLeftCheck", i18n("Pelvis"), "leftCheek", "pelvis");
    createLink<HumanBodyMuscle>("leftThigh", i18n("Left thigh"), "leftKnee", "leftCheek");
    createLink<HumanBodyMuscle>("leftLeg", i18n("Left leg"), "leftKnee", "leftAnkle");
    createLink<HumanBodyLink>("pelvisToRightCheck", i18n("Pelvis"), "rightCheek", "pelvis");
    createLink<HumanBodyMuscle>("rightThigh", i18n("Right thigh"), "rightKnee", "rightCheek");
    createLink<HumanBodyMuscle>("rightLeg", i18n("Right leg"), "rightKnee", "rightAnkle");
    createLink<HumanBodyLink>("leftCheeckToRightCheck", i18n("Pelvis"), "rightCheek", "leftCheek");
    
    translate( QPointF(50,50));
}

void HumanBody::translate( const QPointF& translate)
{
    foreach( HumanBodyNode* node, d->nodes.values())
    {
        node->setPosition( node->position() + translate );
    }
}

void HumanBody::paint(QPainter& painter, const KoViewConverter &converter)
{
    foreach( HumanBodyNode* node, d->nodes.values())
    {
        painter.save();
        node->paint(painter, converter);
        painter.restore();
    }
    foreach( HumanBodyLink* link, d->links.values())
    {
        painter.save();
        link->paint(painter, converter);
        painter.restore();
    }
}

HumanBodyNode* HumanBody::nodeAt( const QPointF& point )
{
    foreach( HumanBodyNode* node, d->nodes.values())
    {
        QPointF pos = node->position();
        if( norm2(point - pos) < 2 )
        {
            return node;
        }
    }
    return 0;
}

HumanBody::~HumanBody()
{
    delete d;
}

HumanBodyParameters* HumanBody::parameters()
{
    return &d->parameters;
}
