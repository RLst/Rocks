#include "Object.h"

namespace pkr {

Object::Object()
	:	m_life(0)
{}

Object::~Object()
{}

//void pkr::Object::init(const Vector2 & pos, const Vector2 & vel)
//{
//	m_pos = pos;
//	m_vel = vel;
//}

bool Object::update(float deltaTime)
{
	//If no more life then kill object straight away
	if (!isAlive()) kill();

	//Update core movement
	m_pos += m_vel * deltaTime;

}

} //namespace pkr
