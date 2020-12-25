#pragma once

class GameObject;
class Transform;

class Component
{

	Transform* transform;

protected:
	GameObject* gameObject;

public:
	Component(GameObject* gameObject);

	virtual ~Component() {}
	void init();

protected:
	friend class GameObject;
	virtual void awake();
	virtual void onEnable();
	virtual void start();
	virtual void fixedUpdate();
	virtual void update();
	virtual void lateUpdate();
	virtual void onDisable();
	virtual void onDestroy();
	virtual void draw() {}

};

