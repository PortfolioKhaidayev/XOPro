#ifndef XOFIELD_H
#define XOFIELD_H

#include <WWidget>

class XOField : public WWidget
{
private:
  XOCell cells;/// : public XOShape
    /// x, y of center of cell in field
    /// top, left, bottom, right of this cell IN field


public:
  XOField(WWidget *parent = nullptr);

  // WWidget interface
protected:
  virtual int style() override;
  virtual bool mouseReleaseEvent(WMouseEvent *e) override;
  virtual bool paintEvent(WPaintEvent *e) override;
};

#endif // XOFIELD_H
