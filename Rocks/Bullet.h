#pragma once
#include <glm/vec2.hpp>

namespace pkr {

class Bullet
{
	bool				m_active;
	union {
		//In use
		struct {
			glm::vec2	m_pos;
			glm::vec2	m_vel;
		} live;

		//Available
		Bullet*			next;
	} m_state;

public:
	Bullet();
	~Bullet();

	//Core
	void initialise(glm::vec2 &pos, glm::vec2 &vel);
	bool advance(float deltaTime);

	//Active
	bool isActive() const { return m_active == true; }
	void kill() { m_active = false; }

	//Checks
	bool outOfBounds();

	//Gets
	Bullet* getNext() const { return m_state.next; }
	//aie::Texture getTex() const { return m_state.live.}
	glm::vec2 getPos() const { return m_state.live.m_pos; }
	glm::vec2 getVel() const { return m_state.live.m_vel; }
	float posx() const { return m_state.live.m_pos.x; }
	float posy() const { return m_state.live.m_pos.y; }


	//Sets
	void setNext(Bullet* next) { m_state.next = next; }
};

}
