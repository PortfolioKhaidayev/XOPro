#include "xowindow.h"
#include "xogame.h"

#include <WGui>
#include <iostream>

/// \bref
std::vector<WWidget> XOWindow::ui() const
{
  return _ui;
}

void XOWindow::setUi(const std::vector<WWidget> &ui)
{
  _ui = ui;
}

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
  int width  = 400;
  int height = 570;
  int x = WScreen::width()  / 2 - width  / 2;
  int y = WScreen::height() / 2 - height / 2;

  wgt->setTitle(L"XOPro");
  wgt->setGeometry(x, y, width, height);// piece

  WSpinBox* sbSize = new WSpinBox(this);
  sbSize->setGeometry( 10, 10, 340, 30);
  sbSize->setMaximum(10);
  sbSize->setMinimum(3);
  sbSize->setValue(3);
  sbSize->show();


  WPushButton* btnStart = new WPushButton(this);
  btnStart->setGeometry(10, 160, 340, 30);
  btnStart->setTitle(L"Start");
  btnStart->show();
  WPushButton* btnExit  = new WPushButton(this);
  btnExit->setGeometry(10, 200, 340, 30);
  btnExit->setTitle(L"Exit");
  btnExit->show();

  wgt->setGeometry(x, y,
                   btnExit->geometry().right()+30,
                   btnExit->geometry().bottom()+50
                   );

  auto *fld = new XOGame(this);


  WRadioButton* rbOnePlayer = new WRadioButton(wgt);
  rbOnePlayer->setGeometry( 10, sbSize->geometry().bottom() + 10, 150, 30 );
  rbOnePlayer->setTitle(L"One");
  rbOnePlayer->setChecked(true);
  rbOnePlayer->on_clicked( [=](WMouseEvent*,bool){
    fld->setMode(GameMode::OnePalyer);
  });
  WRadioButton* rbTwoPlayers = new WRadioButton(wgt);
  rbTwoPlayers->setGeometry( rbOnePlayer->geometry().bottomRight().x() + 10, sbSize->geometry().bottom() + 10, 150, 30 );
  rbTwoPlayers->setTitle(L"Two");
  rbTwoPlayers->setChecked(false);
  rbTwoPlayers->on_clicked( [=](WMouseEvent*,bool){
    fld->setMode(GameMode::TwoPlayers);
  });
  WButtonGroup* bgMode = new WButtonGroup(wgt);
  bgMode->addButton(rbOnePlayer);
  bgMode->addButton(rbTwoPlayers);

  WRadioButton* rbFigureX = new WRadioButton(wgt);
  rbFigureX->setGeometry( 10, rbOnePlayer->geometry().bottom() + 10, 150, 30 );
  rbFigureX->setTitle(L"X");
  rbFigureX->setChecked(true);
  rbFigureX->on_clicked( [=](WMouseEvent*,bool){
    fld->initAi( O );
  });
  WRadioButton* rbFigureO = new WRadioButton(wgt);
  rbFigureO->setGeometry( rbOnePlayer->geometry().bottomRight().x() + 10, rbOnePlayer->geometry().bottom() + 10, 150, 30 );
  rbFigureO->setTitle(L"O");
  rbFigureO->setChecked(false);
  rbFigureO->on_clicked( [=](WMouseEvent*,bool){
    fld->initAi( X );
  });

  WButtonGroup* bgFigure = new WButtonGroup(wgt);
  bgFigure->addButton(rbFigureO);
  bgFigure->addButton(rbFigureX);


  btnStart->on_clicked([=](WMouseEvent*,bool){
    int sz = sbSize->value();
    fld->startNewGame( sz );

//    fld->setPos( WPoint( width / 2 - (fld->geometry().right())/2, sbSize->geometry().bottom() + 10) );
    btnStart->setGeometry( 10, fld->geometry().bottom(), 340, 30);
    btnExit->setGeometry( 10, btnStart->geometry().bottom()+16, 340, 30);

    wgt->setGeometry(x, y,
                     btnExit->geometry().right()+30,
                     btnExit->geometry().bottom()+50
                     );
  });

  btnExit->on_clicked([=](WMouseEvent*, bool){
    wgt->exit();
  });

  fld->setPos( WPoint( 10, rbFigureX->geometry().bottom() + 10) );
//  fld->setPos( WPoint( btnExit->geometry().right() / 3, sbSize->geometry().bottom() + 10) );
  fld->startNewGame( fld->getSize() );


  btnStart->click();
  _ui.push_back( sbSize );
  _ui.push_back( btnStart );
  _ui.push_back( btnExit );
}

void XOWindow::hideUi()
{
  for(WWidget comp : _ui){
    comp.hide();
  }
}

void XOWindow::showUi()
{
  for(auto comp : _ui){
    comp.show();
  }
}

bool XOWindow::paintEvent(WPaintEvent *e)
{
  return e->isAccepted();
}

