#include "Player.h"



Player::Player()
{
	m_player = new aie::Texture("../bin/testures/ship.png");
	m_playerPosX = 100.0f;
	m_playerPosY = 100.0f;
	m_playerSpeed = 100.0f;
}


Player::~Player()
{
	delete m_player;
}

void Player::update(float deltaTime, aie::Input * input)
{
	if (input->isKeyDown(aie::INPUT_KEY_A))
	{
		m_playerPosX -= m_playerSpeed * deltaTime;
	}

	if (input->isKeyDown(aie::INPUT_KEY_D))
	{
		m_playerPosX += m_playerSpeed * deltaTime;
	}
}

void Player::draw(aie::Renderer2D * spriteBatch)
{
	spriteBatch->drawSprite(m_player, m_playerPosX, m_playerPosY);
}
