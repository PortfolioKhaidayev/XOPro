#ifndef XORECTANGLE_H
#define XORECTANGLE_H

#include "xoshape.h"

class XORectangle : public XOShape
{// XOElipce // XOShape
public:
  XORectangle();
  XORectangle(WObject parent = nullptr);
  XORectangle(WPoint pivotPoint, WSize size, WPivotPointPosition pivotPointType = WPivotPointPosition::Center);

  virtual void draw(HDC hdc) override;
};

#endif // XORECTANGLE_H
