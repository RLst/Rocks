#include "Bullet.h"
#include "RockPool.h"
#include <glm/vec2.hpp>
#include "GameDefines.h"
#include <Renderer2D.h>

namespace pkr {

Bullet::Bullet() : m_life(false)
{}

Bullet::~Bullet()
{}

void Bullet::init(glm::vec2 pos, glm::vec2 vel, float life, float attack)
{
	//Set bullet as active and init with pos and velocity
	m_life = life;
	m_state.live.pos = pos;
	m_state.live.vel = vel;
	m_state.live.attack = attack;
}

bool Bullet::update(float deltaTime)
{
	//IMPORTANT!!! 
	//Returns TRUE if the bullet dies
	//Returns FALSE if the bullet is inactive

	if (!isAlive()) return false;	//End and return false if not active

	//Move the object
	m_state.live.pos += m_state.live.vel * deltaTime;

	//Decrease life of bullet
	m_life -= deltaTime;

	return m_life <= 0;
}

}

