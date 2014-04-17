#include "GameObject.h"

GameObject::GameObject()
{
	transform.position.x = transform.position.y = 0;
	transform.scale.x = transform.scale.y = 1;
	angle = 0;
}

GameObject::~GameObject()
{

}

float GameObject::getTx(void)
{
	return transform.position.x;
}

float GameObject::getTy(void)
{
	return transform.position.y;
}

float GameObject::getEx(void)
{
	return transform.scale.x;
}

float GameObject::getEy(void)
{
	return transform.scale.y;
}

float GameObject::getAngle(void)
{
	return angle;
}

void GameObject::incrementAngle()
{
	angle += 1;
}

void GameObject::decrementAngle()
{
	angle -= 1;
}

void GameObject::incrementTx()
{
	transform.position.x += 10;
}

void GameObject::incrementTy()
{
	transform.position.y += 10;
}

void GameObject::incrementEx()
{
	transform.scale.x += 0.1;
}

void GameObject::incrementEy()
{
	transform.scale.y += 0.1;
}

void GameObject::decrementTx()
{
	transform.position.x -= 10;
}

void GameObject::decrementTy()
{
	transform.position.y -= 10;
}

void GameObject::decrementEx()
{
	transform.scale.x -= 0.1;
}

void GameObject::decrementEy()
{
	transform.scale.y -= 0.1;
}
