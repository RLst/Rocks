#include "Bullet.h"
#include <glm/vec2.hpp>

namespace pkr {

Bullet::Bullet()
{
}


Bullet::~Bullet()
{
}

void Bullet::init(glm::vec2 pos, glm::vec2 vel)
{
	m_pos = pos;
	m_vel = vel;
}

bool Bullet::animate()
{
	if (!inUse()) return false;

	--m_framesLeft;
	m_pos += m_vel;

	return m_framesLeft == 0;
}

}
