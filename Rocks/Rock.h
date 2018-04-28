#pragma once

#include <glm/vec2.hpp>
#include "GameDefines.h"
namespace aie {
	class Texture;
}

namespace pkr {
class Bullet;
class Player;

//struct RockModel {
//	float m_health;
//};
//class RockModel {
//	RockType			m_type;
//	aie::Texture*		m_tex;
//	float				m_hit_radius;
//};

class Rock
{
private:
	bool					m_alive;
	union {
		//State while in use/unavailable
		struct {
			glm::vec2		pos;
			glm::vec2		vec;
			glm::vec2		ang;		//r = current rotation, g = angular velocity
			float			health;
			float			radius;
			aie::Texture*	tex;		//Points to a texture stored in RockPool
		} live;

		//State while available
		Rock*				next;
	} m_state;

	//glm::vec2			m_pos;
	//glm::vec2			m_vector;	
	//float				m_angle;
	//unsigned short		m_rock_size;	//1 = small, 2 = medium, 3 = large
	//aie::Texture*		m_tex;			//Texture changes with the size
	//float				m_radius;		//For collision

public:
	Rock();
	~Rock();

	Rock* getNext() const { return m_state.next; }
	void setNext(Rock* next) { m_state.next = next; }

	void init(
		glm::vec2 pos, glm::vec2 vec,
		glm::vec2 ang, float health, 
		float radius, aie::Texture* tex);

	bool update(float deltaTime);		//Returns true rock goes out of bounds/screen

	void kill();
	bool isAlive() const { return m_alive == true; }

	bool hasBeenShot(Bullet &bullet);		//returns true if bullet hits rock
	bool hasHitPlayer(Player &player);		//???returns true if rock hits player
};

}
