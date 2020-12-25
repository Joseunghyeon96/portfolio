#include "stdafx.h"
#include <time.h>

float randomRange(float min, float max)
{
	return (float)(rand() % (int)(max - min + 1)) + min;
}
