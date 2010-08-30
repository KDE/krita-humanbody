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

#include "HumanBodyNode.h"

#include <QString>
#include <QPainter>
#include <QPointF>

#include <KoViewConverter.h>

#include "HumanBody.h"
#include "HumanBodyParameters.h"
#include <kis_coordinates_converter.h>

struct HumanBodyNode::Private {
    QString id;
    QString name;
    QPointF position;
    HumanBody* parent;
};

HumanBodyNode::HumanBodyNode(const QString& _id, const QString& _name, HumanBody* _parent  ) : d(new Private)
{
    d->id = _id;
    d->name = _name;
    d->parent = _parent;
}

HumanBodyNode::~HumanBodyNode()
{
}

QPointF HumanBodyNode::position() const
{
    return d->position;
}
void HumanBodyNode::setPosition(const QPointF& pos)
{
    d->position = pos;
}

const QString& HumanBodyNode::id() const
{
    return d->id;
}

void HumanBodyNode::paint(QPainter& gc, const KisCoordinatesConverter* converter)
{
    int size = humanBody()->parameters()->articulationSize();
    double halfSize = size / 2.0;
    QRectF rect = QRectF( d->position.x() - halfSize, d->position.y() - halfSize, size, size);
    gc.drawEllipse( converter->documentToWidget( rect ) );
}

HumanBody* HumanBodyNode::humanBody()
{
    return d->parent;
}
