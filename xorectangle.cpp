#include "xorectangle.h"

XORectangle::XORectangle()
  : XOShape()
{
}

XORectangle::XORectangle(WObject parent)
  : XOShape( parent )
{
}

XORectangle::XORectangle(WPoint pivotPoint, WSize size, WPivotPointPosition pivotPointType)
  : XOShape( pivotPoint, size)
{
}

void XORectangle::draw(HDC hdc)
{
  Rectangle(hdc, _leftTopVertex.x(), _leftTopVertex.y(), _rightBotVertex.x(), _rightBotVertex.y());
}


