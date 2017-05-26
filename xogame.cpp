#include "xogame.h"
#include <vector>
#include <iostream>

MapItem **XOGame::map() const
{
  return _map;
}

void XOGame::initAi(char aiPlayer)
{
  _aiPlayer = aiPlayer;
  if(_aiPlayer == O)
  {
    _huPlayer = X;
  }
  else if(_aiPlayer == X){
    _huPlayer = O;
  }
}

AiMove XOGame::getBestMove(char currentPlayer)
{
  char rv = this->checkVictory();
  if( rv == _aiPlayer ){
    return AiMove(10);
  }else if ( rv == _huPlayer ) {
    return AiMove(-10);
  }else if( rv == -1){
    return AiMove(0);
  }

  std::vector<AiMove> moves;

  for (int i = 0; i < _size; ++i) {
    for (int j = 0; j < _size; ++j) {
      if( _map[i][j].symbol == _ ){
        AiMove move;
        move._x = i;
        move._y = j;
        _map[i][j].symbol = currentPlayer;
        if ( currentPlayer == _aiPlayer ) {
          move._score = getBestMove(_huPlayer)._score;
        } else {
          move._score = getBestMove(_aiPlayer)._score;
        }
        moves.push_back(move);
        _map[i][j].symbol = _;
      }
    }
  }

  int bestMove = 0;


  if ( currentPlayer == _aiPlayer ) {
    int bestScore = -1;
    bestScore <<= 15;

    for (size_t i = 0; i < moves.size(); ++i) {
      if( moves[i]._score > bestScore ){
        bestMove = i;
        bestScore = moves[i]._score;
      }
    }

  } else {
    int bestScore = 1;
    bestScore <<= 15;

    for (size_t i = 0; i < moves.size(); ++i) {
      if( moves[i]._score < bestScore ){
        bestMove = i;
        bestScore = moves[i]._score;
      }
    }
  }

  return moves.at( bestMove );
}

void XOGame::run_minimax()
{
  AiMove move = getBestMove();
  this->setTile( move._x, move._y, O);
}

void XOGame::eraseMap(char def)
{
  if( ! _map ) return;

  for (int i = 0; i < _size; ++i) {
    for (int j = 0; j < _size; ++j) {
//      if(def == ' ' || def == 'O' || def == 'X'){
        _map[i][j].btn->setTitle(L" ");
        _map[i][j].symbol = def;
//      }
    }
  }
}

XOGame::XOGame(WWidget *main)
{
  _main = main;
}

void XOGame::setPos(const WPoint &point)
{
  _pos = point;
}

void XOGame::setMainWindow(WWidget *main)
{
  _main = main;
}

void XOGame::startNewGame(int size)
{
  if(_map){
    this->deleteMap();
  }

  _size = size;

  this->createMap();
}

bool XOGame::setTile(int i, int j, char tile)
{
  if(_map[i][j].symbol == ' '){
    _map[i][j].btn->setTitle( tile == X ? L"X" : L"O" );
    _map[i][j].symbol = tile;

    return true;
  }
  return false;
}

char XOGame::checkVictory()
{
  static unsigned long long cnt = 0;
//  std::cout << "count:"  << ++cnt << std::endl;
  bool victory;
  char c;

  //*
  // rows
  for (int y = 0; y < _size; ++y) {
    c = _map[0][y].symbol;
    if( c != _ ){
      victory = true;
      for (int x = 0; x < _size; ++x) {
        if ( _map[x][y].symbol != c) {
          victory = false;
          break;
        }
      }
      if ( victory ) return c;
    }
  }
  //*/
//  std::cout << "No win rows" << std::endl;

  //*
  // columns
  for (int x = 0; x < _size; ++x) {
    c = _map[x][0].symbol;
    if ( c != _ ) {
      victory = true;
      for (int y = 0; y < _size; ++y) {
        if ( _map[x][y].symbol != c) {
          victory = false;
          break;
        }
      }
      if ( victory ) return c;
    }
  }
  //*/
//  std::cout << "No win cols" << std::endl;

  //*
  // main axis
  c = _map[0][0].symbol;
  if ( c != _ ) {
    victory = true;
    for (int xy = 0; xy < _size; ++xy) {
      if ( _map[xy][xy].symbol != c) {
        victory = false;
        break;
      }
    }
    if ( victory ) return c;
  }
  //*/
//  std::cout << "No win main" << std::endl;

  //*
  // add axis
  c = _map[_size - 1][0].symbol;
  if ( c != _ ) {
    victory = true;
    for (int xy = 0; xy < _size; ++xy) {
      if ( _map[ _size - xy - 1 ][xy].symbol != c) {
        victory = false;
        break;
      }
    }
    if ( victory ) return c;
  }
  //*/
//  std::cout << "No win addl" << std::endl;

  //*
  for (int i = 0; i < _size; ++i) {
    for (int j = 0; j < _size; ++j) {
      if( _map[i][j].symbol == _ )
        return _;
    }
  }
  //*/
//  std::cout << "No accesible turns" << std::endl;

  return -1;
}


void XOGame::deleteMap()
{
  for (int i = 0; i < _size; ++i) {
    for (int j = 0; j < _size; ++j) {
      delete _map[i][j].btn;
    }
    delete _map[i];
  }
  delete[] _map;
  _map = nullptr;
}

void XOGame::createMap()
{
  _map = new MapItem*[_size];

  for (int i = 0; i < _size; ++i) {
    _map[i] = new MapItem[_size];
  }

  for (int i = 0; i < _size; ++i) {
    for (int j = 0; j < _size; ++j) {
      _map[i][j].btn = new WPushButton(_main);
      _map[i][j].btn->on_clicked([=](WMouseEvent*,bool){
        this->setTile(i, j, X);
        for(int i = 0; i < _size; i++){
          for(int j = 0; j < _size; j++){
            std::cout << "[" << _map[i][j].symbol << "]";
          }
          std::cout << std::endl;
        }
        this->run_minimax();
      });
      _map[i][j].btn->setGeometry(i*_tileSize + _pos.x(), j*_tileSize + _pos.y(), _tileSize,_tileSize);
      _map[i][j].btn->show();
      _map[i][j].symbol = ' ';
    }
  }
}

