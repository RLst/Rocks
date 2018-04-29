#pragma once
#include <glm/vec2.hpp>

namespace pkr {

class Bullet
{
	int m_framesLeft;
	glm::vec2 m_pos;
	glm::vec2 m_vel;

	union {
		//In use
		struct {
			glm::vec2 m_pos;
			glm::vec2 m_vel;
		} live;

		//Available
		Bullet* next;
	} m_state;

public:
	Bullet();
	~Bullet();

	void init(glm::vec2 pos, glm::vec2 vel);
	bool animate();
	bool inUse() const { return m_framesLeft > 0; }

	Bullet* getNext() const { return m_state.next; }
	void setNext(Bullet* next) { m_state.next = next; }
};

}
