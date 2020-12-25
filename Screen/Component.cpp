#include "stdafx.h"
#include "Component.h"
#include "GameObject.h"

Component::Component(GameObject * gameObject)
	:gameObject(gameObject)
{
	transform = gameObject->getTransform();
}

void Component::init()
{

}

void Component::awake()
{
}

void Component::onEnable()
{
}

void Component::start()
{
}

void Component::fixedUpdate()
{
}

void Component::update()
{
}

void Component::lateUpdate()
{
}

void Component::onDisable()
{
}

void Component::onDestroy()
{
}


