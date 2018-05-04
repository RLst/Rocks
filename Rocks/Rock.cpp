#include "Rock.h"
#include <Texture.h>
#include "glm/vec2.hpp"
#include "GameDefines.h"
#include <Renderer2D.h>

namespace pkr {

Rock::Rock()
{
}
Rock::~Rock()
{
}

void Rock::init(glm::vec2 pos, glm::vec2 vec, glm::vec2 ang, float health, float radius, float attack, aie::Texture* tex)
{
	m_active = true;
	m_state.live.pos = pos;
	m_state.live.vel = vec;
	m_state.live.ang = ang;
	m_state.live.health = health;
	m_state.live.radius = radius;
	m_state.live.attack = attack;
	m_state.live.tex = tex;
}

bool Rock::update(float deltaTime)
{
	//Moves and kills the rock if it goes out of bounds?
	//NOPE -> JUST DO ONE THING. Let RockPool::update() deal with this
	if (!isActive()) return false;

	//Move the rock
	m_state.live.pos += m_state.live.vel * deltaTime;
	//Continue rotating the rock
	//m_state.live.ang.g += m_state.live.ang.r * deltaTime;

	//Kill if out of bounds
	if (outOfBounds()) {
		kill();
		return m_active == false;
		//return true;
	}

	////If the rock moves offscreen then flag (should I just kill it)
	//if (m_state.live.pos.x < (0 - m_state.live.radius * 2) &&
	//	m_state.live.pos.x >(SCREEN_WIDTH + m_state.live.radius * 2) &&
	//	m_state.live.pos.y < (0 - m_state.live.radius * 2) &&
	//	m_state.live.pos.y >(SCREEN_HEIGHT + m_state.live.radius * 2)) {
	//	return true;
	//}
	//else
	//	return false;
}

void Rock::draw(aie::Renderer2D * renderer)
{
	renderer->drawSprite(m_state.live.tex, m_state.live.pos.x, m_state.live.pos.y, 0.0f, 0.0f, m_state.live.ang.g);
}

bool Rock::outOfBounds()
{
	//returns true if rock is out of bounds
	if (m_state.live.pos.x < 0 ||
		m_state.live.pos.x > SCREEN_WIDTH ||
		m_state.live.pos.y < 0 ||
		m_state.live.pos.y > SCREEN_HEIGHT)
		return true;
	else
		return false;		
}

void Rock::kill()
{
	m_active = false;

	//setup next?
}

bool Rock::isActive() const
{
	return m_active == true;
}

bool Rock::hasBeenShot(Bullet & bullet)
{
	//If the bullet is in range of rock
	
		//Take damage

		//Kill bullet

	return false;
}

}


