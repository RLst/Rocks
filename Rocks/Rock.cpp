#include "Rock.h"
#include "Bullet.h"
#include "Fighter.h"
#include <Texture.h>
#include <pkr\math\Vector2.h>
#include <Renderer2D.h>
#include "GameDefines.h"

#include <iostream>

namespace pkr {

Rock::Rock() {}
Rock::~Rock() {}

void Rock::init(Vector2 pos, Vector2 vec, Vector2 ang, float health, float radius, float attack, aie::Texture* tex, RockType type)
{
	m_state.live.m_pos = pos;
	m_state.live.m_vel = vec;
	m_state.live.m_ang = ang;
	m_state.live.m_health = health;
	m_state.live.radius = radius;
	m_state.live.attack = attack;
	m_state.live.m_tex = tex;
	m_state.live.type = type;
}

void Rock::update(float deltaTime, float &baseSpeed)
{
	//Do nothing if rock not alive
	if (!isAlive()) return;

	//Challenge; Make the rocks speed up the longer the game goes on
	baseSpeed += deltaTime * 0.01f;

	//Move the rock
	m_state.live.m_pos.x += (m_state.live.m_vel.x * baseSpeed) * deltaTime;
	m_state.live.m_pos.y += (m_state.live.m_vel.y * baseSpeed) * deltaTime;

	//Rotate the rock
	m_state.live.m_ang.g += m_state.live.m_ang.r * deltaTime;
}

void Rock::draw(aie::Renderer2D * renderer)
{
	//DEBUG: Collision box
	//renderer->drawCircle(m_state.live.pos.x, m_state.live.pos.y, m_state.live.radius * 2.0f);
	
	//Rock
	renderer->drawSprite(m_state.live.m_tex, m_state.live.m_pos.x, m_state.live.m_pos.y, 0.0f, 0.0f, m_state.live.m_ang.g);
}

bool Rock::isAlive() const
{
	return m_state.live.m_health > 0;
}

bool Rock::hasHitPlayer(Fighter * player)
{
	//Return true if hit
	if (getDistance(this->getPos(), player->getPos()) < this->getRadius() * 1.8f)	
		//Fighter doesn't really have a radius, so just add an arbitrary multiplier to the collision zone of the rock
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
	if (m_state.live.m_pos.y > SCREEN_HEIGHT + padding)
		m_state.live.m_pos.y = 0 - padding;

	//Wrap from bottom to top
	if (m_state.live.m_pos.y < 0 - padding)
		m_state.live.m_pos.y = SCREEN_HEIGHT + padding;

	//Wrap from left to right
	if (m_state.live.m_pos.x < 0 - padding)
		m_state.live.m_pos.x = SCREEN_WIDTH + padding;

	//Wrap from right to left
	if (m_state.live.m_pos.x > SCREEN_WIDTH + padding)
		m_state.live.m_pos.x = 0 - padding;
}

}


