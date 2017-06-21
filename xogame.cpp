#include "xogame.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include <WMessageBox>

int random(int from, int to)
{
  srand( time(NULL) % 2 );
  return from + rand() % to;
}

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
  /*
function AlphaBeta(position, alpha, beta, deph, player) : int
    if isTerminal(position) then
        return -heuristic(position)
    end
    score  = beta;
    for child from child(position, player) do
        s = -AlphaBeta(child, -score, -alpha, deph+1, -player)
        if s < score  then score  = s
        if score <= alpha then return score
    end;
    return score
end
  //*/
  char rv = this->checkVictory();
  if( rv == _aiPlayer ){
    return AiMove(10);
  }else if ( rv == _huPlayer ) {
    return AiMove(-10);
  }else if( rv == -1){
    return AiMove(0);
  }

  std::vector<AiMove> moves;

  if( depth < 1 ){
    if( moves.size() > 0 ){
      return moves[ random( 0, moves.size() )];
    }

    AiMove move;
    move._x = random( 0, _size);
    move._y = random( 0, _size);

    return move;
  }

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

  AiMove move = getBestMove(_aiPlayer, (_size > 3)
                                        ? _size
                                        : _size * _size
                            );
  this->setTile( move._x, move._y, _aiPlayer);
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

int XOGame::getMode() const
{
  return _mode;
}

void XOGame::setMode(int mode)
{
  _mode = mode;
}


int XOGame::getCountWinO() const
{
  return _countWinO;
}

void XOGame::setCountWinO(int value)
{
  _countWinO = value;
}

int XOGame::getCountWinX() const
{
  return _countWinX;
}

void XOGame::setCountWinX(int value)
{
  _countWinX = value;
}

int XOGame::getCountNotWhose() const
{
  return _countNotWhose;
}

void XOGame::setCountNotWhose(int value)
{
  _countNotWhose = value;
}

XOGame::XOGame(WWidget *main)
 : WWidget(main)
{
  _main = main;
}

void XOGame::checkGameOver()
{
  char rv = checkVictory();
  if( rv == _aiPlayer ){
    std::cout << "win: _aiPlayer"  << std::endl;
    if( _aiPlayer == X ){
      _countWinX++;
    }
    if( _aiPlayer == O ){
      _countWinO++;
    }
    std::cout << "X: " << _countWinX<< std::endl;
    std::cout << "O: " << _countWinO<< std::endl;
    std::cout << "Not: " << _countNotWhose<< std::endl;

    _lCountWinX->setTitle( L"X: " + std::to_wstring( _countWinX ) );
    _lCountWinO->setTitle( L"O: " + std::to_wstring( _countWinO ) );

    WMessageBox::information(nullptr, L"Game Over", L"You Loos =(");
    startNewGame(_size);
    return;
  }else if ( rv == _huPlayer ) {
    std::cout << "win: _huPlayer"  << std::endl;
    if( _huPlayer == X ){
      _countWinX++;
    }
    if( _huPlayer == O ){
      _countWinO++;
    }
    std::cout << "X: " << _countWinX << std::endl;
    std::cout << "O: " << _countWinO << std::endl;
    std::cout << "Not: " << _countNotWhose << std::endl;

    _lCountWinX->setTitle( L"X: " + std::to_wstring( _countWinX ) );
    _lCountWinO->setTitle( L"O: " + std::to_wstring( _countWinO ) );

    WMessageBox::information(nullptr, L"Win", L"You Winner ;)");
    startNewGame(_size);
    return;
  }else if( rv == -1){
    std::cout << "win: _"  << std::endl;
    _countNotWhose++;

    std::cout << "X: " << _countWinX << std::endl;
    std::cout << "O: " << _countWinO << std::endl;
    std::cout << "Not: " << _countNotWhose << std::endl;

    _lCountNotWhose->setTitle( L"Not Whose: " + std::to_wstring( _countNotWhose ) );
    _lCountNotWhose->show();
    WMessageBox::information(nullptr, L"Game Over", L"Tie, you can better...");
    startNewGame(_size);
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

  delete _lCountNotWhose;
  delete _lCountWinO;
  delete _lCountWinX;

  XOGame::countFigure = 0;
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
        _currentFigure = _huPlayer;

        if( ( countFigure % 2 ) == 0){
          _currentFigure = _huPlayer;
        } else {
          _currentFigure = _aiPlayer;
        }

        this->setTile(i, j, _currentFigure);

        std::cout << "win: " << rv << std::endl;
        for(int i = 0; i < _size; i++){
          for(int j = 0; j < _size; j++){
            std::cout << "[" << _map[i][j].symbol << "]";
          }
          std::cout << std::endl;
        }
        if( this->_mode == GameMode::OnePalyer ){
          this->run_minimax();
          countFigure++;
        }
        countFigure++;
        checkGameOver();
      });
      _map[i][j].btn->setGeometry(i*_tileSize + _pos.x(), j*_tileSize + _pos.y(), _tileSize,_tileSize);
      _map[i][j].btn->show();
      _map[i][j].symbol = ' ';
    }
  }


  _lCountWinX = new WLabel(_main);
  _lCountWinX->setGeometry( this->geometry().topRight().x(), this->geometry().top(), 64, 30 );
  _lCountWinX->setTitle( L"X: " + std::to_wstring( _countWinX ) );
  std::cout <<  "[createMap()]::_contWinX: " << _countWinX << std::endl;
//  _lCountWinX->show();

  _lCountWinO = new WLabel(_main);
  _lCountWinO->setGeometry( this->geometry().topRight().x(), _lCountWinX->geometry().bottom() + 10, 64, 30 );
  _lCountWinO->setTitle( L"O: " + std::to_wstring( _countWinO ) );
  std::cout <<  "[createMap()]::_contWinO: " << _countWinO << std::endl;
//  _lCountWinO->show();

  _lCountNotWhose = new WLabel(_main);
  _lCountNotWhose->setGeometry( this->geometry().topRight().x(), _lCountWinO->geometry().bottom() + 10, 128, 30 );
  _lCountNotWhose->setTitle( L"Not Whose: " + std::to_wstring( _countNotWhose ) );
  std::cout <<  "[createMap()]::_countNotWhose: " << _countNotWhose << std::endl;
  //  _lCountNotWhose->show();
}

