#ifndef XOSHAPE_H
#define XOSHAPE_H

#include <WObject>
#include <WPoint>
#include <WSize>

enum class WPivotPointPosition{
  Center,
  LeftTop,
  LeftBot,
  RightTop,
  RightBot,
  TopJustify,
  BotJustify,
  LeftJustify,
  RightJustify,
};

class WShape
{
protected:
  WPoint _pivotPonit;
  WPivotPointPosition _pivotType;

  WPoint _leftTopVertex;
  WPoint _rightBotVertex;

  WSize _size;


  void initGiometry();

public:
  WShape(WPoint pivotPoint, WSize size, WPivotPointPosition pivotPointType = WPivotPointPosition::Center);

  void setGeometry(WPoint pivotPoint, WSize size, WPivotPointPosition pivotPointType = WPivotPointPosition::Center);
  void setGeometry(WPivotPointPosition pivotPointType = WPivotPointPosition::Center);

  virtual void draw(HDC hdc);
  void draw(HDC hdc, WPoint pos);

  WPoint pivotPonit() const;
  void pivotPonit(const WPoint &pivotPonit);

  WPoint leftTopVertex() const;
  WPoint rightBotVertex() const;

  WSize size() const;
  void size(const WSize &size);
};

#endif // XOSHAPE_H
