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
	glm::vec2		m_vel;		//Unit vectors
	float			m_ang;
	float			m_speed;	//Linear speed
	float			m_angSpeed;	
	float			m_smooth;
	//float			m_playerAngle;
	//float			m_playerSpeed;
public:
	Fighter();
	~Fighter();
	void update(float deltaTime);
	void draw(aie::Renderer2D* spriteBatch);

	//Rotation
	void rotate(float amount);

	//Getters
	glm::vec2 getPos() { return m_pos; }
	float getAng() { return m_ang; }
};

}
