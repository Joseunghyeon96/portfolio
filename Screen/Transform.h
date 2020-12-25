#pragma once
#include "Component.h"

class Transform :
	public Component
{
	Vector2 position;
	Vector2 rotation;
	Vector2 scale;

public:
	Transform(GameObject* gameObject, 
		const Vector2& position = Vector2::zero,
		const Vector2& rotation = Vector2::zero,
		const Vector2& scale = Vector2::ones);
	~Transform();
	Vector2& getPos();
	Vector2& getScale() { return scale; }
	void setPos(const Vector2& pos);
	void setScale(const Vector2& scale);

protected:
	void start();
	void update();

};

