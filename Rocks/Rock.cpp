#include "Rock.h"
#include <Texture.h>
#include "glm/vec2.hpp"
#include "GameDefines.h"

namespace pkr {

Rock::Rock()
{
}
Rock::~Rock()
{
}

void Rock::init(glm::vec2 pos, glm::vec2 vec, glm::vec2 ang, 
	float health, float radius, aie::Texture* tex)
{
	m_alive = true;
	m_state.live.pos = pos;
	m_state.live.vec = vec;
	m_state.live.ang = ang;
	m_state.live.health = health;
	m_state.live.radius = radius;
	m_state.live.tex = tex;
}

bool Rock::update(float deltaTime)
{
	//Moves and kills the rock if it goes out of bounds?
	//NOPE -> JUST DO ONE THING. Let RockPool::update() deal with this
	if (!isAlive()) return false;

	//Move the rock
	m_state.live.pos += m_state.live.vec * deltaTime;

	//If the rock moves offscreen then flag (should I just kill it)
	if (m_state.live.pos.x < (0 - m_state.live.radius * 2) &&
		m_state.live.pos.x >(SCREEN_WIDTH + m_state.live.radius * 2) &&
		m_state.live.pos.y < (0 - m_state.live.radius * 2) &&
		m_state.live.pos.y >(SCREEN_HEIGHT + m_state.live.radius * 2))
		return false;
	else
		return true;
}

void Rock::kill()
{
	m_alive = false;

	//setup next?
}

bool Rock::hasBeenShot(Bullet & bullet)
{
	//If the bullet is in range of rock
	
		//Take damage

		//Kill bullet

	return false;
}

}


