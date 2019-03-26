#ifndef UPDATE_H
#define UPDATE_H

#include <atomic>

#include "setup.h"

#define TIME_INCREMENT 0.001
#define TRUE_SEPERATION 0

bool update_collision(particle& pt, particle& pu);
//void update_sys(std::list<particle*>& pl, int zn, const vec3& box_size, std::atomic<long>& collisions, std::atomic<long>& wall_collisions, std::atomic<double>& wall_impulse, std::list<particle*>& left, std::list<particle*>& right);
void update_sys(std::list<particle*>& pl, int zn, const vec3& box_size, std::atomic<long>& collisions, std::atomic<long>& wall_collisions, double& wall_impulse, std::list<particle*>& left, std::list<particle*>& right);

#endif // UPDATE_H
