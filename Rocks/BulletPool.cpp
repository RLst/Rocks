#include "BulletPool.h"
#include "Bullet.h"
#include <Texture.h>
#include <cassert>

BulletPool::BulletPool(int PoolSize) : POOL_SIZE(PoolSize)
{
	//Load rock textures
	m_tex_rock_sml = new aie::Texture("../bin/textures/rock_small.png");
	m_tex_rock_med = new aie::Texture("../bin/textures/rock_medium.png");
	m_tex_rock_lge = new aie::Texture("../bin/textures/rock_large.png");

	//Create bullet pool
	m_bullet_pool = new Bullet[POOL_SIZE];

	//The first one is available
	m_firstAvailable = &m_bullet_pool[0];

	//Each particle points to the next
	for (int i = 0; i < POOL_SIZE - 1; ++i) {
		m_bullet_pool[i].setNext(&m_bullet_pool[i - 1]);
	}

	//the last one terminates the list
	m_bullet_pool[POOL_SIZE - 1].setNext(NULL);
}

BulletPool::~BulletPool()
{
}

void BulletPool::create(glm::vec2 pos, glm::vec2 vel)
{
	//Make sure the pool isn't full
	assert(m_firstAvailable != NULL);

	//Remove it from the available list
	Bullet* newBullet = m_firstAvailable;
	m_firstAvailable = newBullet->getNext;

	newBullet->init(pos, vel);
}

void BulletPool::animate()
{
	for (int i = 0; i < POOL_SIZE; ++i) {
		if (m_bullet_pool[i].animate()) {
			//Add this bullet to the front of the list
			m_bullet_pool[i].setNext(m_firstAvailable);
			m_firstAvailable = &m_bullet_pool[i];
		}
	}
}
