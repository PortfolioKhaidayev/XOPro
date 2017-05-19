#include "wellipse.h"

WEllipse::WEllipse(WPoint pivotPoint, WSize size, WPivotPointPosition pivotPointType)
  : WShape( pivotPoint, size, pivotPointType )
{
}

WEllipse::WEllipse(WPoint pivotPonit, int horisontalRadius, int verticalRadius)
  : WShape( pivotPonit, WSize(horisontalRadius*2, verticalRadius*2))
{

}

WEllipse::WEllipse(WPoint pivotPonit, int radius)
  : WShape( pivotPonit, WSize(radius*2, radius*2) )
{

}

void WEllipse::setGeometry(WPoint pivotPonit, int horisontalRadius, int verticalRadius)
{
  setGeometry( pivotPonit,
               WSize( horisontalRadius*2, verticalRadius*2),
               WPivotPointPosition::Center);
}

void WEllipse::setGeometry(WPoint pivotPonit, int radius)

{
  setGeometry( pivotPonit,
               WSize( radius*2, radius*2),
               WPivotPointPosition::Center);
}

void WEllipse::draw(HDC& hdc)
{
  Ellipse(hdc, _leftTopVertex.x(), _leftTopVertex.y(), _rightBotVertex.x(), _rightBotVertex.y());
}
