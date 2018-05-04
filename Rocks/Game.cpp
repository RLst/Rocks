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
	m_bullet_pool = new pkr::BulletPool(50);

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

	// input example
	aie::Input* input = aie::Input::getInstance();
	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	//TIMER
	m_timer += deltaTime;
	std::cout << m_timer << std::endl;	//DEBUG

	//PLAYER
	m_player->update(deltaTime);

	//CONTROL PLAYER FIRE
	if (input->isKeyDown(aie::INPUT_KEY_SPACE)) {

		//Delay bullets so they don't shoot too fast
		//if ((timer - lastFired) > fireRate)	//PSEUDO
		std::cout << "Last Fired = " << m_player->getLastFired() << std::endl;	//DEBUG
		if ((m_timer - m_player->getLastFired()) > m_player->getFireRate()) {
			m_bullet_pool->request(m_player->getGunPos(), m_player->getGunVel());
			m_player->setLastFired(m_timer);
		}
	}
	m_bullet_pool->update(deltaTime);

	//ROCKS
	//Insert random rocks
	static int spawnOccurence = 250;		//HIGHER is less
	if (Random(spawnOccurence) == spawnOccurence) {
		m_rock_pool->request(m_player);
	}
	m_rock_pool->update(deltaTime);

	//HANDLE COLLISIONS
	//Player < Rock
	HandleCollisionsWithPlayerAndRocks();

	//Bullet <> Rock
	HandleCollisionWithBulletsAndRocks();


}

void Game::draw() {

	// wipe the screen to the background colour
	clearScreen();
	// begin drawing sprites
	m_2dRenderer->begin();
	//////////////////////////////////////////////////////////////////////////////////////////

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

	/////////////////////////////////////////////////////////////////////////////////////////
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);
	// done drawing sprites
	m_2dRenderer->end();
}

void Game::HandleCollisionsWithPlayerAndRocks()
{
	//Go through rock pool and check if it collides with player
	m_rock_pool->HandlePlayerCollision(m_player);
	//m_rock_pool.HandleCollisionWithPlayer
	//for (int i = 0; i < m_rock_pool->size(); ++i) 
	//{
	//	if (m_rock_pool->checkPlayerCollision())
	//	for (int j = 0; j < m_)
	//}

}

void Game::HandleCollisionWithBulletsAndRocks()
{
	//Go through bullet pool and handle bullet collisions with rock pool
	m_rock_pool->HandleBulletCollision(m_bullet_pool);
	//for (int i = 0; i < m_bullet_pool->size(); ++i) 
	//{
	//}
	////Handle player collision
	//if (m_rock_pool->g    
	//	m_rocks   [i].hasHitPlayer(player)) {
	//	//Damage player
	//	player->takeDamage(m_rocks[i].getAttack());
	//	//Explosion
	//}
}
