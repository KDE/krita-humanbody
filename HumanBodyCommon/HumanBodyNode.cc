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

struct HumanBodyNode::Private {
    QString id;
    QString name;
    QPointF position;
};

HumanBodyNode::HumanBodyNode(const QString& id, const QString& name ) : d(new Private)
{
    d->id = id;
    d->name = name;
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

void HumanBodyNode::paint(QPainter& gc, const KoViewConverter &converter)
{
    QRectF rect = QRectF( d->position.x() - 1, d->position.y() - 1, 2, 2);
    gc.drawEllipse( converter.documentToView( rect ) );
}
