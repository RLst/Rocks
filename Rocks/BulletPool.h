#pragma once

//Prototypes
#include <glm\vec2.hpp>

class Bullet;
namespace aie {
	class Texture;
}

class BulletPool
{
	//static const int POOL_SIZE = 25;
	//Bullet* m_bullets[POOL_SIZE];
	int							POOL_SIZE;
	Bullet*						m_bullet_pool;
	Bullet*						m_firstAvailable;

	//Textures
	aie::Texture*				m_tex_rock_sml;
	aie::Texture*				m_tex_rock_med;
	aie::Texture*				m_tex_rock_lge;

public:
	BulletPool(int poolSize);
	~BulletPool();

	void create(glm::vec2 pos, glm::vec2 vel);
	void animate();
};

