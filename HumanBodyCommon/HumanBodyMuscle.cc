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

#include "HumanBodyMuscle.h"

#include <math.h>

#include <QPainter>
#include <KoViewConverter.h>

#include "HumanBody.h"
#include "HumanBodyNode.h"
#include "HumanBodyParameters.h"

#include "Utils.h"
#include <kis_coordinates_converter.h>

struct HumanBodyMuscle::Private {
  double m_proportion1;
  double m_proportion2;
};

HumanBodyMuscle::HumanBodyMuscle(const QString& id, const QString& name, HumanBodyNode* node1, HumanBodyNode* node2, HumanBody* _parent, double _proportion1, double _proportion2 ) : HumanBodyLink(id, name, node1, node2, _parent), d(new Private)
{
  d->m_proportion1 = _proportion1;
  d->m_proportion2 = _proportion2;
}

HumanBodyMuscle::~HumanBodyMuscle()
{
    delete d;
}

void HumanBodyMuscle::paint(QPainter& _painter, const KisCoordinatesConverter* _converter)
{
    QPointF p1 = node1()->position();
    QPointF p2 = node2()->position();
    _painter.translate( _converter->documentToWidget( p1 ) );
    _painter.rotate( angle(p1, p2) * 180 / M_PI );
    double proportion1 = d->m_proportion1 * 0.5;
    double proportion2 = d->m_proportion2 * 0.5;
    QPolygonF polygon;
    double muscleSize = norm2(p2-p1) - humanBody()->parameters()->articulationSize() * 0.25;
    polygon.push_back( _converter->documentToWidget(
                       QPointF(   humanBody()->parameters()->articulationSize() * 0.25,
                                - humanBody()->parameters()->articulationSize() * proportion1 ) ) );
    polygon.push_back( _converter->documentToWidget(
                       QPointF( muscleSize, - humanBody()->parameters()->articulationSize() * proportion2 ) ) );
    polygon.push_back( _converter->documentToWidget(
                       QPointF( muscleSize,  humanBody()->parameters()->articulationSize() * proportion2 ) ) );
    polygon.push_back( _converter->documentToWidget(
                       QPointF(   humanBody()->parameters()->articulationSize() * 0.25,
                                  humanBody()->parameters()->articulationSize() * proportion1 ) ) );
    _painter.drawPolygon( polygon );
    
/*    painter.drawRect(
        converter.documentToView(
            QRectF( QPointF(
                          humanBody()->parameters()->articulationSize() * 0.25,
                        - humanBody()->parameters()->articulationSize() * proportion1),
                    QPointF(norm2(p2-p1) - humanBody()->parameters()->articulationSize() * 0.25,
                          humanBody()->parameters()->articulationSize() * proportion1) ) ) );*/
}

