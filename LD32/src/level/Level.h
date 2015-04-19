#pragma once

#include <iostream>
#include <vector>
#include <sparky.h>

#include "entity/Player.h"
#include "../layers/LevelLayer.h"
#include "projectiles/Projectile.h"
#include "objects/LevelObject.h"
#include "entity/enemies/Fighter.h"
#include "Portal.h"

class Entity;

class Level
{
	friend class Player;
	friend class Nuke;
private:
	std::vector<Entity*> m_Entities;
	LevelLayer* m_LevelLayer;

	std::vector<LevelObject*> m_Objects;
	std::vector<Projectile*> m_Projectiles;
	sparky::maths::vec2 m_Offset;
	Player* m_Player;
	int m_Ships;
	float m_PlatformOffsetX;
	unsigned int m_Difficulty;
	Portal* m_Portal;
	Nuke* m_Nuke;
	bool m_GameOver;
public:
	Level(unsigned int difficulty);
	~Level();
	void add(Entity* entity);
	void addObject(LevelObject* object);
	void addPlayer(Player* player);
	void addProjectile(Projectile* projectile);
	void update();
	void render();

	void start();
	void endGame();

	Player* getPlayer() const { return m_Player; }
	std::vector<LevelObject*> getObjects(const Entity* entity, float radius);
	std::vector<Projectile*> getProjectiles(const Entity* entity, float radius);

	inline unsigned int getDifficulty() const { return m_Difficulty; }
	inline const sparky::maths::vec2& getOffset() const { return m_Offset; }
private:
	void generatePlatforms(int count);
	void setOffset(const sparky::maths::vec2& offset) { m_Offset = offset; }
};