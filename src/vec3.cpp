#include <cmath>
#include "vec3.h"

vec3::vec3(double x, double y, double z) : e{x, y, z} {}
vec3::~vec3(){}
vec3::vec3(const vec3& other) : e{other.x(), other.y(), other.z()} {}
vec3& vec3::operator=(const vec3& rhs) {
   if (this == &rhs) return *this; // handle self assignment
   e[0] = rhs.x(); e[1] = rhs.y(); e[2] = rhs.z();
   return *this;
}
double vec3::x() const {
   return(e[0]);
}
double& vec3::x() {
   return(e[0]);
}
double vec3::y() const {
   return(e[1]);
}
double& vec3::y() {
   return(e[1]);
}
double vec3::z() const {
   return(e[2]);
}
double& vec3::z() {
   return(e[2]);
}
const vec3& vec3::operator+() const {
   return *this;
}
vec3 vec3::operator+(const vec3& other) const {
   return vec3(e[0] + other.x(), e[1] + other.y(), e[2] + other.z());
}
vec3& vec3::operator+=(const vec3& other){
   e[0] += other.x();
   e[1] += other.y();
   e[2] += other.z();
   return *this;
}
vec3 vec3::operator-() const {
   return vec3(-e[0], -e[1], -e[2]);
}
vec3 vec3::operator-(const vec3& other) const {
   return vec3(e[0] - other.x(), e[1] - other.y(), e[2] - other.z());
}
vec3& vec3::operator-=(const vec3& other){
   e[0] -= other.x();
   e[1] -= other.y();
   e[2] -= other.z();
   return *this;
}
double vec3::squared_length() const{
   return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
}
double vec3::length() const{
   return sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);
}
double vec3::dot(const vec3& other) const{
   return e[0]*other.x() + e[1]*other.y() + e[2]*other.z();
}
vec3 operator*(const vec3& t, double s){
   return(vec3(s*t.x(), s*t.y(), s*t.z()));
}
vec3 operator*(double s, const vec3& t){
   return(vec3(s*t.x(), s*t.y(), s*t.z()));
}
std::ostream& operator<<(std::ostream& os, const vec3& t){
   using std::operator<<;
   os << t.x() << " " << t.y() << " " << t.z();
   return(os);
}
