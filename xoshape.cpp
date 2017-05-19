#include "xoshape.h"

WPoint XOShape::pivotPonit() const
{
  return _pivotPonit;
}

void XOShape::setPivotPonit(const WPoint &pivotPonit)
{
  _pivotPonit = pivotPonit;
}

WPoint XOShape::leftTopVertex() const
{
  return _leftTopVertex;
}

WPoint XOShape::rightBotVertex() const
{
  return _rightBotVertex;
}

WSize XOShape::size() const
{
  return _size;
}

void XOShape::setSize(const WSize &size)
{
  _size = size;
}

void XOShape::initGiometry()
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

XOShape::XOShape()
  : setType( WObjectType::Shape )
{
}

XOShape::XOShape(WObject parent)
  :WObject( parent ), setType( WObjectType::Shape )
{
}

XOShape::XOShape(WPoint pivotPoint, WSize size, WPivotPointPosition pivotPointType)
{
  this->setGiometry(pivotPoint, size, pivotPointType);
}

void XOShape::setGiometry(WPoint pivotPoint, WSize size, WPivotPointPosition pivotPointType)
{
  _pivotPonit =  pivotPoint;
  _size = size;
  _pivotType = pivotPointType;

  this->initGiometry();
}

void XOShape::setGiometry(WPivotPointPosition pivotPointType)
{
  _pivotType = pivotPointType;

  this->initGiometry();
}

void XOShape::draw(HDC hdc, WPoint pos)
{
  this->pivotPonit( pos );
  this->draw(hdc);
}
