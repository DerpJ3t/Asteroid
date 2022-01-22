#include "utils.hpp"


float Utils::clamp_frame(float dt)
{
	if (dt < 0.01f)
		return 0.01f;
	
	return dt;
}