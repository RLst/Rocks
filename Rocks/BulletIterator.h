#pragma once
#include "Bullet.h"

namespace pkr
{
//class Bullet;

class BulletIterator 
{
	Bullet* m_bullet = nullptr;

public:
	BulletIterator() {}

	BulletIterator(Bullet * bullet)
	{
		m_bullet = bullet;
	}

	~BulletIterator() {}

	bool operator == (const BulletIterator& other) {
		return this->m_bullet == other.m_bullet;
	}

	bool operator != (const BulletIterator& other) {
		return m_bullet != other.m_bullet;
	}

	BulletIterator operator ++ () {
		m_bullet = m_bullet->getNext();
		return *this;
	}

	Bullet & operator * () {
		return *m_bullet->getNext();
	}

	Bullet* get() {	//Returns the bullet?
		return m_bullet;
	}


};

}