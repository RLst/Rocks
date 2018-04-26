#include "Fighter.h"
#include "Bullet.h"
#include <Texture.h>
#include <Input.h>
#include <Renderer2D.h>

Fighter::Fighter()
{
	m_player = new aie::Texture("../bin/testures/ship.png");
	m_playerPos.x = 100.0f;
	m_playerPos.y = 100.0f;
	m_playerSpeed = 100.0f;
}

Fighter::~Fighter()
{
	delete m_player;
}

void Fighter::update(float deltaTime, aie::Input * input)
{
	if (input->isKeyDown(aie::INPUT_KEY_A))
	{
		m_playerPos.x -= m_playerSpeed * deltaTime;
	}

	if (input->isKeyDown(aie::INPUT_KEY_D))
	{
		m_playerPos.x += m_playerSpeed * deltaTime;
	}
}

void Fighter::draw(aie::Renderer2D * spriteBatch)
{
	spriteBatch->drawSprite(m_player, m_playerPos.x, m_playerPos.y);
}
