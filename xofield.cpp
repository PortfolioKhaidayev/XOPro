#include "xofield.h"

#include <wpainter.h>

XOField::XOField(WWidget *parent)
  : WWidget(parent)
{
  this->initWndClass(L"WWIDGET");
}

int XOField::style()
{
  return WS_CHILD | WS_BORDER;
}

bool XOField::mouseReleaseEvent(WMouseEvent *e)
{
  // e->x() | e->y
  return false;
}

bool XOField::paintEvent(WPaintEvent *e)
{
  WPainter p(this);
  p.begin();
  p.drawLine( e->rect().left(), e->rect().top(), e->rect().right(), e->rect().bottom() );
  p.end();
  return false;
}
