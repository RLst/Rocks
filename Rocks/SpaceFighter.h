#pragma once

#include <glm\vec2.hpp>

namespace aie
{
	class Texture;
	class Renderer2D;
	class Input;
}

class Bullet;

class SpaceFighter
{
	aie::Texture*	m_player;
	glm::vec2		m_playerPos;
	float			m_playerAngle;
	float			m_playerSpeed;
	//float			m_playerPosX;
	//float			m_playerPosY;



public:
	SpaceFighter();
	~SpaceFighter();
	void update(float deltaTime, aie::Input* input);
	void draw(aie::Renderer2D* spriteBatch);
};

