#pragma once
#include "Entity.h"
class SpacePanicModel;
class Image;

class HoleEntity : public Entity
{
public:
	typedef enum
	{
		STAGE0,
		STAGE1,
		STAGE2,
		STAGE3
	} HoleState;
private:
	HoleState state;
public:
	HoleEntity(SpacePanicModel* model, Position position);

	Image* getImage() override;
	bool canGrow() const;
	bool canShrink() const;
	HoleState getStage() const;
	Image* stage1;
	Image* stage2;
	Image* stage3;
	
	
	bool grow();
	bool shrink();

	~HoleEntity() override;
};
