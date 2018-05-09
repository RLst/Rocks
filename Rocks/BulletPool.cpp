#include <cassert>
#include <Input.h>
#include "Bullet.h"
#include <Texture.h>
#include "BulletPool.h"
#include <Renderer2D.h>

#include <iostream>		//DEBUG


namespace pkr {
//Overloaded Constructor
BulletPool::BulletPool(int PoolSize) : MAX_BULLETS(PoolSize)
{
	//Set bullet settings
	m_bulletLifeTime = 1.0f;		//In float seconds
	m_bulletAttack = 25.0f;			//Amount of damage a bullet does

	//Load textures
	m_tex_bullet = new aie::Texture("../bin/textures/bullet.png");

	//Create bullet pool
	m_bullets = new Bullet[MAX_BULLETS];

	//The first one is available
	m_firstAvailable = &m_bullets[0];
	//Each particle points to the next
	for (int i = 0; i < MAX_BULLETS - 1; ++i) {
		m_bullets[i].setNext(&m_bullets[i + 1]);
	}
	//the last one terminates the list
	m_bullets[MAX_BULLETS - 1].setNext(NULL);

}
//Deconstructor
BulletPool::~BulletPool()
{
	delete[] m_bullets;
	delete m_tex_bullet;
}

void BulletPool::request(glm::vec2 pos, glm::vec2 vel)
{
	//Make sure the pool has objects to take
	assert(m_firstAvailable != NULL);			//All pool objects exhausted!!!
	//If pool is empty then do nothing
	//if (m_firstAvailable == NULL) return;

	//Bullet request granted; remove it from the available list
	Bullet* newBullet = m_firstAvailable;

	//Re-point firstAvailable to next free bullet
	m_firstAvailable = newBullet->getNext();

	//Initialise the bullet
	newBullet->init(pos, vel, m_bulletLifeTime, m_bulletAttack);
}

void BulletPool::restore(Bullet * bullet)
{
	bullet->setNext(m_firstAvailable);
	m_firstAvailable = bullet;
}

void BulletPool::restoreAll()
{
	//Kill all objects and hopefully the game::update() deals with the cleanup
	for (int i = 0; i < this->size() - 1; ++i)
	{
		m_bullets[i].kill();
	}
}

void BulletPool::update(float deltaTime)
{
	for (int i = 0; i < MAX_BULLETS; ++i) {
		//Update and control bullet deaths
		if (m_bullets[i].update(deltaTime) || !m_bullets[i].isAlive()) 
		{
			//Bullet is dead so put back into avail list
			restore(&m_bullets[i]);
		}
	}
}

void BulletPool::draw(aie::Renderer2D * renderer)
{
	for (int i = 0; i < MAX_BULLETS; ++i) {
		//If the bullet is alive then draw it
		if (m_bullets[i].isAlive()) {
			//Draw the bullet
			renderer->drawSprite(m_tex_bullet, m_bullets[i].getPos().x, m_bullets[i].getPos().y);
		}
	}
}

Bullet * BulletPool::operator[](int index) const
{
	return &m_bullets[index];
}

}
