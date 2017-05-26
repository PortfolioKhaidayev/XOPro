#ifndef XOFIELD_H
#define XOFIELD_H

#include <WAbstractButton>
#include <wpainter.h>
class XOField : public WWidget
{
private:
  char** _map = nullptr;
  int _size = 3;
  int _tileSize = 32;

public:
  XOField(WWidget *parent = nullptr);

  void startNewGame(int size);

  bool setTile(int i, int j, char tile);

private:
  void drawGrid(WPainter &p);
  void drawTiles(WPainter &p);

  void deleteMap();
  void createMap();
  void eraseMap(char def = ' ');

  // WWidget interface
protected:
  virtual int style() override;
  virtual bool mouseReleaseEvent(WMouseEvent *e) override;
  virtual bool paintEvent(WPaintEvent *e) override;
};

#endif // XOFIELD_H
