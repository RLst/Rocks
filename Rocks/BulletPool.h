#pragma once

//Prototypes
#include <glm\vec2.hpp>

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
	Bullet*					m_firstAvailable;
	int						m_bulletLife;
	float					m_bulletDamage;

	Bullet*					m_firstInUse;	//test
	Bullet*					m_nextInUse;	//test
	int						m_InUseIndex;	//test

	//Textures
	aie::Texture*			m_tex_bullet;

public:
	Bullet*					m_bullets;		//BAD!!!
	BulletPool(int poolsize);
	~BulletPool();

	void					request(glm::vec2 pos, glm::vec2 vel);
	void					restore(Bullet* bullet);

	void					update(float deltaTime);
	void					draw(aie::Renderer2D* renderer);

	//Get pointers to in use
	Bullet*					getNextInUse();	//Test
	float					getBulletDamage() { return m_bulletDamage; }

	//Getters and setters
	Bullet*					operator[](int index) const;	//?
	int						size() { return MAX_BULLETS; }
};

}
