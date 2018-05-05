#include "Rock.h"
#include <Texture.h>
#include "glm/vec2.hpp"
#include "GameDefines.h"
#include <Renderer2D.h>
#include "Fighter.h"
#include "Bullet.h"

namespace pkr {

Rock::Rock()
{
}
Rock::~Rock()
{
}

void Rock::init(glm::vec2 pos, glm::vec2 vec, glm::vec2 ang, float health, float radius, float attack, aie::Texture* tex)
{
	m_state.live.pos = pos;
	m_state.live.vel = vec;
	m_state.live.ang = ang;
	m_state.live.health = health;
	m_state.live.radius = radius;
	m_state.live.attack = attack;
	m_state.live.tex = tex;
}

void Rock::update(float deltaTime)
{
	//Do nothing if rock not alive
	if (!isAlive()) return;

	//Move the rock
	m_state.live.pos += m_state.live.vel * deltaTime;

	//Rotate the rock
	m_state.live.ang.g += m_state.live.ang.r * deltaTime;
}

void Rock::draw(aie::Renderer2D * renderer)
{
	renderer->drawSprite(m_state.live.tex, m_state.live.pos.x, m_state.live.pos.y, 0.0f, 0.0f, m_state.live.ang.g);
}

bool Rock::isAlive() const
{
	return m_state.live.health > 0;
}

bool Rock::hasHitPlayer(Fighter * player)
{
	//Return true if hit
	if (distance(this->getPos(), player->getPos()) < this->getRadius())
		return true;
	else
		return false;
}

bool Rock::hasBeenShot(Bullet * bullet)
{
	//If the bullet is in range of rock
	if ( distance(this->getPos(), bullet->getPos()) < this->getRadius() ) {
		//Kill bullet and damage rock
        bullet->kill();
		this->takeDamage(bullet->getAttack());
	}
		//return true;
	else 
		return false;
}

void Rock::wrapAroundScreen()
{
	static int padding = 40;
	//Wrap from top to bottom
	if (m_state.live.pos.y > SCREEN_HEIGHT + padding)
		m_state.live.pos.y = 0;

	//Wrap from bottom to top
	if (m_state.live.pos.y < 0 - padding)
		m_state.live.pos.y = SCREEN_HEIGHT;

	//Wrap from left to right
	if (m_state.live.pos.x < 0 - padding)
		m_state.live.pos.x = SCREEN_WIDTH;

	//Wrap from right to left
	if (m_state.live.pos.x > SCREEN_WIDTH + padding)
		m_state.live.pos.x = 0;
}

}


