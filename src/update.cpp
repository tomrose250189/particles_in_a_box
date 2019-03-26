#include <cmath>
#include <mutex>

#include "update.h"

bool collision_update(particle& p1, particle& p2){ //Elastic collisions
   vec3 d = p2.p() - p1.p();
   double total_sep = p1.s() + p2.s();
   #if TRUE_SEPERATION == 0
      if((d.x()>total_sep)||(d.y()>total_sep)||(d.z()>total_sep)){
         return false;
      }
      double dsq = d.squared_length();
   #else
      double dsq = d.squared_length();
      if(dsq > total_sep*total_sep){
         return false;
      }
   #endif // TRUE_SEPERATION
   double total_mass = p1.m() + p2.m();
   if(total_mass == 0.0){
      return true;
   }
   vec3 vdiff = p2.v() - p1.v();
   if(dsq == 0.0){
      d = -vdiff;
      dsq = vdiff.squared_length();
   }
   double dp_cond = d.dot(vdiff);
   if(dp_cond >= 0){
      return false;
   }
   vec3 common = (2.0*dp_cond/(dsq*total_mass))*d;
   p1.v() += p2.m()*common;
   p2.v() -= p1.m()*common;
   return true;
}

std::mutex mutex_wall_impulse;

void update_sys(std::list<particle*>& pl, int zn, const vec3& box_size, std::atomic<long>& collisions, std::atomic<long>& wall_collisions, double& wall_impulse, std::list<particle*>& left, std::list<particle*>& right){
   if(pl.empty()){
      return;
   }
   std::list<particle*>::iterator it, jt;
   for(it = pl.begin(); it != pl.end(); ++it){
      particle& pt = **it;
      // Wall collisions - Elastic
      if(zn == 0){
         if(pt.p().x() <= pt.s()){
            pt.v().x() *= -1.0;
//            wall_impulse.fetch_add(2.0*abs(pt.v().x())*pt.m());
            ++wall_collisions;
            std::lock_guard<std::mutex> lock(mutex_wall_impulse);
            wall_impulse += 2.0*fabs(pt.v().x())*pt.m();
         }
      }
      if(zn == NOC - 1){
         if(pt.p().x() >= box_size.x() - pt.s()){
            pt.v().x() *= -1.0;
//            wall_impulse.fetch_add(2.0*abs(pt.v().x())*pt.m());
            ++wall_collisions;
            std::lock_guard<std::mutex> lock(mutex_wall_impulse);
            wall_impulse += 2.0*fabs(pt.v().x())*pt.m();
         }
      }
      if((pt.p().y() <= pt.s())||(pt.p().y() >= box_size.y() - pt.s())){
         pt.v().y() *= -1.0;
//         wall_impulse.fetch_add(2.0*abs(pt.v().y())*pt.m());
         ++wall_collisions;
         std::lock_guard<std::mutex> lock(mutex_wall_impulse);
         wall_impulse += 2.0*fabs(pt.v().y())*pt.m();
      }
      if((pt.p().z() <= pt.s())||(pt.p().z() >= box_size.z() - pt.s())){
         pt.v().z() *= -1.0;
//         wall_impulse.fetch_add(2.0*abs(pt.v().z())*pt.m());
         ++wall_collisions;
         std::lock_guard<std::mutex> lock(mutex_wall_impulse);
         wall_impulse += 2.0*fabs(pt.v().z())*pt.m();
      }
      // Particle Collisions
      if(pt.i()){
         jt = it;
         for(++jt; jt != pl.end(); ++jt){
            particle& pu = **jt;
            if(pu.i()){
               if(collision_update(pt, pu)){
                  ++collisions;
               }
            }
         }
      }
   }
   // Update particle positions
   it = pl.begin();
   while(it != pl.end()){
      particle* pt = *it;
      pt->position_update(TIME_INCREMENT);
#if NOC > 1
      double l_b = double(zn)*box_size.x()/double(NOC);
      double r_b = double(zn + 1)*box_size.x()/double(NOC);
      if(zn != 0){
         if(pt->p().x() < l_b){
            left.push_back(pt);
            it = pl.erase(it);
            continue;
         }
      }
      else if(zn != NOC-1){
         if(pt->p().x() > r_b){
            right.push_back(pt);
            it = pl.erase(it);
            continue;
         }
      }
#endif
      ++it;
   }
   return;
}
