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
	glm::vec2		m_pos, m_targetPos;		//t for target
	glm::vec2		m_vel;				//Unit vectors
	float			m_ang, m_targetAng;
	float			m_speed;			//Linear speed
	float			m_angSpeed;			//Angular speed
	float			m_smooth;
	//float			m_playerAngle;
	//float			m_playerSpeed;
	//Gun
	double			m_lastFired;
	float			m_fireRate = 0.3f;		//in seconds
	int				m_gunOffset = 30;
	float			m_bulletSpeed = 750.0f;

public:
	Fighter();
	~Fighter();
	void update(float deltaTime);
	void draw(aie::Renderer2D* spriteBatch);

	//Rotation
	void angleWrap();

	glm::vec2		getPos() { return m_pos; }
	glm::vec2		getVel() { return m_vel; }
	float			getAng() { return m_ang; }

	//Guns
	glm::vec2		getGunPos();
	glm::vec2		getGunVel();
	double			getLastFired() { return m_lastFired; }
	float			getFireRate() { return m_fireRate; }
	void			setLastFired(double timer) { m_lastFired = timer; }

	//debugs
	glm::vec2		getTargetPos() { return m_targetPos; }

};

}
