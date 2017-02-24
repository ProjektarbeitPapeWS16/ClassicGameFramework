#pragma once

#include "Entity.h"

class Entity_Pauline : public Entity
{
public:
private:
	unsigned long counter = 0;
public:
	Entity_Pauline(Position* position);
	Image* spritesheet;	// col1: stand, col2: pound chest, col3: throwbarrel down, col4: throwbarrel right
	//Image* getImage() override;
};