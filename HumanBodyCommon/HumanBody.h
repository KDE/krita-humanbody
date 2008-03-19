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

#ifndef _HUMAN_BODY_H_
#define _HUMAN_BODY_H_

class QString;
class QPointF;
class QPainter;
class HumanBodyNode;
class KoViewConverter;

class HumanBody {
    public:
        HumanBody();
        ~HumanBody();
    public:
        
        void translate( const QPointF& translate);
        void paint(QPainter& painter, const KoViewConverter &converter);
    private:
        void createNode( const QString& id, const QString& name, const QPointF& pos);
        void createLink( const QString& id, const QString& name, const QString& nodeId1, const QString& nodeId2);
    private:
        struct Private;
        Private* const d;
};

#endif
