#pragma once
#include "Entity.h"


class Renderer;



class PlayerEntity : public Entity
{
	const int schrittweite = 20;
	Image* moveRight1;// = new Image(nullptr, "textures/player_run1_right.bmp", this, 200, 80, 0);
	Image* moveRight2;// = new Image(nullptr, "textures/player_run2_right.bmp", this, 200, 80, 0);
	Image* moveLeft1;// = new Image(nullptr, "textures/player_run1_left.bmp", this, 200, 80, 0);
	Image* moveLeft2;// = new Image(nullptr, "textures/player_run2_left.bmp", this, 200, 80, 0);
	Image* climb1;// = new Image(nullptr, "textures/player_climb1.bmp", this, 200, 80, 0);
	Image* climb2;// = new Image(nullptr, "textures/player_climb2.bmp", this, 200, 80, 0);
	Image* dig1;// = new Image(nullptr, "textur.bmp", this);
	Image* dig2;// = new Image(nullptr, "textur.bmp", this);
	Image* dead;// = new Image(nullptr, "textur.bmp", this);

public:
	enum Request
	{
		NONE,
		MOVE_RIGHT,
		MOVE_LEFT,
		MOVE_UP,
		MOVE_DOWN,
		DO_ACTION
	};

	enum PlayerState
	{
		MOVE_RIGHT_1,
		MOVE_RIGHT_2,
		MOVE_LEFT_1,
		MOVE_LEFT_2,
		CLIMB_1,
		CLIMB_2,
		DIG_1,
		DIG_2,
		DEAD
	};
private:
	PlayerState state = MOVE_RIGHT_1;
	Request lastRequest = NONE;
	Renderer* renderer;
public:

	PlayerEntity(Renderer* renderer);
	void request(Request request);
	void execute();
	Image* getImage() override;
};
