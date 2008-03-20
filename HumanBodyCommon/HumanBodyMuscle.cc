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

#include "HumanBodyNode.h"

#include "Utils.h"

struct HumanBodyMuscle::Private {
    
};

HumanBodyMuscle::HumanBodyMuscle(const QString& id, const QString& name, HumanBodyNode* node1, HumanBodyNode* node2 ) : HumanBodyLink(id, name, node1, node2), d(new Private)
{
}

HumanBodyMuscle::~HumanBodyMuscle()
{
    delete d;
}

void HumanBodyMuscle::paint(QPainter& painter, const KoViewConverter &converter)
{
    QPointF p1 = converter.documentToView( node1()->position() );
    QPointF p2 = converter.documentToView( node2()->position() );
    painter.translate( p1 );
    painter.rotate( angle(p1, p2) * 180 / M_PI );
    painter.drawRect( QRectF( QPointF(6,-3), QPointF(norm2(p2-p1) - 6, 3) ) );
}

