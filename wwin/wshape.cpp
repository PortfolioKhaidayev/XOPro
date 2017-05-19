#include "wshape.h"

WPoint WShape::pivotPonit() const
{
  return _pivotPonit;
}

void WShape::pivotPonit(const WPoint &pivotPonit)
{
  _pivotPonit = pivotPonit;
}

WPoint WShape::leftTopVertex() const
{
  return _leftTopVertex;
}

WPoint WShape::rightBotVertex() const
{
  return _rightBotVertex;
}

WSize WShape::size() const
{
  return _size;
}

void WShape::size(const WSize &size)
{
  _size = size;
}

void WShape::initGiometry()
{

  int centerX = ( _size.width()/2 );
  int centerY = ( _size.height()/2 );

  if( _pivotType == WPivotPointPosition::Center ){
    _leftTopVertex.setX( abs( centerX - _pivotPonit.x() ) );
    _leftTopVertex.setY( abs( centerY - _pivotPonit.y() ) );

    _rightBotVertex.setX( abs( centerX + _pivotPonit.x() ) );
    _rightBotVertex.setY( abs( centerY + _pivotPonit.y() ) );
  }
  if( _pivotType == WPivotPointPosition::LeftTop ){
    _leftTopVertex.setX( _pivotPonit.x() );
    _leftTopVertex.setY( _pivotPonit.y() );

    _rightBotVertex.setX( _pivotPonit.x() + _size.width() );
    _rightBotVertex.setY( _pivotPonit.y() + _size.height() );
  }
  if( _pivotType == WPivotPointPosition::LeftBot ){
    _leftTopVertex.setX( _pivotPonit.x() );
    _leftTopVertex.setY( _pivotPonit.y() + _size.height() );

    _rightBotVertex.setX( _pivotPonit.x() + _size.width() );
    _rightBotVertex.setY( _pivotPonit.y()  );
  }
  if( _pivotType == WPivotPointPosition::RightTop ){
    _leftTopVertex.setX( abs( _pivotPonit.x() - _size.width() ) );
    _leftTopVertex.setY( _pivotPonit.y()  );

    _rightBotVertex.setX( _pivotPonit.x()  );
    _rightBotVertex.setY( _pivotPonit.y() + _size.height() );
  }
  if( _pivotType == WPivotPointPosition::RightBot ){
    _leftTopVertex.setX( abs( _pivotPonit.x() - _size.width() ) );
    _leftTopVertex.setY( abs( _pivotPonit.y() - _size.height() ) );

    _rightBotVertex.setX( _pivotPonit.x() );
    _rightBotVertex.setY( _pivotPonit.y() );
  }
  if( _pivotType == WPivotPointPosition::LeftJustify ){
    _leftTopVertex.setX( _pivotPonit.x() );
    _leftTopVertex.setY( abs( _pivotPonit.y() - centerY ) );

    _rightBotVertex.setX( _pivotPonit.x() + _size.width() );
    _rightBotVertex.setY( abs( _pivotPonit.y() + centerY ) );
  }
  if( _pivotType == WPivotPointPosition::TopJustify ){
    _leftTopVertex.setX( _pivotPonit.x() - _size.width() );
    _leftTopVertex.setY( _pivotPonit.y() );

    _rightBotVertex.setX( _pivotPonit.x() + _size.width() );
    _rightBotVertex.setY( _pivotPonit.y() + _size.height() );
  }
  if( _pivotType == WPivotPointPosition::BotJustify ){
    _leftTopVertex.setX( abs( _pivotPonit.x() - centerX ) );
    _leftTopVertex.setY( abs( _pivotPonit.y() - _size.height() ) );

    _rightBotVertex.setX( _pivotPonit.x() + centerX);
    _rightBotVertex.setY( _pivotPonit.y() );
  }
  if( _pivotType == WPivotPointPosition::RightJustify ){
    _leftTopVertex.setX( abs( _pivotPonit.x() - _size.width() ) );
    _leftTopVertex.setY( abs( _pivotPonit.y() - centerY ) );

    _rightBotVertex.setX( _pivotPonit.x() );
    _rightBotVertex.setY( _pivotPonit.y() + centerY );
  }
}

WShape::WShape(WPoint pivotPoint, WSize size, WPivotPointPosition pivotPointType)
{
  this->setGeometry(pivotPoint, size, pivotPointType);
}

void WShape::setGeometry(WPoint pivotPoint, WSize size, WPivotPointPosition pivotPointType)
{
  _pivotPonit = pivotPoint;
  _size = size;
  _pivotType = pivotPointType;

  this->initGiometry();
}

void WShape::setGeometry(WPivotPointPosition pivotPointType)
{
  _pivotType = pivotPointType;

  this->initGiometry();
}

void WShape::draw(HDC &hdc, WPoint pos)
{
  this->pivotPonit( pos );
  this->draw(hdc);
}
