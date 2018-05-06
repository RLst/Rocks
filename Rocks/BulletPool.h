#pragma once
#include <glm\vec2.hpp>
#include "BulletIterator.h"

//Prototypes
namespace aie {
	class Texture;
	class Renderer2D;
}

namespace pkr {
	class Bullet;

class BulletPool
{
	//static const int POOL_SIZE = 25;
	//Bullet* m_bullets[POOL_SIZE];
	int						MAX_BULLETS;
	float					m_bulletLifeTime;
	float					m_bulletAttack;

	Bullet*					m_firstAvailable;

	//Textures
	aie::Texture*			m_tex_bullet;

public:
	BulletPool(int poolsize);
	~BulletPool();

	Bullet*					m_bullets;		//BAD!!! THIS SHOULD BE PRIVATE!!!
	BulletIterator			begin() { return BulletIterator(m_firstAvailable); }
	BulletIterator			end() { return BulletIterator(); }

	void					request(glm::vec2 pos, glm::vec2 vel);
	void					restore(Bullet* bullet);

	void					update(float deltaTime);
	void					draw(aie::Renderer2D* renderer);

	//Get pointers to in use
	//Bullet*					getNextInUse();	//Test
	float					getBulletDamage() { return m_bulletAttack; }

	//Getters and setters
	Bullet*					operator[](int index) const;	//?
	int						size() { return MAX_BULLETS; }
};

}
