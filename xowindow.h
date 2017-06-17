#ifndef XOWINDOW_H
#define XOWINDOW_H

#include <WWidget>

#include <vector>

#include <WLabel>

class XOWindow : public WWidget
{
private:
  std::vector<WWidget> _ui;
public:
  XOWindow(WWidget *parent = nullptr);
  ~XOWindow();


  void initUi();

  void hideUi();
  void showUi();

  bool paintEvent(WPaintEvent *e) override;
  std::vector<WWidget> ui() const;
  void setUi(const std::vector<WWidget> &ui);
};

#endif // XOWINDOW_H
