#include "HardBrick.h"


HardBrick::HardBrick()
{
	rows = 0;
	columns = 0;
	bricks = NULL;
	hp = 2;
}


HardBrick::~HardBrick()
{
	if (bricks != NULL)
		delete bricks;
}
