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

#include "HumanBodyHead.h"

#include <QPainter>

#include <KoViewConverter.h>

#include "HumanBody.h"
#include "HumanBodyParameters.h"

struct HumanBodyHead::Private
{
    
};

HumanBodyHead::HumanBodyHead(const QString& _id, const QString& _name, HumanBody* _parent ) : HumanBodyNode(_id, _name, _parent), d(new Private)
{
    
}

HumanBodyHead::~HumanBodyHead()
{
    delete d;
}

void HumanBodyHead::paint(QPainter& _painter, const KoViewConverter &_converter)
{
    HumanBodyNode::paint(_painter, _converter);
    int headSize = humanBody()->parameters()->headSize();
    double proportion = humanBody()->parameters()->headProportion();
    QRectF rect = QRectF( position().x() - 0.8 * headSize * 0.5, position().y() - headSize * 0.5, headSize * 0.8, headSize);
    _painter.drawEllipse( _converter.documentToView( rect ) );
}

