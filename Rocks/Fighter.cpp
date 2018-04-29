#include "Fighter.h"
#include "Bullet.h"
#include <Texture.h>
#include <Input.h>
#include <Renderer2D.h>
#include "GameDefines.h"
#include <cmath>

namespace pkr {

Fighter::Fighter()
{
	m_tex = new aie::Texture("../bin/textures/ship.png");	//New ship texture on hep
	
	//Position in centre of screen, 0 degrees is facing upwards
	m_pos.x = SCREEN_WIDTH / 2;
	m_pos.y = SCREEN_HEIGHT / 2;
	m_ang = 0.0f;

	//Basic speed and interpolation settings
	m_speed = 500.0f;
	m_angSpeed = 100.0f;
	m_smooth = 50.0f;
}

Fighter::~Fighter()
{
	delete m_tex;
}

void Fighter::update(float deltaTime)
{
	aie::Input* input = aie::Input::getInstance();
	static float angAdj = 90.0f;			//Angle offset (if required)

	///MOVEMENT
	m_vel = { 0 , 0 };

	//Forward
	if (input->isKeyDown(aie::INPUT_KEY_W)) {
		m_vel.x = cos((angAdj + m_ang) * PI / 180.0f) * (m_speed * deltaTime);
		m_vel.y = sin((angAdj + m_ang) * PI / 180.0f) * (m_speed * deltaTime);
		//m_pos.x -= (m_speed * deltaTime);
		//m_pos.y -= m_speed * deltaTime;
	}

	//Backward
	if (input->isKeyDown(aie::INPUT_KEY_S)) {
		m_vel.x = cos((angAdj + m_ang) * PI / 180.0f) * (-m_speed * deltaTime);
		m_vel.y = sin((angAdj + m_ang) * PI / 180.0f) * (-m_speed * deltaTime);
		//m_pos.x += m_speed * deltaTime;
	}

	//Strafe left
	if (input->isKeyDown(aie::INPUT_KEY_A))	{
		m_vel.x = cos((angAdj + m_ang - 90.0f) * PI / 180.0f) * (-m_speed * deltaTime);
		m_vel.y = sin((angAdj + m_ang - 90.0f) * PI / 180.0f) * (-m_speed * deltaTime);
	}

	//Strafe right
	if (input->isKeyDown(aie::INPUT_KEY_D)) {
		m_vel.x = cos((angAdj + m_ang - 90.0f) * PI / 180.0f) * (m_speed * deltaTime);
		m_vel.y = sin((angAdj + m_ang - 90.0f) * PI / 180.0f) * (m_speed * deltaTime);
	}

	///ROTATION
	//static float angSpeed = 200.0f;
	//Angle
	if (input->isKeyDown(aie::INPUT_KEY_Q)) {
		//Rotate left
		rotate(m_angSpeed * deltaTime);
	}
	if (input->isKeyDown(aie::INPUT_KEY_E)) {
		//Rotate right
		rotate(-m_angSpeed * deltaTime);
	}
}

void Fighter::draw(aie::Renderer2D * spriteBatch)
{
	//Draw the ship including rotation
	spriteBatch->drawSprite(m_tex, m_pos.x, m_pos.y, 0.0f, 0.0f, rads(m_ang));
}

void Fighter::rotate(float amount)
{
	//Apply rotation
	m_ang += amount;

	//Wrap
	//do {
		if (m_ang < 0.0f)
			m_ang + 360.0f;
		else if (m_ang > 360.0f)
			m_ang - 360.0f;
	//} while (m_ang < 0.0f && m_ang > 360.0f);
}

}
