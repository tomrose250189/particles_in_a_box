#ifndef VEC3_H
#define VEC3_H

#include <iostream>

class vec3
{
   public:
      vec3(double x = 0.0, double y = 0.0, double z = 0.0);
      ~vec3();
      vec3(const vec3& other);
      vec3& operator=(const vec3& other);
      double x() const;
      double& x();
      double y() const;
      double& y();
      double z() const;
      double& z();
      const vec3& operator+() const;
      vec3 operator+(const vec3& other) const;
      vec3& operator+=(const vec3& other);
      vec3 operator-() const;
      vec3 operator-(const vec3& other) const;
      vec3& operator-=(const vec3& other);
      double squared_length() const;
      double length() const;
      double dot(const vec3& other) const;
   protected:

   private:
      double e[3];
};

vec3 operator*(const vec3& t, double s);
vec3 operator*(double s, const vec3& t);
std::ostream& operator<<(std::ostream& os, const vec3& t);

#endif // VEC3_H
