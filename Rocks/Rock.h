#pragma once

#include <glm/vec2.hpp>
#include "GameDefines.h"
namespace aie {
	class Texture;
	class Renderer2D;
}

namespace pkr {
class Bullet;
class Fighter;

class Rock
{
private:
	union {
		//State while in use/unavailable
		struct {
			aie::Texture*	tex;		//Points to a texture stored in RockPool
			glm::vec2		pos;
			glm::vec2		vel;
			glm::vec2		ang;		//r = angular velocity, g = current rotation
			
			float			health;
			float			radius;
			float			attack;
			RockType		type;
		} live;

		//State while available
		Rock*				next;
	} m_state;

public:
	Rock();
	~Rock();

	//Core
	void					init(glm::vec2 pos, glm::vec2 vec, glm::vec2 ang, float health, float radius, float attack, aie::Texture* tex, RockType type);
	void					update(float deltaTime);		//Returns true rock goes out of bounds/screen
	void					draw(aie::Renderer2D* renderer);

	//Collisions
	bool					hasHitPlayer(Fighter * player);		//???returns true if rock hits player
	bool					hasBeenShot(Bullet * bullet);		//returns true if bullet hits rock

	void					wrapAroundScreen();

	//void					kill();
	bool					isAlive() const;

	float					getRadius() { return m_state.live.radius; }
	
	//Pool
	Rock*					getNext() const { return m_state.next; }
	void					setNext(Rock* next) { m_state.next = next; }

	//Vectors
	glm::vec2				getPos() { return m_state.live.pos; }
	glm::vec2				getVec() { return m_state.live.vel; }
	RockType				getType() { return m_state.live.type; }

	//Damage and health
	float					getHealth() { return m_state.live.health; }
	float					getAttack() { return m_state.live.attack; }
	void					takeDamage(float damage) { m_state.live.health -= damage; }
	
};

}
