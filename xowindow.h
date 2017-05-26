#ifndef XOWINDOW_H
#define XOWINDOW_H

#include <WWidget>

class XOWindow : public WWidget
{
private:

public:
  XOWindow(WWidget *parent = nullptr);
  ~XOWindow();

  void initUi();

  bool paintEvent(WPaintEvent *e) override;
};

#endif // XOWINDOW_H
