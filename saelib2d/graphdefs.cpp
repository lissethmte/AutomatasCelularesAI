#include "graphdefs.h"

bool operator==(const sRGB& c1, const sRGB& c2)
{
	return (c1.r == c2.r &&
		c1.g == c2.g && c1.b == c2.b);
}
