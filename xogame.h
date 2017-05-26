#ifndef XOGAME_H
#define XOGAME_H

#include <WPushButton>

enum PlayerType{
  X = 'X',
  O = 'O',
  _ = ' ',
};

typedef struct {
  WPushButton* btn;
  char symbol;
} MapItem;

struct AiMove{
  AiMove(){}
  AiMove( int score ): _score(score){}
  int _x = 0;
  int _y = 0;
  int _score = 0;
};

class XOGame
{
private:

  char _aiPlayer = O;
  char _huPlayer = X;

  int _size = 3;
  int _tileSize = 32;
  WPoint _pos;
  WWidget* _main;
  MapItem** _map = nullptr;

public:
  XOGame( WWidget* main = nullptr );

  void setPos(const WPoint& point);
  void setMainWindow(WWidget* main = nullptr);

  void startNewGame(int size);

  bool setTile(int i, int j, char tile);

  char checkVictory();


  MapItem **map() const;

private:

  void initAi(char aiPlayer = O);
  AiMove getBestMove(char currentPlayer = O);
  void run_minimax();

  void deleteMap();
  void createMap();
  void eraseMap(char def = ' ');

};

#endif // XOGAME_H
