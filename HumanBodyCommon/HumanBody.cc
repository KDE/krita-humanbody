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

#include <QMap>
#include <QPointF>

#include <klocale.h>

#include "HumanBodyLink.h"
#include "HumanBodyNode.h"

struct HumanBody::Private {
    QMap<QString, HumanBodyNode*> nodes;
    QMap<QString, HumanBodyLink*> links;
};

HumanBody::HumanBody() : d(new Private)
{
    // Create human nodes
    createNode("head", i18n("Head"), QPointF( 0, 0 ) );
    createNode("neck", i18n("Neck"), QPointF( 0, 10 ) );
    createNode("leftShoulder", i18n("Left shoulder"), QPointF( 10, 10 ) );
    createNode("leftElbow", i18n("Left elbow"), QPointF(10, 20 ) );
    createNode("leftWrist", i18n("Left wrist"), QPointF(10,30) ); 
    createNode("leftHand", i18n("Left hand"), QPointF(11,30) ); 
    createNode("rightShoulder", i18n("Right shoulder"), QPointF( -10, 10 ) );
    createNode("rightElbow", i18n("Right elbow"), QPointF(-10, 20 ) );
    createNode("rightWrist", i18n("Right wrist"), QPointF(-10,30) ); 
    createNode("rightHand", i18n("Right hand"), QPointF(-11,30) ); 
    createNode("pelvis", i18n("Pelvis"), QPointF(0,30) );
    createNode("leftCheek", i18n("Left cheek"), QPointF(10,30) );
    createNode("leftKnee", i18n("Left knee"), QPointF(10,40) );
    createNode("leftAnkle", i18n("Left ankle"), QPointF(10,50) );
    createNode("leftFoot", i18n("Left foot"), QPointF(11,50) );
    createNode("rightCheek", i18n("Right cheek"), QPointF(-10,30) );
    createNode("rightKnee", i18n("Right knee"), QPointF(-10,40) );
    createNode("rightAnkle", i18n("Right ankle"), QPointF(-10,50) );
    createNode("rightFoot", i18n("Right foot"), QPointF(-11,50) );

    // Create human links (muscles and so)
    createLink("neck", i18n("Neck"), "neck", "head");
    createLink("leftShoulder", i18n("Left shoulder"), "leftShoulder", "neck");
    createLink("leftForeArm", i18n("Left forearm"), "leftShoulder", "leftElbow");
    createLink("leftArm", i18n("Left arm"), "leftElbow", "leftWrist");
    createLink("rightShoulder", i18n("Right shoulder"), "rightShoulder", "neck");
    createLink("rightForeArm", i18n("Right forearm"), "rightShoulder", "rightElbow");
    createLink("rightArm", i18n("Right arm"), "rightElbow", "rightWrist");
    
    createLink("trunk", i18n("Trunk"), "neck", "pelvis");
    createLink("pelvisToLeftCheck", i18n("Pelvis"), "leftCheek", "pelvis");
    createLink("leftThigh", i18n("Left thigh"), "leftKnee", "leftCheek");
    createLink("leftLeg", i18n("Left leg"), "leftKnee", "leftAnkle");
    createLink("pelvisToRightCheck", i18n("Pelvis"), "rightCheek", "pelvis");
    createLink("rightThigh", i18n("Right thigh"), "rightKnee", "rightCheek");
    createLink("rightLeg", i18n("Right leg"), "rightKnee", "rightAnkle");
    createLink("leftCheeckToRightCheck", i18n("Pelvis"), "rightCheek", "leftCheek");
    
    translate( QPointF(50,50));
}

void HumanBody::createNode( const QString& id, const QString& name, const QPointF& pos)
{
    HumanBodyNode* node = new HumanBodyNode(id, name);
    node->setPosition( pos );
    d->nodes[ node->id() ] = node;
}

void HumanBody::createLink( const QString& id, const QString& name, const QString& nodeId1, const QString& nodeId2)
{
    HumanBodyLink* link = new HumanBodyLink(id, name, d->nodes[nodeId1], d->nodes[nodeId2]);
    d->links[ link->id() ] = link;
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
        node->paint(painter, converter);
    }
    foreach( HumanBodyLink* link, d->links.values())
    {
        link->paint(painter, converter);
    }
}

HumanBody::~HumanBody()
{
    delete d;
}

