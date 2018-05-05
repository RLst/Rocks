#pragma once
#include <glm/vec2.hpp>

namespace pkr {

class Bullet
{
	int					m_life;
	union {
		//In use
		struct {
			glm::vec2	pos;
			glm::vec2	vel;
		} live;

		//Available
		Bullet*			next;
	} m_state;

public:
	Bullet();
	~Bullet();

	//Core
	void				init(glm::vec2 pos, glm::vec2 vel, int life);
	bool				update(float deltaTime);
	//void draw(aie::Renderer2D* renderer);

	//Active
	bool				isAlive() const { return m_life > 0; }
	void				kill() { m_life = 0; }

	//Checks
	bool				outOfBounds();

	//Gets
	Bullet*				getNext() const { return m_state.next; }
	//aie::Texture getTex() const { return m_state.live.}
	glm::vec2			getPos() const { return m_state.live.pos; }
	glm::vec2			getVel() const { return m_state.live.vel; }
	float				getAttack() const { return m_state.live.attack; }
	//float				posx() const { return m_state.live.m_pos.x; }
	//float				posy() const { return m_state.live.m_pos.y; }

	//Sets
	void				setNext(Bullet* next) { m_state.next = next; }
};

}
