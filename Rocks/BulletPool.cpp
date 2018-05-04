#include <Input.h>
#include "Bullet.h"
#include <Texture.h>
#include "BulletPool.h"
#include <Renderer2D.h>
#include <cassert>

#include <iostream>		//DEBUG


namespace pkr {
//Overloaded Constructor
BulletPool::BulletPool(int PoolSize) : MAX_BULLETS(PoolSize)
{
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
	m_bullets[MAX_BULLETS - 1].setNext(nullptr);
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
	//assert(m_firstAvailable != NULL);			//All pool objects exhausted!!!

	//If pool is empty then do nothing
	if (m_firstAvailable == NULL) return;

	//Delay bullets so they don't shoot too fast
	//static float minimumBulletDelay = 200.0f;	//200ms
	//if (getLastBulletTime() < minimumBulletDelay) return;

	//Bullet request granted; remove it from the available list
	Bullet* newBullet = m_firstAvailable;

	//Re-point firstAvailable to next free bullet
	m_firstAvailable = newBullet->getNext();

	//Initialise the bullet
	newBullet->init(pos, vel);
}

void BulletPool::update(float deltaTime)
{
	//aie::Input* input = aie::Input::getInstance();
	////Fire bullet
	//if (input->isKeyDown(aie::INPUT_KEY_SPACE)) {
	//	request(m_player->getGunPos(), m_player->getGunVel());
	//}

	for (int i = 0; i < MAX_BULLETS; ++i) {
		if (m_bullets[i].update(deltaTime)) {
			//If the bullet died

			//Add this bullet to the front of the availability list
			m_bullets[i].setNext(m_firstAvailable);
			m_firstAvailable = &m_bullets[i];
		}
	}
}

void BulletPool::draw(aie::Renderer2D * renderer)
{
	for (int i = 0; i < MAX_BULLETS; ++i) {
		//If the bullet is alive then draw it
		if (m_bullets[i].isActive()) {
			//Draw the bullet
			renderer->drawSprite(m_tex_bullet, m_bullets[i].getPos().x, m_bullets[i].getPos().y);
		}
	}
}

}
