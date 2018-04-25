#pragma once
#include <glm\vec2.hpp>
//#include "Bullet.h"
//#include <Texture.h>


//Are these right? VVVV
class Bullet;

namespace aie {
	class Texture;
}

namespace glm {
	class vec2;
}

class BulletPool
{
	//static const int POOL_SIZE = 25;
	static int POOL_SIZE;
	//Bullet* m_bullets[POOL_SIZE];
	Bullet* m_bullets;
	Bullet* m_firstAvailable;

	aie::Texture m_tex_rocksml;
	aie::Texture


public:
	BulletPool(int poolSize);
	~BulletPool();

	void create(glm::vec2 pos, glm::vec2 vel, int lifetime);
	void animate();
};

