#include "xogame.h"
#include <vector>
#include <iostream>
#include <WMessageBox>

int XOGame::countFigure = 0;

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

AiMove XOGame::getBestMove(char currentPlayer, int depth)
{  
  char rv = this->checkVictory();
  if( rv == _aiPlayer ){
    return AiMove(10);
  }else if ( rv == _huPlayer ) {
    return AiMove(-10);
  }else if( rv == -1){
    return AiMove(0);
  }

  if( depth <= 0 ){
    if( rv == _aiPlayer ){
      return AiMove(10);
    }else if ( rv == _huPlayer ) {
      return AiMove(-10);
    }else if( rv == -1){
      return AiMove(0);
    }
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
          move._score = getBestMove(_huPlayer, depth--)._score;
        } else {
          move._score = getBestMove(_aiPlayer, depth--)._score;
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
  checkGameOver();

  AiMove move = getBestMove(_aiPlayer, 3);
  this->setTile( move._x, move._y, _aiPlayer);

  checkGameOver();
}

void XOGame::eraseMap()
{
  if( ! _map ) return;

  for (int i = 0; i < _size; ++i) {
    for (int j = 0; j < _size; ++j) {
      //      if(def == ' ' || def == 'O' || def == 'X'){
      _map[i][j].btn->setTitle(L" ");
      _map[i][j].symbol = _;
      //      }
    }
  }
}

int XOGame::getCountFigure()
{
  return countFigure;
}

int XOGame::incrementCountFigure()
{
  return countFigure++;
}

void XOGame::setCountFigure(int value)
{
  countFigure = value;
}

int XOGame::getSize() const
{
  return _size;
}

XOGame::XOGame(WWidget *main)
{
  _main = main;
}

void XOGame::checkGameOver()
{
  char rv = checkVictory();
  if( rv == _aiPlayer ){
    std::cout << "win: _aiPlayer"  << std::endl;
    WMessageBox::information(nullptr, L"Game Over", L"You Loos =(");
    startNewGame(_size);
    return;
  }else if ( rv == _huPlayer ) {
    std::cout << "win: _huPlayer"  << std::endl;
    WMessageBox::information(nullptr, L"Win", L"You Winner ;)");
    startNewGame(_size);
    return;
  }else if( rv == -1){
    std::cout << "win: _"  << std::endl;
    WMessageBox::information(nullptr, L"Game Over", L"Tie, you can better...");
    return;
  }
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

WRect XOGame::geometry()
{
  if( _map ){
    return WRect( _map[0][0].btn->geometry().left(),
        _map[0][0].btn->geometry().top(),
        _map[_size - 1][_size - 1].btn->geometry().right(),
        _map[_size - 1][_size - 1].btn->geometry().bottom()
        );
  }
  return WRect( 0, 0, _tileSize*_size + _pos.x(), _tileSize*_size + _pos.y() );
}

char XOGame::checkVictory()
{
  bool victory;
  char c;

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
      if ( victory ) {
        return c;
      }
    }
  }

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
      if ( victory ) {
        return c;
      }
    }
  }

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
    if ( victory ) {
      return c;
    }
  }

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
    if ( victory ) {
      return c;
    }
  }

  for (int i = 0; i < _size; ++i) {
    for (int j = 0; j < _size; ++j) {
      if( _map[i][j].symbol == _ )
        return _;
    }
  }

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
        char rv = checkVictory();
        this->setTile(i, j, X);

        std::cout << "win: " << rv << std::endl;
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

