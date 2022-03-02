#include "utils.hpp"


float Utils::clamp_frame(float fps)
{
	if (fps > 100.0f)
		fps = 100.0f;
	return fps;
}