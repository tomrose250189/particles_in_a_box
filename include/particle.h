#ifndef PARTICLE_H
#define PARTICLE_H
#include "vec3.h"

class particle
{
   public:
      particle(vec3 p = vec3(), vec3 v = vec3(), double m = 0.01, double s = 0.01, bool interacts = true);
      void position_update(double t_s);
      vec3& p();
      vec3& v();
      double m();
      double s();
      bool i();
   protected:

   private:
      vec3 position;
      vec3 velocity;
      double mass;
      double size;
      bool interacts;
};

#endif // PARTICLE_H
