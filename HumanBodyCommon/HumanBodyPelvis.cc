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

#include "HumanBodyPelvis.h"

#include <QPainter>

#include <KoViewConverter.h>

#include <HumanBody.h>
#include <HumanBodyNode.h>
#include <HumanBodyParameters.h>
#include "Utils.h"
#include <kis_coordinates_converter.h>

struct HumanBodyPelvis::Private
{
    HumanBodyNode* pelvisTop;
    HumanBodyNode* leftCheek;
    HumanBodyNode* rightCheek;
    HumanBody* humanBody;
};

HumanBodyPelvis::HumanBodyPelvis( HumanBody* body, HumanBodyNode* pelvisTop, HumanBodyNode* leftCheek, HumanBodyNode* rightCheek) : d(new Private)
{
    d->pelvisTop = pelvisTop;
    d->leftCheek = leftCheek;
    d->rightCheek = rightCheek;
    d->humanBody = body;
}

HumanBodyPelvis::~HumanBodyPelvis()
{
    delete d;
}

bool HumanBodyPelvis::contains( HumanBodyNode* node)
{
    return (node == d->pelvisTop or node == d->leftCheek or node == d->rightCheek);
}

HumanBodyNode* HumanBodyPelvis::pelvisTop()
{
    return d->pelvisTop;
}
HumanBodyNode* HumanBodyPelvis::leftCheek()
{
    return d->leftCheek;
}
HumanBodyNode* HumanBodyPelvis::rightCheek()
{
    return d->rightCheek;
}

void HumanBodyPelvis::paint(QPainter& painter, const KisCoordinatesConverter* converter)
{
    Q_UNUSED(painter);
    Q_UNUSED(converter);
    QPointF l2r = d->leftCheek->position() - d->rightCheek->position();
    l2r /= norm2( l2r );
    QPointF l2rAS = l2r * d->humanBody->parameters()->articulationSize();
    QPointF leftHoriPt = d->leftCheek->position() - l2rAS;
    QPointF rightHoriPt = d->rightCheek->position() + l2rAS;
    painter.drawLine( converter->documentToWidget( leftHoriPt ),
                      converter->documentToWidget( rightHoriPt ) );
#if 0
    QPointF l2r = d->leftCheek->position() - d->rightCheek->position();
    l2r /= norm2( l2r );
    QPointF l2rPerp = QPointF( -l2r.y(), -l2r.x() );
    QPointF l2rAS = l2r * d->humanBody->parameters()->articulationSize();
    QPointF l2rPerpAS = l2rPerp * d->humanBody->parameters()->articulationSize();
    QPointF leftHoriPt = d->leftCheek->position() - l2rAS;
    QPointF leftVertiPt = d->leftCheek->position() + l2rPerpAS;
    QPointF leftHoriVertiPt = d->leftCheek->position() - l2rAS + l2rPerpAS;
    QPointF rightHoriPt = d->rightCheek->position() + l2rAS;
    QPointF rightVertiPt = d->rightCheek->position() + l2rPerpAS;
    QPointF rightHoriVertiPt = d->rightCheek->position() + l2rAS + l2rPerpAS;
    painter.drawLine( converter.documentToView( leftHoriPt ),
                      converter.documentToView( rightHoriPt ) );
    { // Draw the arc around the left cheek
        QPainterPath path( converter.documentToView( leftHoriPt ) );
        path.cubicTo( converter.documentToView( leftHoriVertiPt ),
                       converter.documentToView( leftHoriVertiPt ),
                       converter.documentToView( leftVertiPt ) );
        painter.drawPath( path );
    }
    { // Draw the arc around the right cheek
        QPainterPath path( converter.documentToView( rightHoriPt ) );
        path.cubicTo( converter.documentToView( rightHoriVertiPt ),
                       converter.documentToView( rightHoriVertiPt ),
                       converter.documentToView( rightVertiPt ) );
        painter.drawPath( path );
    }
#endif
}
