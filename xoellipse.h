#ifndef XOELLIPSE_H
#define XOELLIPSE_H

#include "xoshape.h"

class XOEllipse : public XOShape
{
public:
  XOEllipse();
  XOEllipse(WObject parent = nullptr);
  XOEllipse(WPoint pivotPoint, WSize size, WPivotPointPosition pivotPointType = WPivotPointPosition::Center);

  void setGiometry(WPoint pivotPonit, int horisontalRadius, int verticalRadius);
  void setGiometry(WPoint pivotPonit, int radius);

  virtual void draw(HDC hdc) override;
};

#endif // XOELIPCE_H
