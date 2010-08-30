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

#include "HumanBodyFoot.h"

#include <QPainter>

#include <kis_coordinates_converter.h>

#include "HumanBody.h"
#include "HumanBodyNode.h"
#include "HumanBodyParameters.h"
#include "Utils.h"

struct HumanBodyFoot::Private
{
};

HumanBodyFoot::HumanBodyFoot(const QString& _id, const QString& _name, HumanBodyNode* _node1, HumanBodyNode* _node2 , HumanBody* _parent ) : HumanBodyLink(_id, _name, _node1, _node2, _parent), d(new Private)
{
}

HumanBodyFoot::~HumanBodyFoot()
{
    delete d;
}

void HumanBodyFoot::paint(QPainter& _painter, const KisCoordinatesConverter* _converter)
{
    QPointF p1 = node1()->position();
    QPointF p2 = node2()->position();
    double footSize = norm2(p2 - p1) - humanBody()->parameters()->articulationSize() * 0.5;
    _painter.translate( _converter->documentToWidget( p1 ) );
    double rot = angle(p1, p2) * 180 / M_PI - 90;
    if( (rot < 180 and rot > 0) or (rot > -270 and rot < -180  ) )
    {
        _painter.rotate( rot - 180 );
        _painter.scale( 1, -1 );
    } else {
        _painter.rotate( rot );
    }
    QPolygonF polygon;
    polygon.push_back( _converter->documentToWidget(
                       QPointF( - humanBody()->parameters()->articulationSize() * 0.5,
                                  humanBody()->parameters()->articulationSize() * 0.5 ) ) );
    polygon.push_back( _converter->documentToWidget(
                       QPointF( - humanBody()->parameters()->articulationSize() * 0.5, footSize ) ) );
    polygon.push_back( _converter->documentToWidget(
                       QPointF(   0, footSize ) ) );
    polygon.push_back( _converter->documentToWidget(
                       QPointF(   humanBody()->parameters()->articulationSize() * 0.5,
                                  humanBody()->parameters()->articulationSize() * 0.5 ) ) );
    _painter.drawPolygon( polygon );
}

