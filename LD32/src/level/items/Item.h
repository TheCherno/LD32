#pragma once

#include <sparky.h>

enum ItemType
{
	UNKNOWN, SHIELD
};

class Item
{
protected:
	unsigned int m_ID;
	std::string m_Name;
	sparky::graphics::Group* m_Sprite;
	ItemType m_Type;
public:
	Item(unsigned int id, std::string name)
		: m_ID(id), m_Name(name), m_Type(UNKNOWN)
	{ }

	virtual void use() = 0;
	virtual void update() = 0;
	virtual void render() = 0;

	inline const std::string& getName() const { return m_Name; }
	inline const ItemType getType() const { return m_Type; }
	inline sparky::graphics::Group* getSprite() const { return m_Sprite; }
};