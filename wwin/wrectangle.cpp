#include "wrectangle.h"

WRectangle::WRectangle(WPoint pivotPoint, WSize size, WPivotPointPosition pivotPointType)
  : WShape( pivotPoint, size)
{
}

void WRectangle::draw(HDC hdc)
{
  Rectangle(hdc, _leftTopVertex.x(), _leftTopVertex.y(), _rightBotVertex.x(), _rightBotVertex.y());
}


