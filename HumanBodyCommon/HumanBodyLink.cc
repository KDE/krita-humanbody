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

#include "HumanBodyLink.h"

#include <QPainter>

#include <KoViewConverter.h>

#include "HumanBodyNode.h"

struct HumanBodyLink::Private {
    HumanBodyNode* node1;
    HumanBodyNode* node2;
    QString id;
    QString name;
};

HumanBodyLink::HumanBodyLink( const QString& id, const QString& name, HumanBodyNode* node1, HumanBodyNode* node2 ) : d(new Private)
{
    d->node1 = node1;
    d->node2 = node2;
    d->id = id;
    d->name = name;
}

HumanBodyLink::~HumanBodyLink()
{
    delete d;
}

const QString& HumanBodyLink::id() const
{
    return d->id;
}

void HumanBodyLink::paint(QPainter& painter, const KoViewConverter &converter)
{
    painter.drawLine( converter.documentToView( d->node1->position() ), converter.documentToView( d->node2->position() ) );
}
