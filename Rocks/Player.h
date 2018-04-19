#pragma once

namespace aie
{
	class Texture;
	class Renderer2D;
	class Input;
}

class Player
{
	aie::Texture*	m_player;
	float			m_playerPosX;
	float			m_playerPosY;
	float			m_playerSpeed;

public:
	Player();
	~Player();
	void update(float deltaTime, aie::Input* input);
	void draw(aie::Renderer2D* spriteBatch);
};

