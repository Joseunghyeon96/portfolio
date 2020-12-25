#include "stdafx.h"
#include "GameObject.h"
#include "Transform.h"


vector<GameObject*> GameObject::gameObjects;

GameObject::GameObject(const string& name, GameObject* parent, const string& tag,const string& shape)
	: name(name),tag(tag), enabled(true), parent(parent),shape(shape)
	,screen(Screen::getInstance()),transform(new Transform(this)) 
{
	components.clear();
	components.push_back(transform);
}


GameObject::~GameObject()
{
}

void GameObject::traverseStart()
{
	if (enabled == false) return;

	for (auto comp : components)
	{
		comp->start();
	}
	for (auto child : children)
	{
		child->traverseStart();
	}
}

void GameObject::traverseUpdate()
{
	if (enabled == false) return;

	for (auto comp : components)
	{
		
		comp->update();
	}
	for (auto child : children)
	{
		child->traverseUpdate();

	}
}

void GameObject::traverseLateUpdate()
{
	if (enabled == false) return;

	for (auto comp : components)
	{

		comp->lateUpdate();
	}
	for (auto child : children)
	{
		child->traverseLateUpdate();

	}
}

void GameObject::traverseDraw()
{

	if (enabled == false) return;
	
	for (auto comp  :components)
	{
		comp->draw();
	}


	for (auto child : children)
	{
		child->traverseDraw();
	}
}

Transform * GameObject::getTransform()
{
	return transform;
}

void GameObject::setTransform(Transform transform)
{
	*(this->transform) = transform;
}

void GameObject::setPosition(const Vector2& pos)
{
	transform->setPos(pos);
}

void GameObject::setScale(const Vector2 & scale)
{
	transform->setScale(scale);
}

GameObject * GameObject::Find(const string & path)
{
	for (auto gameObject : gameObjects)
	{
		if (gameObject->name == path)
			return gameObject;
	}

	return nullptr;
}

vector<GameObject *> GameObject::allFind(const string & path)
{
	vector<GameObject*> finds;

	for (auto gameObject : gameObjects)
	{
		if (gameObject->tag == path)
			finds.push_back(gameObject);
	}
	return finds;
}

void GameObject::setParent(GameObject * parent)
{
	{
		this->parent = parent;
	}

}

void GameObject::destroy(GameObject * gameObject)
{
	if (gameObject == nullptr) return;


	gameObjects.erase(remove_if(gameObjects.begin(), gameObjects.end()
		, [gameObject](GameObject* obj) {return gameObject == obj; }), gameObjects.end());
	delete gameObject;
	gameObject = nullptr;
	return;
	
}

vector<GameObject*> GameObject::getObjs()
{
	return gameObjects;
}


