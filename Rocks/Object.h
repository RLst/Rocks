#pragma once

#include <pkr\math\Vector2.h>

namespace aie {
	class Texture;
	class Renderer2D;
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
		};

		//Inactive
		Object*			m_next;
	};

public:
	Object();
	virtual ~Object();

	//Core essentials for object pool
	virtual bool	update(float deltaTime) = 0;
	virtual void	draw(aie::Renderer2D* renderer) {};

	//State control
	bool			isAlive() const { return m_life > 0; }
	void			kill() { m_life = 0; }

	//Pointers to next
	Object*			getNext() const { return m_next; }
	void			setNext(Object* next) { m_next = next; }

	//void			init(const Vector2 &pos, const Vector2 &vel);
	//virtual void	derivUpdate(float deltaTime) = 0;
	//virtual void	derivDraw(aie::Renderer2D* renderer) = 0;
};

} //namespace pkr
