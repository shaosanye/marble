//
// This file is part of the Marble Virtual Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2009      Andrew Manson <g.real.ate@gmail.com>
//

#ifndef TMPGRAPHICSITEM_H
#define TMPGRAPHICSITEM_H

#include <QtCore/QRect>
#include <QtCore/QObject>
#include <QtGui/QPainterPath>
#include <QtGui/QMouseEvent>

#include "GeoGraphicsItem.h"
#include "marble_export.h"

namespace Marble
{

class GeoDataPlacemark;

class TmpGraphicsItem : public GeoGraphicsItem
{
public:
    TmpGraphicsItem( GeoDataPlacemark *placemark );
    ~TmpGraphicsItem();

    virtual void paint(GeoPainter * painter, const ViewportParams * viewport) =0;

    QList<QRegion> regions() const;

    //Start dealing with the event stuff
    //is this the best thing to call the event distributer?
    bool sceneEvent( QEvent* event );

    GeoDataPlacemark *placemark();
protected:
    void setRegions( const QList<QRegion>& regions );


    virtual bool mousePressEvent( QMouseEvent* event );
    virtual bool mouseMoveEvent( QMouseEvent* event );
    virtual bool mouseReleaseEvent( QMouseEvent* event );

 private:
    QList<QRegion> m_regions;
    GeoDataPlacemark *m_placemark;

};

}

#endif // TMPGRAPHICSITEM_H
