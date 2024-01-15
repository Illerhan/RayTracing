#pragma once

#include <cmath>
#include <limits>
#include <memory>


using std::shared_ptr;
using std::make_shared;
using std::sqrt;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.14159265897932385;

inline double DegToRad(double degrees)
{
	return degrees * pi / 180.0;
}