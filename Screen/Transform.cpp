#include "stdafx.h"
#include "Transform.h"

Transform::Transform(GameObject * gameObject,
	const Vector2 & position, 
	const Vector2 & rotation, 
	const Vector2 & scale)
	: position(position),
	rotation(rotation), 
	scale(scale),
	Component(gameObject)
{

}

Transform::~Transform()
{
}

void Transform::start()
{
}

void Transform::update()
{
}

Vector2& Transform::getPos()
{
	return position;
}

void Transform::setPos(const Vector2 & pos)
{
	this->position = pos;
}

void Transform::setScale(const Vector2 & scale)
{
	this->scale = scale;
}
