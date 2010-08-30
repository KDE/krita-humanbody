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

#include <QList>

class QString;
class QPointF;
class QPainter;

class KisCoordinatesConverter;
class KoViewConverter;

class HumanBodyLink;
class HumanBodyNode;
class HumanBodyParameters;
class HumanBodyPelvis;
class HumanBodyMuscle;

#include "KritaHumanBodyCommon_export.h"

class KRITAHUMANBODYCOMMON_EXPORT HumanBody {
    public:
        HumanBody();
        ~HumanBody();
    public:
        
        void translate( const QPointF& translate);
        void paint(QPainter& painter, const KisCoordinatesConverter* converter);
    public:
        HumanBodyNode* nodeAt( const QPointF& point );
        HumanBodyParameters* parameters();
        QList<HumanBodyLink*> linksForNode( const HumanBodyNode* );
        HumanBodyPelvis* pelvis();
    private:
        template< class _T_  >
        _T_* createNode( const QString& id, const QString& name, const QPointF& pos);
        template< class _T_  >
        _T_* createLink( const QString& id, const QString& name, const QString& nodeId1, const QString& nodeId2);
        HumanBodyMuscle* createMuscle( const QString& _id, const QString& _name, const QString& _nodeId1, const QString& _nodeId2, double _proportion1, double _proportion2);
    private:
        struct Private;
        Private* const d;
};

#endif
