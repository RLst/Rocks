#pragma once

//References and prototype
#include <pkr\math\Vector2.h>
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

	//Position and Rotation
	Vector2		m_pos, m_targetPos;		
	float			m_ang, m_targetAng;		

	//Movement
	Vector2		m_vel;
	float			m_speed, m_angSpeed;

	//LERP
	float			m_smooth;

	//Health
	float			m_health;
	float			m_resetHealth;

	//Gun
	double			m_lastTimeShot;
	float			m_shootDelay;			//in seconds
	int				m_gunOffset;
	float			m_bulletSpeed;

public:
	Fighter();
	~Fighter();

	//Core
	void update(float deltaTime, int & deaths);
	void draw(aie::Renderer2D* renderer);

	//Health
	void			takeDamage(float damage);
	bool			isAlive() { return m_health > 0; }
	void			randomLocate();
	void			reset();		//Resets player position

	//Vectors
	Vector2		getPos() { return m_pos; }
	Vector2		getVel() { return m_vel; }
	void			angleWrap();
	float			getAng() { return m_ang; }
	void			ClampAroundScreen();
	void			WrapAroundScreen();

	//Guns
	Vector2		getGunPos();
	Vector2		getGunVel();
	double			getTimeLastFired() { return m_lastTimeShot; }
	float			getShootDelay() { return m_shootDelay; }
	void			setLastFired(double timer) { m_lastTimeShot = timer; }

};

}
