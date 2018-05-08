#include "Rock.h"
#include "Bullet.h"
#include "Fighter.h"
#include <Texture.h>
#include "glm/vec2.hpp"
#include <Renderer2D.h>
#include "GameDefines.h"

namespace pkr {

Rock::Rock() {}
Rock::~Rock() {}

void Rock::init(glm::vec2 pos, glm::vec2 vec, glm::vec2 ang, float health, float radius, float attack, aie::Texture* tex, RockType type)
{
	m_state.live.pos = pos;
	m_state.live.vel = vec;
	m_state.live.ang = ang;
	m_state.live.health = health;
	m_state.live.radius = radius;
	m_state.live.attack = attack;
	m_state.live.tex = tex;
	m_state.live.type = type;
}

void Rock::update(float deltaTime)
{
	//Do nothing if rock not alive
	if (!isAlive()) return;

	//Challenge; Make the rocks speed up the longer the game goes on
	static float baseSpeed = 0.0f;
	baseSpeed += deltaTime * 0.01;

	//Move the rock
	m_state.live.pos.x += (m_state.live.vel.x * baseSpeed) * deltaTime;
	m_state.live.pos.y += (m_state.live.vel.y * baseSpeed) * deltaTime;

	//Rotate the rock
	m_state.live.ang.g += m_state.live.ang.r * deltaTime;
}

void Rock::draw(aie::Renderer2D * renderer)
{
	//DEBUG: Collision box
	//renderer->drawCircle(m_state.live.pos.x, m_state.live.pos.y, m_state.live.radius * 2.0f);
	
	//Rock
	renderer->drawSprite(m_state.live.tex, m_state.live.pos.x, m_state.live.pos.y, 0.0f, 0.0f, m_state.live.ang.g);
}

bool Rock::isAlive() const
{
	return m_state.live.health > 0;
}

bool Rock::hasHitPlayer(Fighter * player)
{
	//Return true if hit
	if (getDistance(this->getPos(), player->getPos()) < this->getRadius() * 1.8f)	//Fighter doesn't really have a radius, so just add an arbitrary multiplier to the collision zone of the rock
		return true;
	else
		return false;
}

bool Rock::hasBeenShot(Bullet * bullet)
{
	//If the bullet is in range of rock
	if ( getDistance(this->getPos(), bullet->getPos()) < this->getRadius() ) {
		//Kill bullet and damage rock
        bullet->kill();
		this->takeDamage(bullet->getAttack());
		return true;	//Might be redundant?
	}
	else 
		return false;
}

void Rock::wrapAroundScreen()
{
	static float padding = 70;
	//Wrap from top to bottom
	if (m_state.live.pos.y > SCREEN_HEIGHT + padding)
		m_state.live.pos.y = 0 - padding;

	//Wrap from bottom to top
	if (m_state.live.pos.y < 0 - padding)
		m_state.live.pos.y = SCREEN_HEIGHT + padding;

	//Wrap from left to right
	if (m_state.live.pos.x < 0 - padding)
		m_state.live.pos.x = SCREEN_WIDTH + padding;

	//Wrap from right to left
	if (m_state.live.pos.x > SCREEN_WIDTH + padding)
		m_state.live.pos.x = 0 - padding;
}

}


