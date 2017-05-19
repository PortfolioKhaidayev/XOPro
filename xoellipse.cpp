#include "xoellipse.h"

XOEllipse::XOEllipse()
  : XOShape()
{

}

XOEllipse::XOEllipse(WObject parent)
  : XOShape( parent )
{

}

XOEllipse::XOEllipse(WPoint pivotPoint, WSize size, WPivotPointPosition pivotPointType)
  : XOShape( pivotPoint, size, pivotPointType )
{
}

void XOEllipse::setGiometry(WPoint pivotPonit, int horisontalRadius, int verticalRadius)
  : XOShape::setGiometry(pivotPonit,
                         WSize( horisontalRadius*2, verticalRadius*2),
                         WPivotPointPosition::Center)
{
}

void XOEllipse::setGiometry(WPoint pivotPonit, int radius)
  : XOShape::setGiometry(pivotPonit,
                         WSize( radius*2, radius*2),
                         WPivotPointPosition::Center)
{
}

void XOEllipse::draw(HDC hdc)
{
  Ellipse(hdc, _leftTopVertex.x, _leftTopVertex.y, _rightBotVertex.x, _rightBotVertex.y);
}
