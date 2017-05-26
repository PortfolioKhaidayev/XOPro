#include "xowindow.h"
#include "xofield.h"
#include "wellipse.h"
#include "wrectangle.h"
#include "xogame.h"

#include <WGui>
#include <wpainter.h>


#include <iostream>


XOWindow::XOWindow(WWidget *parent)
  :WWidget(parent)
{

}

XOWindow::~XOWindow()
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

  auto *fld = new XOGame(this);
  fld->setPos( WPoint( 360, 10) );
  btnStart->on_clicked([=](WMouseEvent*,bool){
    int sz = sbSize->value();
    fld->startNewGame( sz );
  });

}

bool XOWindow::paintEvent(WPaintEvent *e)
{

  WEllipse el( WPoint( 150, 150), 150 );

  WRectangle rg(WPoint( 360, 10), WSize(300, 300), WPivotPointPosition::LeftTop );

  WPainter* painter = new WPainter( this );

  painter->begin();

//  painter->drawShape( rg );
//  painter->drawRect(360, 10, 300, 300);

  painter->end();
}
