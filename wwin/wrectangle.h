#ifndef XORECTANGLE_H
#define XORECTANGLE_H

#include "wshape.h"

class WRectangle : public WShape
{
public:
  WRectangle(WPoint pivotPoint, WSize size, WPivotPointPosition pivotPointType = WPivotPointPosition::Center);

  virtual void draw(HDC hdc) override;
};

#endif // XORECTANGLE_H
