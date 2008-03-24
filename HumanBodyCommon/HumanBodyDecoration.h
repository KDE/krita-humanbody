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

#ifndef _HUMAN_BODY_DECORATOR_H_
#define _HUMAN_BODY_DECORATOR_H_

#include "kis_canvas_decoration.h"
#include "KritaHumanBodyCommon_export.h"

class HumanBody;

class KRITAHUMANBODYCOMMON_EXPORT HumanBodyDecoration : public KisCanvasDecoration {
    public:
        HumanBodyDecoration(KisView2 * parent);
        ~HumanBodyDecoration();
        HumanBody* humanBody();
        /**
         * Set a new human body and takes the ownership of the pointer.s
         */
        void setHumanBody( HumanBody* hb);
    protected:
        virtual void drawDecoration(QPainter& gc, const QRect& area, const KoViewConverter &converter);
    private:
        struct Private;
        Private* const d;
};

#endif
