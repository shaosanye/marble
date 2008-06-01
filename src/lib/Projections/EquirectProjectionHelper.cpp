//
// This file is part of the Marble Desktop Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2008      Inge Wallin  <ingwa@kde.org>"
//


// Local
#include "EquirectProjectionHelper.h"
#include "AbstractProjectionHelper_p.h"

// Marble
#include "GeoPainter.h"
#include "ViewportParams.h"


EquirectProjectionHelper::EquirectProjectionHelper()
    : AbstractProjectionHelper()
{
}

EquirectProjectionHelper::~EquirectProjectionHelper()
{
}


void EquirectProjectionHelper::paintBase( GeoPainter     *painter, 
					  ViewportParams *viewport,
					  QPen           &pen,
					  QBrush         &brush,
					  bool            antialiasing )
{
    // Convenience variables
    int  radius = viewport->radius();
    int  width  = viewport->width();
    int  height = viewport->height();

    // Igor, prepare the painter!
    painter->setRenderHint( QPainter::Antialiasing, antialiasing );
    painter->setPen( pen );
    painter->setBrush( brush );

    // Calculate translation of center point
    double  centerLon;
    double  centerLat;
    viewport->centerCoordinates( centerLon, centerLat );

    int yCenterOffset = (int)(centerLat * (double)( 2 * radius ) / M_PI );
    int yTop          = height / 2 - radius + yCenterOffset;
    int yBottom       = yTop + 2 * radius;

    // Bound the values to the viewport.
    if ( yTop < 0 )
	yTop = 0;
    if ( yBottom > height )
	yBottom =  height;

    painter->drawRect( 0, yTop, width, yBottom - yTop );
}


void EquirectProjectionHelper::setActiveRegion( ViewportParams *viewport )
{
    // Convenience variables
    int  radius = viewport->radius();
    int  width  = viewport->width();
    int  height = viewport->height();

    // Calculate translation of center point
    double  centerLon;
    double  centerLat;
    viewport->centerCoordinates( centerLon, centerLat );

    int yCenterOffset = (int)( centerLat * (double)( 2 * radius ) / M_PI );
    int yTop          = height / 2 - radius + yCenterOffset;
    int yBottom       = yTop + 2 * radius;

    // Don't let the active area be outside the image, and also let a
    // thin strip 25 pixels wide be outside it.
    if ( yTop < 25 )
	yTop = 25;
    if ( yBottom > height - 25 )
	yBottom =  height - 25;

    d->activeRegion = QRegion( 25, yTop, width - 50, yBottom - yTop,
			       QRegion::Rectangle );
}
