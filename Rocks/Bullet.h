#pragma once
#include <pkr\math\Vector2.h>

namespace pkr {

class Bullet
{
	float				m_life;
	union {
		//In use
		struct {
			Vector2	pos;
			Vector2	vel;
			float		attack;
		} live;

		//Available
		Bullet*			next;
	} m_state;

public:
	Bullet();
	~Bullet();

	//Core
	void				init(Vector2 pos, Vector2 vel, float life, float attack);
	bool				update(float deltaTime);
	//void				draw(aie::Renderer2D* renderer);

	//Active
	bool				isAlive() const { return m_life > 0; }
	void				kill() { m_life = 0.0f; }

	//Gets
    Bullet*				getNext() const { return m_state.next; }
	Vector2			getPos() const { return m_state.live.pos; }
	Vector2			getVel() const { return m_state.live.vel; }
	float				getAttack() const { return m_state.live.attack; }

	//Sets
	void				setNext(Bullet* next) { m_state.next = next; }
};

}
