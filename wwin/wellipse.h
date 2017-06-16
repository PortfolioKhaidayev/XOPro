#ifndef XOELLIPSE_H
#define XOELLIPSE_H

#include "wshape.h"

class WEllipse : public WShape
{
public:
  WEllipse();
  WEllipse(WPoint pivotPoint, WSize size, WPivotPointPosition pivotPointType = WPivotPointPosition::Center);
  WEllipse(WPoint pivotPonit, int horisontalRadius, int verticalRadius);
  WEllipse(WPoint pivotPonit, int radius);

  void setGeometry(WPoint pivotPonit, int horisontalRadius, int verticalRadius);
  void setGeometry(WPoint pivotPonit, int radius);

  void draw(HDC hdc) override;
};

#endif // XOELIPCE_H
