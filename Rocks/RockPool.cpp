#include "RockPool.h"
#include "Rock.h"
#include "Fighter.h"
#include "GameDefines.h"
#include <Texture.h>

namespace pkr {

//Default
RockPool::RockPool()
{
	//Initialise rocks
	MAX_ROCKS = 100;
	m_rocks = new Rock[MAX_ROCKS];

	//The first one is available
	m_firstAvailable = &m_rocks[0];

	//Each particle points to the next
	for (int i = 0; i <= MAX_ROCKS; ++i) {
		m_rocks[i].setNext(&m_rocks[i + 1]);
	}

	//The last one terminates the list
	m_rocks[MAX_ROCKS - 1].setNext(NULL);

	//Load rock textures
	m_rock_sml = new aie::Texture("..\bin\textures\rock_small.png");
	m_rock_med = new aie::Texture("..\bin\textures\rock_medium.png");
	m_rock_lge = new aie::Texture("..\bin\textures\rock_large.png");
}
//Overload
RockPool::RockPool(unsigned int PoolSize) : MAX_ROCKS(PoolSize = 100)
{
	//Initialise rocks
	m_rocks = new Rock[MAX_ROCKS];

	//Load rock textures
	m_rock_sml = new aie::Texture("..\bin\textures\rock_small.png");
	m_rock_med = new aie::Texture("..\bin\textures\rock_medium.png");
	m_rock_lge = new aie::Texture("..\bin\textures\rock_large.png");
}
//Deconstructor
RockPool::~RockPool()
{
	delete[] m_rocks;
	delete m_rock_sml;
	delete m_rock_med;
	delete m_rock_lge;
}

void RockPool::hurl(Fighter & player)
//Hurls a random sized rock with random direction and velocity at player
{
	//assert(m_firstAvailable != NULL);		//Make sure the pool isn't full
	if (m_firstAvailable == NULL) return;	//OR if the pool is full/don't have any objects available, then take no action

	//Initialise variables to be passed in
	glm::vec2 newPos;
	glm::vec2 newVec;
	glm::vec2 newAng;
	float newHealth;
	float newRadius;
	aie::Texture* newTex;

	//Set random rock type
	int rockSelect = Random(1, 3);

	//HEALTH and RADIUS
	newHealth = 50.0f * rockSelect;
	newRadius = 25.0f * rockSelect;

	//TEXTURE
	switch (Random(1, 3)) {
	case SML_ROCK:
		newTex = m_rock_sml;
		break;
	case MED_ROCK:
		newTex = m_rock_med;
		break;
	case LGE_ROCK:
		newTex = m_rock_lge;
		break;
	default:
		assert(false);
	}

	//POSITION: Set initial position at a random point offscreen
	switch (Random(1, 4))
	{
	case 1:	//Top
		newPos.y = SCREEN_HEIGHT;
		newPos.x = Random(0, SCREEN_WIDTH);
		break;
	case 2: //Bottom
		newPos.y = 0;
		newPos.x = newPos.x = Random(0, SCREEN_WIDTH);
		break;
	case 3: //Left
		newPos.x = 0;
		newPos.y = Random(0, SCREEN_HEIGHT);
		break;
	case 4: //Right
		newPos.x = SCREEN_WIDTH;
		newPos.y = Random(0, SCREEN_HEIGHT);
		break;
	}

	//VECTOR; roughly hurl towards player
	static int vecRough = 10;		//rough trajectory towards player
	newVec += (player.getPos() - newPos) + (float)Random(-vecRough, vecRough);

	//ANGLE; put a random spin on the rock
	static int angRough = 5;
	newAng.r = Random(angRough, angRough);		//rotational velocity
	newAng.g = Random(0, 360);	//real-time z angle

	//LAUNCH
	//Remove it from the available list
	Rock* newRock = m_firstAvailable;			//Set new rock ptr to first available
	m_firstAvailable = newRock->getNext();		//Set first available ptr to next avail
	newRock->init(newPos, newVec, newAng, newHealth, newRadius, newTex);
}

void RockPool::update(float deltaTime)
{
	for (int i = 0; i < MAX_ROCKS; ++i) {
		//If rock
		if (m_rocks[i].update(deltaTime)) {	//returns false if out of bounds
			//Add to the front of the list
			m_rocks[i].setNext(m_firstAvailable);
			m_firstAvailable = &m_rocks[i];
		}
		else {

		}
	}

}




}
