#ifndef XOWINDOW_H
#define XOWINDOW_H

#include <WWidget>

class XOWindow : public WWidget
{
public:
  XOWindow(WWidget *parent = nullptr);

  void initUi();

};

#endif // XOWINDOW_H
