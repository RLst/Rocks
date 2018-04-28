#pragma once

//References and prototype
#include <glm\vec2.hpp>
namespace aie
{
	class Texture;
	class Renderer2D;
	class Input;
}

namespace pkr {

class Fighter
{
	aie::Texture*	m_tex;
	glm::vec2		m_pos;
	glm::vec2		m_vel;		//velocity
	glm::vec2		m_ang;
	float			m_smooth;
	//float			m_playerAngle;
	//float			m_playerSpeed;
public:
	Fighter();
	~Fighter();
	void update(float deltaTime, aie::Input* input);
	void draw(aie::Renderer2D* spriteBatch);

	//Getters
	glm::vec2 getPos() { return m_pos; }
};

}
