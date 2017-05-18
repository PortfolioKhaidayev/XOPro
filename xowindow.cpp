#include "xowindow.h"
#include <WGui>
#include "xofield.h"

#include <iostream>

XOWindow::XOWindow(WWidget *parent)
  :WWidget(parent)
{

}

void XOWindow::initUi()
{
  auto wgt = this;
  int width  = 920;
  int height = 570;
  int x = WScreen::width()  / 2 - width  / 2;
  int y = WScreen::height() / 2 - height / 2;

  wgt->setTitle(L"XOPro");
  wgt->setGeometry(x, y, width, height);// piece


  WSpinBox* sbSize = new WSpinBox(this);
  sbSize->setGeometry(10, 10, 340, 30);
  sbSize->setMaximum(32);
  sbSize->setMinimum(3);
  sbSize->setValue(3);
  sbSize->show();

  WButtonGroup *difficultyButtons = new WButtonGroup(this);

  WRadioButton *rbtnEasy   = new WRadioButton(this);
  rbtnEasy->setGeometry(10, 40, 340, 30);
  rbtnEasy->setTitle(L"Easy");
  rbtnEasy->show();
  WRadioButton *rbtnNormal = new WRadioButton(this);
  rbtnNormal->setGeometry(10, 80, 340, 30);
  rbtnNormal->setTitle(L"Normal");
  rbtnNormal->show();
  WRadioButton *rbtnHard   = new WRadioButton(this);
  rbtnHard->setGeometry(10, 120, 340, 30);
  rbtnHard->setTitle(L"Hard");
  rbtnHard->show();

  difficultyButtons->addButton(rbtnEasy);
  difficultyButtons->addButton(rbtnNormal);
  difficultyButtons->addButton(rbtnHard);

  WPushButton* btnStart = new WPushButton(this);
  btnStart->setGeometry(10, 160, 340, 30);
  btnStart->setTitle(L"Start");
  btnStart->show();
  WPushButton* btnExit  = new WPushButton(this);
  btnExit->setGeometry(10, 200, 340, 30);
  btnExit->setTitle(L"Exit");
  btnExit->show();

  XOField *fld = new XOField(this);
  fld->setGeometry( 350, 10, 300, 300);
  fld->show();

  /// game`s main menu
  ///   Size: [___]
  ///   ( )Easy ( )Normal ( )Hard
  ///   [Start]
  ///   [Exit]

  // [x|0|0]
  // [0|x|x]
  // [x|0|x]
  // [ReStart]
}
