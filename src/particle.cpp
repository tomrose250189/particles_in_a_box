#include "particle.h"

particle::particle(vec3 p, vec3 v, double m, double s, bool interacts) : position(p), velocity(v), mass(m), size(s), interacts(interacts) {}
void particle::position_update(double t_s){
   position += t_s*velocity;
}
vec3& particle::p(){
   return position;
}
vec3& particle::v(){
   return velocity;
}
double particle::m(){
   return mass;
}
double particle::s(){
   return size;
}
bool particle::i(){
   return interacts;
}
