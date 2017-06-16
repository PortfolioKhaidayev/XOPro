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

class XOGame : public WWidget
{
private:
  static int countFigure;
  char _aiPlayer = O;
  char _huPlayer = X;

  int _size = 3;
  int _tileSize = 32;
  WPoint _pos;
  WWidget* _main;
  MapItem** _map = nullptr;

public:
  XOGame( WWidget* main = nullptr );

  void checkGameOver();
  void setPos(const WPoint& point);
  void setMainWindow(WWidget* main = nullptr);

  void startNewGame(int size);

  bool setTile(int i, int j, char tile);
  WRect geometry();

  char checkVictory();  

  MapItem **map() const;

  static int getCountFigure();
  static int incrementCountFigure();

  static void setCountFigure(int value);

  int getSize() const;

private:

  void initAi(char aiPlayer = O);
  AiMove getBestMove(char currentPlayer = O, int depth = 0);
  void run_minimax();

  void deleteMap();
  void createMap();
  void eraseMap();

};

#endif // XOGAME_H
