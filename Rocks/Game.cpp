#include "Game.h"
#include "Font.h"
#include "Input.h"
#include <imgui.h>
#include "Texture.h"
#include "Fighter.h"
#include "RockPool.h"
#include "BulletPool.h"
#include "GameDefines.h"

#include <iostream>

Game::Game() {}

Game::~Game() {}

bool Game::startup() {
	
	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	////Setup the game
	m_timer = 0;

	//Space fighter (player)
	m_player = new pkr::Fighter;

	//Space fighter bullets
	m_bullet_pool = new pkr::BulletPool(200);

	//Enemy asteroids
	m_rock_pool = new pkr::RockPool(50);

	return true;
}

void Game::shutdown() {

	delete m_font;
	delete m_2dRenderer;

	delete m_player;
	delete m_bullet_pool;
	delete m_rock_pool;
}

void Game::update(float deltaTime) {

	aie::Input* input = aie::Input::getInstance();

	///////
	//TIMER
	///////
	m_timer += deltaTime;

	////////
	//PLAYER
	////////
	m_player->update(deltaTime);

	//SHOOTING
	if (input->wasKeyPressed(aie::INPUT_KEY_SPACE)) {

		//Delay bullets so they don't shoot too fast
		//if ((timer - lastFired) > fireRate)	//PSEUDO
		if ((m_timer - m_player->getTimeLastFired()) > m_player->getShootDelay()) {
			m_bullet_pool->request(m_player->getGunPos(), m_player->getGunVel());
			m_player->setLastFired(m_timer);
		}
	}

	/////////
	//BULLETS
	/////////
	m_bullet_pool->update(deltaTime);

	///////
	//ROCKS
	///////
	m_rock_pool->update(deltaTime);
	//Spawn rocks
	static float spawnMinTime = 1.0f;	//All time in seconds
	static float spawnMaxTime = 3.0f;
	static float nextSpawnTime = 2.0f;	//Initial delay before the first rock is spawned
	//Spawn rock according to next spawn time
	if (nextSpawnTime < m_timer) {
		m_rock_pool->request(m_player);
		//Set the spawn time for the next rock
		nextSpawnTime = m_timer + Random(spawnMinTime, spawnMaxTime);
	}

	///////////////////
	//HANDLE COLLISIONS
	///////////////////
	//Player < Rock
	m_rock_pool->HandlePlayerCollision(m_player);
	//Bullet <> Rock
	m_rock_pool->HandleBulletCollision(m_bullet_pool);

}

void Game::draw() {

	// wipe the screen to the background colour
	clearScreen();
	// begin drawing sprites
	m_2dRenderer->begin();
	///////
	//BEGIN
	///////

	////DRAW
	//Player
	m_player->draw(m_2dRenderer);
	//Bullets
	m_bullet_pool->draw(m_2dRenderer);
	//Rocks
	m_rock_pool->draw(m_2dRenderer);

	//DEBUGS
	//system("cls");
	//std::cout << m_player->getAng() << std::endl;
	//char dbg[32];
	//sprintf_s(dbg, 32, "m_player::m_ang = : %i", m_player->getAng());
	//m_2dRenderer->drawText(m_font, dbg, 0, 32);
	//m_2dRenderer->drawText(m_font, "Fighter::m_ang = " + m_player->getAng(), 0, 32);

	/////
	//END
	/////
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);
	// done drawing sprites
	m_2dRenderer->end();
}
