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
#include "Utils.h"

struct HumanBodyLink::Private {
    HumanBodyNode* node1;
    HumanBodyNode* node2;
    QString id;
    QString name;
    HumanBody* parent;
    bool visible;
};

HumanBodyLink::HumanBodyLink( const QString& id, const QString& name, HumanBodyNode* node1, HumanBodyNode* node2, HumanBody* _parent  ) : d(new Private)
{
    d->node1 = node1;
    d->node2 = node2;
    d->id = id;
    d->name = name;
    d->parent = _parent;
    d->visible = true;
}

HumanBodyLink::~HumanBodyLink()
{
    delete d;
}

const QString& HumanBodyLink::id() const
{
    return d->id;
}

void HumanBodyLink::setVisible(bool v)
{
    d->visible = v;
}

void HumanBodyLink::paint(QPainter& painter, const KoViewConverter &converter)
{
    if(d->visible)
    {
        painter.drawLine( converter.documentToView( d->node1->position() ), converter.documentToView( d->node2->position() ) );
    }
}

HumanBodyNode* HumanBodyLink::node1()
{
    return d->node1;
}
HumanBodyNode* HumanBodyLink::node2()
{
    return d->node2;
}

HumanBody* HumanBodyLink::humanBody()
{
    return d->parent;
}

double HumanBodyLink::length() const
{
    return norm2( d->node1->position() - d->node2->position() );
}
