#pragma once

#include <pkr\math\Vector2.h>
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
			aie::Texture*	m_tex;		//Points to a texture stored in RockPool
			Vector2			m_pos;
			Vector2			m_vel;
			Vector2			m_ang;		//r = angular velocity, g = current rotation
			
			float			m_health;
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
	void					init(Vector2 pos, Vector2 vec, Vector2 ang, float health, float radius, float attack, aie::Texture* tex, RockType type);
	void					update(float deltaTime, float &baseSpeed);		//Returns true rock goes out of bounds/screen
	void					draw(aie::Renderer2D* renderer);

	//Collisions
	bool					hasHitPlayer(Fighter * player);		//returns true if rock hits player
	bool					hasBeenShot(Bullet * bullet);		//returns true if bullet hits rock

	void					wrapAroundScreen();

	bool					isAlive() const;
	void					kill() { m_state.live.m_health = 0; }

	float					getRadius() { return m_state.live.radius; }
	
	//Pool
	Rock*					getNext() const { return m_state.next; }
	void					setNext(Rock* next) { m_state.next = next; }

	//Vectors
	Vector2				getPos() { return m_state.live.m_pos; }
	Vector2				getVec() { return m_state.live.m_vel; }
	RockType				getType() { return m_state.live.type; }

	//Damage and health
	float					getHealth() { return m_state.live.m_health; }
	float					getAttack() { return m_state.live.attack; }
	void					takeDamage(float damage) { m_state.live.m_health -= damage; }
	
};

}
