#include "BulletPool.h"
#include "Bullet.h"
#include <cassert>

BulletPool::BulletPool(int poolSize) : POOL_SIZE(poolSize)
{
	//Load textures
	m_tex_small

	//Create bullet pool
	m_bullets = new Bullet[POOL_SIZE];

	//The first one is available
	m_firstAvailable = &m_bullets[0];

	//Each particle points to the next
	for (int i = 0; i < POOL_SIZE - 1; ++i) {
		m_bullets[i].setNext(&m_bullets[i - 1]);
	}

	//the last one terminates the list
	m_bullets[POOL_SIZE - 1].setNext(NULL);
}

BulletPool::~BulletPool()
{
}

void BulletPool::create(glm::vec2 pos, glm::vec2 vel, int lifetime)
{
	//Make sure the pool isn't full
	assert(m_firstAvailable != NULL);

	//Remove it from the available list
	Bullet* newBullet = m_firstAvailable;
	m_firstAvailable = newBullet->getNext;

	newBullet->init(pos, vel, lifetime);
}

void BulletPool::animate()
{
	for (int i = 0; i < POOL_SIZE; ++i) {
		if (m_bullets[i]->animate()) {
			//Add this bullet to the front of the list
			m_bullets[i]->setNext(m_firstAvailable);
			m_firstAvailable = m_bullets[i];
		}
	}
}
