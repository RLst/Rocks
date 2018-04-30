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
	m_tex = new aie::Texture("../bin/textures/ship.png");	//New ship texture on hep
	
	//Position in centre of screen, 0 degrees is facing upwards
	m_pos.x = m_targetPos.x = SCREEN_WIDTH / 2;
	m_pos.y = m_targetPos.y = SCREEN_HEIGHT / 2;
	m_ang = m_targetAng = 0.0f;

	//Basic speed and interpolation settings
	m_speed = 600.0f;
	m_angSpeed = 250.0f;
	m_smooth = 1.5f;		//Lower is more lerpy
}

Fighter::~Fighter()
{
	delete m_tex;
}

void Fighter::update(float deltaTime)
{
	//* Process user inputs and controls (move and fire)
	//* Clamp angle within bounds
	//* Keep player within bounds of screen

	aie::Input* input = aie::Input::getInstance();

	///MOVEMENT
	static float angAdj = 90.0f;			//Angle offset (if required)

	m_vel = { 0 , 0 };
	//Forward
	if (input->isKeyDown(aie::INPUT_KEY_W)) {
		m_vel.x = cos((angAdj + m_ang) * PI / 180.0f) * (m_speed * deltaTime);
		m_vel.y = sin((angAdj + m_ang) * PI / 180.0f) * (m_speed * deltaTime);
	}
	//Backward
	if (input->isKeyDown(aie::INPUT_KEY_S)) {
		m_vel.x = cos((angAdj + m_ang) * PI / 180.0f) * (-m_speed * deltaTime);
		m_vel.y = sin((angAdj + m_ang) * PI / 180.0f) * (-m_speed * deltaTime);
	}
	//Targets
	m_targetPos += m_vel;

	///ROTATION
	//static float angSpeed = 200.0f;
	//Angle
	if (input->isKeyDown(aie::INPUT_KEY_A)) {
		//Rotate left
		m_targetAng += m_angSpeed * deltaTime;	//Why is this seemingly inverted?
	}
	if (input->isKeyDown(aie::INPUT_KEY_D)) {
		//Rotate right
		m_targetAng -= m_angSpeed * deltaTime;
	}
	angleWrap();	//Keep angle within bounds

	//LERP - Smoothly move towards the target position
	m_pos -= (m_pos - m_targetPos) * m_smooth * deltaTime;
	m_ang -= (m_ang - m_targetAng) * m_smooth * deltaTime;
	//m_pos = lerp(actual, target, smoothingFactor, dt)
}

void Fighter::draw(aie::Renderer2D * spriteBatch)
{
	//Draw the ship including rotation
	spriteBatch->drawSprite(m_tex, m_pos.x, m_pos.y, 0.0f, 0.0f, degTOrads(m_ang));
}

void Fighter::angleWrap()
{
	//Keep wrapping until target (leading) angle is within bounds
	while (m_targetAng < 0.0f /*|| m_ang < 0.0f*/) {
		m_targetAng += 360.0f;
		m_ang += 360.0f;
	}
	while (m_targetAng > 360.0f /*|| m_ang > 360.0f*/) {
		m_targetAng -= 360.0f;
		m_ang -= 360.0f;
	}
}



}
