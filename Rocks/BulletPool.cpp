#include "BulletPool.h"
#include "Bullet.h"
#include <Texture.h>
#include <Renderer2D.h>
#include <cassert>

#include <iostream>		//For debugs


namespace pkr {

BulletPool::BulletPool(int PoolSize) : MAX_BULLETS(PoolSize)
{
	//Load textures
	m_tex_bullet = new aie::Texture("../bin/textures/bullet.png");
	m_tex_rock_sml = new aie::Texture("../bin/textures/rock_small.png");
	m_tex_rock_med = new aie::Texture("../bin/textures/rock_medium.png");
	m_tex_rock_lge = new aie::Texture("../bin/textures/rock_large.png");

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

BulletPool::~BulletPool()
{
	delete m_tex_bullet;
	delete m_tex_rock_sml;
	delete m_tex_rock_med;
	delete m_tex_rock_lge;
	delete[] m_bullets;
}

void BulletPool::request(glm::vec2 &pos, glm::vec2 &vel)
{
	//Make sure the pool isn't full
	//assert(m_firstAvailable != NULL);
	if (m_firstAvailable == NULL) return;

	//Remove it from the available list
	Bullet* newBullet = m_firstAvailable;
	m_firstAvailable = newBullet->getNext();

	newBullet->initialise(pos, vel);
}

void BulletPool::update(float dt)
{
	for (int i = 0; i < MAX_BULLETS; ++i) {
		if (m_bullets[i].advance(dt)) {
			//Add this bullet to the front of the list
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
			std::cout << "Drawing bullets" << std::endl;	//debug
			//Draw the bullet
			//renderer->drawSprite(m_tex_bullet, m_bullet_pool[i].getPos().x, m_bullet_pool[i].getPos().y);
			renderer->drawSprite(m_tex_bullet, m_bullets[i].getPos().x, m_bullets[i].getPos().y);	//OK

		}
	}
}

}
