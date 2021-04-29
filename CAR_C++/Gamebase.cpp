#include "Gamebase.h"

int UpdateGameTimeAndScore(int& timeofgame, int& speed, int& score)
{
    if (timeofgame == TIME_MAX)
	{
		speed += SPEED_INCREASEMENT;
	}

	if (timeofgame > TIME_MAX)
	{
		timeofgame = 0;
	}
	if (timeofgame % 5 == 0)
	{
		score += SCORE_INCREASEMENT;
	}

	timeofgame += TIME_INCREASEMENT;

	return timeofgame;
}
