#include "Rock.h"
#include "Fighter.h"
#include <Texture.h>
#include <Renderer2D.h>
#include "RockPool.h"
#include "GameDefines.h"

#include <iostream>

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
//Hurls a random sized rock with random direction and velocity at player
{
	//assert(m_firstAvailable != NULL);		//Make sure the pool isn't full
	if (m_firstAvailable == NULL) return;	//OR if the pool is full/don't have any objects available, then take no action

	//INIT AND NULLIFY variables to be passed in
	glm::vec2		newPos = { 0, 0 };
	glm::vec2		newVec = { 0,0 };			//****** NOT DOING THIS TRIGGERED THE MAJOR HEADACHE!!!!
	glm::vec2		newAng = { 0,0 };
	float			newHealth = 0.0f;
	float			newRadius = 0.0f;
	aie::Texture*	newTex = nullptr;

	//ROCK TYPE
	int rockType = Random(1, 3);

	//HEALTH and RADIUS
	newHealth = 50.0f * rockType;
	newRadius = 25.0f * rockType;

	//TEXTURE
	switch (rockType) {
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

	//POSITION: Set initial position at a random point offscreen
	switch (Random(1, 4))
	{
	case 1:	//Top
		newPos.y = SCREEN_HEIGHT;
		newPos.x = (float)Random(0, SCREEN_WIDTH);
		break;
	case 2: //Bottom
		newPos.y = 0;
		newPos.x = newPos.x = (float)Random(0, SCREEN_WIDTH);
		break;
	case 3: //Left
		newPos.x = 0;
		newPos.y = (float)Random(0, SCREEN_HEIGHT);
		break;
	case 4: //Right
		newPos.x = SCREEN_WIDTH;
		newPos.y = (float)Random(0, SCREEN_HEIGHT);
		break;
	}
	//newPos = { 250.0f, 250.0f };	//debug

	//VECTOR; roughly hurl towards player
	static int vecRough = 100;		//rough trajectory towards player
	//glm::vec2 tempVec = { 50, 50 };	//debug
	//newVec = tempVec;
	newVec += (player->getTargetPos() - newPos) + (float)Random(-vecRough, vecRough);

	//ANGLE; put a random spin on the rock
	static int angRough = 10;
	newAng.r = (float)Random(-angRough, angRough);		//rotational velocity
	newAng.g = (float)Random(0, 360);	//real-time z angle

	//LAUNCH
	//Remove it from the available list
	Rock* newRock = m_firstAvailable;			//Set new rock ptr to first available

	m_firstAvailable = newRock->getNext();		//Set first available ptr to next avail

	std::cout << "newRock->init()" << std::endl;	//DEBUG
	newRock->init(newPos, newVec, newAng, newHealth, newRadius, newTex);
}

void RockPool::update(float deltaTime)
{
	for (int i = 0; i < MAX_ROCKS; ++i) {
		if (m_rocks[i].update(deltaTime)) {
			//If the rock gets killed

			//Add to the front of the list
			m_rocks[i].setNext(m_firstAvailable);
			m_firstAvailable = &m_rocks[i];
		}
		//else {
		//	//?
		//}
	}

}

void RockPool::draw(aie::Renderer2D * renderer)
{
	for (int i = 0; i < MAX_ROCKS; ++i) {
		//If the rock is active then draw it (including it's rotation)
		if (m_rocks[i].isActive()) {
			std::cout << "Rock being drawn" << std::endl;
			//renderer->drawSprite(m_tex_rock_sml, m_rocks[i].getPos().x, m_rocks[i].getPos().y); //debug
			m_rocks[i].draw(renderer);
		}
	}

}

}
