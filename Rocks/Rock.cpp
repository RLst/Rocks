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
	//NOTICE! This function must return something
	//RETURN true to kill this object
	//RETURN false to continue rendering this object

	//Moves and kills the rock if it goes out of bounds?
	//NOPE -> JUST DO ONE THING. Let RockPool::update() deal with this
	if (!isActive()) return false;

	//Move the rock
	m_state.live.pos += m_state.live.vel * deltaTime;

	//Rotate the rock
	m_state.live.ang.g += m_state.live.ang.r * deltaTime;

	//Wrap if out of bounds
	if (outOfBounds()) {
		wrapAroundScreen();
		//return m_active == false;
		return false;
	}

	//CHECK COLLISION CONDITIONS
	//if (hasBeenShot)


	
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


