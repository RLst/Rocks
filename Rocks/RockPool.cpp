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
}
