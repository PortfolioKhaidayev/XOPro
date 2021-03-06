#ifndef WPAINTEVENT_H
#define WPAINTEVENT_H

#include "wevent.h"
#include "wrect.h"

class WPaintEvent : public WEvent
{
    WRect _rect;
    //WRegion _region;
public:
  WPaintEvent(WRect);
  //WPaintEvent(WRegion);
  WRect rect() const;
  void setRect(const WRect &rect);
};

#endif // WPAINTEVENT_H
