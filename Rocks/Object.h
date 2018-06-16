#pragma once
#include <Vector2.h>
//#include <Matrix3.h>

namespace aie {
	class Texture;
}

namespace pkr {

class Object
{
protected:
	//Essential symbols for a free list
	float				m_life;		//Can be either time or health based
	aie::Texture*		m_tex;
	union
	{
		//Active
		struct {
			Vector2		m_pos;
			Vector2		m_vel;
			//Matrix3		m_worldTransform;
		};

		//Inactive
		Object*			m_next;
	};

public:
	Object();
	virtual ~Object();

	//Core essentials for object pool
	void			init(const Vector2 &pos, const Vector2 &vel);
	void			update(float deltaTime); //Maybe should use onUpdate/update combo
	//Active
	bool			isAlive() const { return m_life > 0; }
	void			kill() { m_life = 0; }
	//Pointers to next
	Object*			getNext() const { return m_next; }
	void			setNext(Object* next) { m_next = next; }
};

} //namespace pkr
