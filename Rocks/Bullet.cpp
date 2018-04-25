#include "Bullet.h"

Bullet::Bullet()
{
}


Bullet::~Bullet()
{
}

void Bullet::init(glm::vec2 pos, glm::vec2 vel, int lifetime) :
	m_pos(pos),
	m_vel(vel),
	m_framesLeft(lifetime)
{
	
}

bool Bullet::animate()
{
	if (!inUse()) return false;

	--m_framesLeft;
	m_pos += m_vel;

	return m_framesLeft == 0;
}
