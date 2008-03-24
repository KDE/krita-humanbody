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

struct HumanBodyMuscle::Private {
};

HumanBodyMuscle::HumanBodyMuscle(const QString& id, const QString& name, HumanBodyNode* node1, HumanBodyNode* node2, HumanBody* _parent ) : HumanBodyLink(id, name, node1, node2, _parent), d(new Private)
{
}

HumanBodyMuscle::~HumanBodyMuscle()
{
    delete d;
}

void HumanBodyMuscle::paint(QPainter& painter, const KoViewConverter &converter)
{
    QPointF p1 = node1()->position();
    QPointF p2 = node2()->position();
    painter.translate( converter.documentToView( p1 ) );
    painter.rotate( angle(p1, p2) * 180 / M_PI );
    painter.drawRect(
        converter.documentToView(
            QRectF( QPointF(
                          humanBody()->parameters()->articulationSize(),
                        - humanBody()->parameters()->articulationSize() * 0.5),
                    QPointF(norm2(p2-p1) - humanBody()->parameters()->articulationSize(),
                          humanBody()->parameters()->articulationSize() * 0.5) ) ) );
}

