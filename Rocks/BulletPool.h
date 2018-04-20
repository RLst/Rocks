#pragma once
#include <glm\vec2.hpp>
#include "Bullet.h"

//class Bullet;

class BulletPool
{
	static const int POOL_SIZE = 25;
	Bullet* m_bullets[POOL_SIZE];
	Bullet* m_firstAvailable;

public:
	BulletPool();
	~BulletPool();

	void create(glm::vec2 pos, glm::vec2 vel, int lifetime);
	void animate();
};

