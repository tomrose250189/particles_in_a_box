#ifndef SETUP_H
#define SETUP_H

#include <vector>
#include <array>
#include <list>

#include "particle.h"

#define NOC 4

void setup_sys(std::array<std::list<particle*>, NOC>& zones, double box_size_x, std::vector<particle>& ps);

#endif // SETUP_H
