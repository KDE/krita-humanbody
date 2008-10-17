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

#include "HumanBodyDecoration.h"

#include <klocale.h>

#include "HumanBody.h"

struct HumanBodyDecoration::Private
{
    HumanBody* humanBody;
};

HumanBodyDecoration::HumanBodyDecoration(KisView2 * parent) : KisCanvasDecoration("humanBody", i18n("Human body"),parent), d(new Private)
{
    d->humanBody = new HumanBody();
}

HumanBodyDecoration::~HumanBodyDecoration()
{
    delete d;
}

void HumanBodyDecoration::drawDecoration(QPainter& gc, const QPoint & documentOffset, const QRect& area, const KoViewConverter &converter)
{
    Q_UNUSED(area);
    d->humanBody->paint(gc, converter);
}

HumanBody* HumanBodyDecoration::humanBody()
{
    return d->humanBody;
}

void HumanBodyDecoration::setHumanBody( HumanBody* hb)
{
    delete d->humanBody;
    d->humanBody = hb;
}
