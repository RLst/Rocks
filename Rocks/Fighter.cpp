#include "Fighter.h"
#include "Bullet.h"
#include <Texture.h>
#include <Input.h>
#include <Renderer2D.h>
#include "GameDefines.h"
#include <cmath>

#include <iostream>

namespace pkr {

Fighter::Fighter()
{
	//New ship texture on heap
	m_tex = new aie::Texture("../bin/textures/ship.png");	
	
	//Position in centre of screen, 0 degrees is facing upwards
	m_pos.x = m_targetPos.x = SCREEN_WIDTH / 2;
	m_pos.y = m_targetPos.y = SCREEN_HEIGHT / 2;
	m_ang = m_targetAng = 0;

	//Basic speed and interpolation settings
	m_speed = 600.0f;
	m_angSpeed = 300.0f;
	m_smooth = 2.0f;		//Lower is more lerpy

	//Cannon settings
	m_lastTimeShot = 0;
	m_shootDelay = 0.15f;
	m_bulletSpeed = 750.0f;

	//Health
	m_health = m_resetHealth = 1;		//Instant death
}

Fighter::~Fighter()
{
	delete m_tex;
}

void Fighter::update(float deltaTime, int & deaths)
{
	//* Process user inputs and controls (move and fire)
	//* Clamp/Wrap angle within bounds
	//* Keep player within bounds of screen

	aie::Input* input = aie::Input::getInstance();

	//Check if alive
	if (!isAlive()) {
		//Player has died..
		//[Transition to game state > PlayAgain

		//Increase death counter
		++deaths;

		//TEMP move player to a random place
		randomLocate();					//Position
		m_health = m_resetHealth;		//Health
	}

	//////////
	//MOVEMENT
	//////////
	static float angAdj = 90.0f;			//Angle offset (if needed)

	//Reset
	if (input->isKeyDown(aie::INPUT_KEY_R)) {
		reset();
	}

	m_vel = { 0 , 0 };
	//Forward
	if (input->isKeyDown(aie::INPUT_KEY_UP)) {
		m_vel.x = cos((angAdj + m_ang) * PI / 180.0f) * (m_speed * deltaTime);
		m_vel.y = sin((angAdj + m_ang) * PI / 180.0f) * (m_speed * deltaTime);
	}
	//Backward
	if (input->isKeyDown(aie::INPUT_KEY_DOWN)) {
		m_vel.x = cos((angAdj + m_ang) * PI / 180.0f) * (-m_speed * deltaTime);
		m_vel.y = sin((angAdj + m_ang) * PI / 180.0f) * (-m_speed * deltaTime);
	}
	//Targets
	m_targetPos += m_vel;

	//Clamp/wrap around screen
	ClampAroundScreen();
	//WrapAroundScreen();

	//////////
	//ROTATION
	//////////
	//Rotate left
	if (input->isKeyDown(aie::INPUT_KEY_LEFT)) {
		m_targetAng += m_angSpeed * deltaTime;	//Why is this seemingly inverted?
	}
	//Rotate right
	if (input->isKeyDown(aie::INPUT_KEY_RIGHT)) {
		m_targetAng -= m_angSpeed * deltaTime;
	}
	angleWrap();	//Keep angle within bounds

	//////////
	//SHOOTING
	//////////
	//if (input->isKeyDown(aie::INPUT_KEY_SPACE)) {
	//	if ((timer - getTimeLastFired()) > getShootDelay()) {
	//	}
	//}

	//////
	//LERP
	//Smoothly move towards the target position
	//////
	//m_pos = lerp(actual, target, smoothingFactor, dt)
	m_pos -= (m_pos - m_targetPos) * m_smooth * deltaTime;
	m_ang -= (m_ang - m_targetAng) * m_smooth * deltaTime;
}

void Fighter::draw(aie::Renderer2D * spriteBatch)
{
	//Draw the ship including rotation
	spriteBatch->drawSprite(m_tex, m_pos.x, m_pos.y, 0.0f, 0.0f, degTOrads(m_ang));
}

void Fighter::takeDamage(float damage)
{
	m_health -= damage;
}

void Fighter::reset()		//to be turned into a death function
{
	//Just reset the position
void Fighter::reset()	//Resets the player
{
	m_pos.x = m_targetPos.x = SCREEN_WIDTH / 2;
	m_pos.y = m_targetPos.y = SCREEN_HEIGHT / 2;
	m_ang = m_targetAng = 0;
}

void Fighter::angleWrap()
{
	//Keep wrapping until target (leading) angle is within bounds
	while (m_targetAng < 0.0f) {
		m_targetAng += 360.0f;
		m_ang += 360.0f;	//The actual angle also needs to be wrapped otherwise will cause sudden twists
	}
	while (m_targetAng > 360.0f) {
		m_targetAng -= 360.0f;
		m_ang -= 360.0f;
	}
}

void Fighter::ClampAroundScreen()	//Sliding collision at the edge of the screen
{
	static float padding = 10;
	//Clamp top
	if (m_pos.y > SCREEN_HEIGHT + padding) {
		m_targetPos.y = SCREEN_HEIGHT + padding;
		m_pos.y = SCREEN_HEIGHT + padding;
	}

	//Clamp bottom
	if (m_pos.y < 0 - padding) {
		m_targetPos.y = 0 - padding;
		m_pos.y = 0 - padding;
	}

	//Clamp left
	if (m_pos.x < 0 - padding) {
		m_targetPos.x = 0 - padding;
		m_pos.x = 0 - padding;
	}

	//Clamp right
	if (m_pos.x > SCREEN_WIDTH + padding) {
		m_targetPos.x = SCREEN_WIDTH + padding;
		m_pos.x = SCREEN_WIDTH + padding;
	}
}

void Fighter::WrapAroundScreen()	//Wrap the figher around the screen; doesn't work very well
{	
	static float padding = 0;
	//Wrap from top > bottom
	if (m_pos.y > SCREEN_HEIGHT + padding) {
		m_targetPos.y = 0 - padding;
		m_pos.y = 0 - padding;
	}

	//Wrap from bottom > top
	if (m_pos.y < 0 - padding) {
		m_targetPos.y = SCREEN_HEIGHT + padding;
		m_pos.y = SCREEN_HEIGHT + padding;
	}

	//Wrap from left > right
	if (m_pos.x < 0 - padding) {
		m_targetPos.x = SCREEN_WIDTH + padding;
		m_pos.x = SCREEN_WIDTH + padding;
	}

	//Wrap from right > left
	if (m_pos.x > SCREEN_WIDTH + padding) {
		m_targetPos.x = 0 - padding;
		m_pos.x = 0 - padding;
	}
}

glm::vec2 Fighter::getGunPos()
{
	//Returns the position of the fighter's gun turret
	static int gunOffset = 35;		//Gun is about 20px from the centre of the ship

	//Clear
	glm::vec2 offset = { 0,0 };

	//Position 
	offset.x = cos((90.0f + m_ang) * PI / 180.0f) * gunOffset;
	offset.y = sin((90.0f + m_ang) * PI / 180.0f) * gunOffset;

	return m_pos + offset;
}

glm::vec2 Fighter::getGunVel()
{
	//Returns a gun velocity + speed of ship
	//(That way the ship isn't able to chase after the bullets)

	//static float bulletSpeed = 500.0f;

	glm::vec2 gunVel = { 0,0 };
	gunVel.x = cos((90.0f + m_ang) * PI / 180.0f) * m_bulletSpeed;
	gunVel.y = sin((90.0f + m_ang) * PI / 180.0f) * m_bulletSpeed;

	return getVel() + gunVel;
}

}
