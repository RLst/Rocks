#include "Rock.h"
#include "Fighter.h"
#include <Texture.h>
#include <Renderer2D.h>
#include "RockPool.h"
#include "GameDefines.h"
#include "Bullet.h"
#include "BulletPool.h"

#include <iostream>		//For Debuggin

namespace pkr {

//Default
//RockPool::RockPool()
//{
//	//Load rock textures
//	m_tex_rock_sml = new aie::Texture("../bin/textures/rock_small.png");
//	m_tex_rock_med = new aie::Texture("../bin/textures/rock_medium.png");
//	m_tex_rock_lge = new aie::Texture("../bin/textures/rock_large.png");
//
//	//Initialise rocks
//	MAX_ROCKS = 100;	//Default of 100
//	m_rocks = new Rock[MAX_ROCKS];		
//
//	////Set up the availability lists
//	//The first one is available
//	m_firstAvailable = &m_rocks[0];
//
//	//Each particle points to the next
//	for (int i = 0; i < MAX_ROCKS - 1; ++i) {
//		m_rocks[i].setNext(&m_rocks[i + 1]);
//	}
//
//	//The last one terminates the list
//	m_rocks[MAX_ROCKS - 1].setNext(NULL);
//
//}
//Overload
RockPool::RockPool(int PoolSize) : MAX_ROCKS(PoolSize)
{
	//Load rock textures
	m_tex_rock_sml = new aie::Texture("../bin/textures/rock_small.png");
	m_tex_rock_med = new aie::Texture("../bin/textures/rock_medium.png");
	m_tex_rock_lge = new aie::Texture("../bin/textures/rock_large.png");

	//Create rock pool
	m_rocks = new Rock[MAX_ROCKS];

	////Set up the availability lists
	//The first one is available
	m_firstAvailable = &m_rocks[0];

	//Each particle points to the next
	for (int i = 0; i < MAX_ROCKS - 1; ++i) {
		m_rocks[i].setNext(&m_rocks[i + 1]);
	}

	//The last one terminates the list
	m_rocks[MAX_ROCKS - 1].setNext(nullptr);

}
//Deconstructor
RockPool::~RockPool()
{
	delete[] m_rocks;
	delete m_tex_rock_sml;
	delete m_tex_rock_med;
	delete m_tex_rock_lge;
}

void RockPool::request(Fighter * player)
{
	//assert(m_firstAvailable != NULL);		//Make sure the pool isn't full
	if (m_firstAvailable == NULL) return;	//OR if the pool is full/don't have any objects available, then take no action

	//////////////////
	//INIT AND NULLIFY variables to be passed in
	//////////////////
	glm::vec2		newPos = { 0, 0 };
	glm::vec2		newVec = { 0,0 };			//****** NOT DOING THIS TRIGGERED THE MAJOR HEADACHE!!!!
	glm::vec2		newAng = { 0,0 };
	float			newHealth = 0.0f;
	float			newRadius = 0.0f;
	float			newAttack = 0.0f;
	aie::Texture*	newTex = nullptr;

	///////////
	//ROCK SIZE
	//Initially set the rock size. All other parameters are worked off this
	///////////
	int RockSize = Random(1, 3);

	///////////////////////////
	//HEALTH, RADIUS and ATTACK
	///////////////////////////
	newHealth = 25.0f * RockSize;
	newRadius = 23.0f * RockSize;
	newAttack = 10.0f * RockSize;	//Large kills instantly, Med kills in 2 hits, Sml kills in 3 hits

	/////////
	//TEXTURE
	//Select texture according to rock size
	/////////
	switch (RockSize) {
	case SML_ROCK:
		newTex = m_tex_rock_sml;
		break;
	case MED_ROCK:
		newTex = m_tex_rock_med;
		break;
	case LGE_ROCK:
		newTex = m_tex_rock_lge;
		break;
	}

	//////////
	//POSITION
	//Set initial position at a random point around the edgeo of the screen
	//////////
	static float padding = 50;
	switch (Random(1, 4))
	{
	case 1:	//Top
		newPos.y = SCREEN_HEIGHT + padding;
		newPos.x = (float)Random(0, SCREEN_WIDTH);
		break;
	case 2: //Bottom
		newPos.y = 0 - padding;
		newPos.x = newPos.x = (float)Random(0, SCREEN_WIDTH);
		break;
	case 3: //Left
		newPos.x = 0 - padding;
		newPos.y = (float)Random(0, SCREEN_HEIGHT);
		break;
	case 4: //Right
		newPos.x = SCREEN_WIDTH + padding;
		newPos.y = (float)Random(0, SCREEN_HEIGHT);
		break;
	}

	/////////
	//VECTOR
	//Add velocity to the rock
	////////

	//Aim imprecisely at player
	static int aimInaccuracy = 50;			//HIGHER is more inaccurate
	newVec = (player->getPos() - newPos) + (float)Random(-aimInaccuracy, aimInaccuracy);

	//Normalize
	normalise(newVec);

	//Speed
	static float maxRockSpeed = 200.0f;
	newVec *= Random(0.0f, maxRockSpeed);

	////////
	//ANGLE
	//Random spin on the rock
	////////
	static int angRough = 6;
	newAng.r = (float)Random(-angRough, angRough);		//rotational velocity
	newAng.g = (float)Random(0, 360);	//real-time z angle

	////////
	//LAUNCH
	//Remove it from the available list
	////////
	Rock* newRock = m_firstAvailable;			//Set new rock ptr to first available
	m_firstAvailable = newRock->getNext();		//Set first available ptr to next avail
	newRock->init(newPos, newVec, newAng, newHealth, newRadius, newAttack, newTex);
}

void RockPool::restore(Rock * rock)
{
	//rock->kill();	//DEBUG
	rock->setNext(m_firstAvailable);
	m_firstAvailable = rock;
}

void RockPool::HandlePlayerCollision(Fighter * player)
{
	for (int i = 0; i < this->size(); ++i) {
		//Check if rock is alive
		if (m_rocks[i].isAlive()) {
			//If player is hit then deals damage to player
			if (m_rocks[i].hasHitPlayer(player)) {
				player->takeDamage(m_rocks[i].getAttack());
			}
		}
	}
}

void RockPool::HandleBulletCollision(BulletPool * bullets)
{
	//Get each active rock from the rock pool
	for (int i = 0; i < this->size(); ++i)
	{
		if (m_rocks[i].isAlive()) {

			//For each active bullet check if it hits a rock
			for (int j = 0; j < bullets->size(); ++j)
			{
				//Check if bullet is alive
				if (bullets->m_bullets[j].isAlive()) {
					//If bullet hits rock...
					if (m_rocks[i].hasBeenShot(&bullets->m_bullets[j])) {
						std::cout << "Rock shot!!!" << std::endl;
						//..deals damage to rock
						//m_rocks[i].takeDamage(bullets->getBulletDamage());
						//..bullet dies too
						//bullets->m_bullets[i].kill();
					}
				}
			}
		}
	}
}

void RockPool::update(float deltaTime)
{
	for (int i = 0; i < MAX_ROCKS; ++i) {
		
		//Handle rock life
		if (!m_rocks[i].isAlive()) {
			//Rock life is too low; Restore back to pool
			m_rocks[i].setNext(m_firstAvailable);
			m_firstAvailable = &m_rocks[i];
		}

		//Draw the rock
		m_rocks[i].update(deltaTime);

		//Wrap the rock if it goes off screen
		m_rocks[i].wrapAroundScreen();
	}

}

void RockPool::draw(aie::Renderer2D * renderer)
{
	for (int i = 0; i < MAX_ROCKS; ++i) {
		//If the rock is active then draw it (including it's rotation)
		if (m_rocks[i].isAlive()) {
			m_rocks[i].draw(renderer);
		}
	}
}

}
