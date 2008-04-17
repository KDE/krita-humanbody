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

#include "HumanBodyParameters.h"

struct HumanBodyParameters::Private {
    int referenceSize;
};

HumanBodyParameters::HumanBodyParameters() : d(new Private)
{
    d->referenceSize = 12;
}

HumanBodyParameters::~HumanBodyParameters()
{
    delete d;
}

int HumanBodyParameters::referenceSize() const
{
    return d->referenceSize;
}

int HumanBodyParameters::headSize() const
{
    return d->referenceSize;
}

double HumanBodyParameters::headProportion() const
{
    return 0.8;
}

int HumanBodyParameters::articulationSize() const
{
    return 4;
}

double HumanBodyParameters::armProportion() const
{
  return 1.0;
}

double HumanBodyParameters::thighProportion() const
{
  return 2.0;
}

double HumanBodyParameters::legProportion() const
{
  return 1.5;
}
