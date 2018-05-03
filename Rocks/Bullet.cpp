#include "Bullet.h"
#include "RockPool.h"
#include <glm/vec2.hpp>
#include "GameDefines.h"
#include <Renderer2D.h>

namespace pkr {

Bullet::Bullet() : m_active(false)
{}

Bullet::~Bullet()
{}

void Bullet::init(glm::vec2 pos, glm::vec2 vel)
{
	//Set bullet as active and init with pos and velocity
	m_active = true;
	m_state.live.m_pos = pos;
	m_state.live.m_vel = vel;
}

bool Bullet::update(float deltaTime)
{
	//IMPORTANT!!! 
	//Returns TRUE if the bullet dies
	//Returns FALSE if the bullet is inactive

	if (!isActive()) return false;	//End and return false if not active

	//Move the object
	m_state.live.m_pos += m_state.live.m_vel * deltaTime;

	////Check for bullet "death" conditions
	//Out of bounds
	if (outOfBounds()) {
		m_active = false;
		return m_active == false;
	}
	//Hit a rock
	//else if (hasCollided(RockPool* rockpool)) {
	//	rockPool->takeDamage();
	//	m_active = false;
	//	return false;
	//}

	//return true;	//Update executed fine. Still alive //********** this was causing the major headache!
}

bool Bullet::outOfBounds()
{
	//Returns true if bullet goes off screen
	if (m_state.live.m_pos.x < 0 ||
		m_state.live.m_pos.x > SCREEN_WIDTH ||
		m_state.live.m_pos.y < 0 ||
		m_state.live.m_pos.y > SCREEN_HEIGHT)
		return true;
	else 
		return false;
}

}

