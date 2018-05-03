#include "Bullet.h"
#include "RockPool.h"
#include <glm/vec2.hpp>
#include "GameDefines.h"

namespace pkr {

Bullet::Bullet() : m_active(false)
{}

Bullet::~Bullet()
{}

void Bullet::initialise(glm::vec2 &pos, glm::vec2 &vel)
{
	m_active = true;
	m_state.live.m_pos = pos;
	m_state.live.m_vel = vel;
}

bool Bullet::advance(float deltaTime)
{
	if (!isActive()) return false;	//End and return false if not active

	//Move object
	m_state.live.m_pos += m_state.live.m_vel * deltaTime;

	//Check for collisions or out of bounds
	if (outOfBounds()) {
		m_active = false;
		return false;
	}
	//else if (hasCollided(RockPool* rockpool)) {
	//	rockPool->takeDamage();
	//	m_active = false;
	//	return false;
	//}
	return true;	//Update executed fine. Still alive
}

bool Bullet::outOfBounds()
{
	if (m_state.live.m_pos.x < 0 ||
		m_state.live.m_pos.x > SCREEN_WIDTH ||
		m_state.live.m_pos.y < 0 ||
		m_state.live.m_pos.y > SCREEN_HEIGHT)
		return true;
	else 
		return false;
}

}
