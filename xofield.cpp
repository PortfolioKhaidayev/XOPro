#include "xofield.h"


#include <iostream>

XOField::XOField(WWidget *parent)
  : WWidget(parent)
{
  this->initWndClass(L"WWIDGET");
}

void XOField::startNewGame(int size)
{
  _size = size;

  if(_map){
    this->deleteMap();
  }
  this->createMap();
  this->eraseMap(' ');
}

bool XOField::setTile(int i, int j, char tile)
{
  if(tile != 'x' && tile != '0'){
    return false;
  }
  if(_map && i < _size && j < _size){
    if(_map[i][j] != ' '){
      return false;
    }
    _map[i][j] = tile;
    return true;
  }
  return false;
}

void XOField::drawGrid(WPainter& p)
{
  for (int i = 0; i < _size-1; ++i) {
      p.drawLine(i*_tileSize+_tileSize,0,i*_tileSize+_tileSize,_size*_tileSize);
      p.drawLine(0,i*_tileSize+_tileSize,_size*_tileSize,i*_tileSize+_tileSize);

  }
}

void XOField::drawTiles(WPainter& p)
{
  for (int i = 0; i < _size; ++i) {
    for (int j = 0; j < _size; ++j) {
      if( _map[i][j] == 'x' ){



        p.drawLine(i*_tileSize,j*_tileSize, i*_tileSize+_tileSize,j*_tileSize+_tileSize);
        p.drawLine(i*_tileSize+_tileSize,j*_tileSize, i*_tileSize,j*_tileSize+_tileSize);
      } else if ( _map[i][j] == '0' ) {
        p.drawElipce(i*_tileSize,j*_tileSize, _tileSize,_tileSize);
      }
    }
  }
}

void XOField::deleteMap()
{
  for (int i = 0; i < _size; ++i) {
    delete _map[i];
  }
  delete[] _map;
  _map = nullptr;
}

void XOField::createMap()
{
  _map = new char*[_size];
  for (int i = 0; i < _size; ++i) {
    _map[i] = new char[_size];
  }
}

void XOField::eraseMap(char def)
{
  for (int i = 0; i < _size; ++i) {
    for (int j = 0; j < _size; ++j) {
      _map[i][j] = def;
    }
  }
}

int XOField::style()
{
  return WS_CHILD | WS_VISIBLE | WS_BORDER | WS_CLIPCHILDREN;
}

bool XOField::mouseReleaseEvent(WMouseEvent *e)
{
  std::cout << "CLck" << std::endl;
  // BS_CLICK sended only for BUTTON !!! CERF !!! .. afk
  WRect wg = this->geometry();
  int i = (e->x() - wg.left()) / _tileSize;
  int j = (e->y() - wg.top())  / _tileSize;
  this->setTile(i,j,'x');
  return false;
}

bool XOField::paintEvent(WPaintEvent *e)
{
  if( _map ){
    WPainter p(this);
    std::cout << "WRect {" << std::endl
              << "\tLeft: " << e->rect().left() << std::endl
              << "\tTop: " << e->rect().top() << std::endl
              << "\tRight: " << e->rect().right() << std::endl
              << "\tBottom: " << e->rect().bottom() << std::endl
              << "}" << std::endl;
    p.begin();
    this->drawGrid(p);
    this->drawTiles(p);
    p.end();
  }
  return false;
}
