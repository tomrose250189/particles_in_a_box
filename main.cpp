#include <thread>
#include <conio.h>
#include <chrono>
#include <random>
#include <functional>

#include "update.h"

constexpr auto MAX_MASS = 0.001;
constexpr auto MAX_SIZE = 0.001;
constexpr auto MAX_SPEED = 1.0;

#ifdef __cplusplus
extern "C"
#endif
int main() {
   //Specify box and total number of particles
   vec3 box_size;
   int n;
   std::atomic<long> collisions(0), wall_collisions(0);
//   std::atomic<double> wall_impulse(0.0);
   double wall_impulse = 0.0;
   std::cout << "Type in box dimensions: ";
   std::cin >> box_size.x() >> box_size.y() >> box_size.z();
   std::cout << "\nType in number of particles: ";
   std::cin >> n;
   std::cout << "\n";
//   n = 2;

   double volume = box_size.x()*box_size.y()*box_size.z();
   std::cout << "\nBox Volume: " << volume << "\n\n";
   double surface_area = 2.0*(box_size.x()*box_size.y() + box_size.y()*box_size.z() + box_size.z()*box_size.x());

   std::vector<particle> ps;
   ps.reserve(n);
   //Choose particle positions, velocities etc. and put in vector ps
//   ps.push_back(particle(vec3(box_size.x()/2, box_size.y()/2, box_size.z()/2), vec3(0.0, 0.0, 0.0), 1.0, 0.01, true));
//   ps.push_back(particle(vec3(box_size.x()/2, box_size.y()/4, box_size.z()/2), vec3(0.0, box_size.y()/4, 0.0), 2.0, 0.01, true));
   int seed = std::chrono::system_clock::now().time_since_epoch().count();
   std::default_random_engine drg(seed);
   std::function<double()> rx, ry, rz, rm, rs, rv;
   rx = std::bind(std::uniform_real_distribution<double>(0.0, box_size.x()), drg);
   ry = std::bind(std::uniform_real_distribution<double>(0.0, box_size.y()), drg);
   rz = std::bind(std::uniform_real_distribution<double>(0.0, box_size.z()), drg);
   rm = std::bind(std::uniform_real_distribution<double>(0.0, MAX_MASS), drg);
   rs = std::bind(std::uniform_real_distribution<double>(0.0, MAX_SIZE), drg);
   rv = std::bind(std::uniform_real_distribution<double>(-MAX_SPEED, MAX_SPEED), drg);
   for(int i = 0; i < n; ++i){
//      ps.push_back(particle(vec3(rx(), ry(), rz()), vec3(rv(), rv(), rv()), rm(), rs(), true));
      ps.push_back(particle(vec3(rx(), ry(), rz()), vec3(rv(), rv(), rv()), MAX_MASS, MAX_SIZE, true));
   }

   std::array<std::list<particle*>, NOC> zones;
   //Put particles into relevant part of zone array
   setup_sys(zones, box_size.x(), ps);

   //Time increment system in a loop until keyboard press
   while(!kbhit()){
//   while(true){
      std::array<std::list<particle*>, NOC> left, right;
#if NOC > 1
      std::array<std::thread, NOC-1> thds;
      for(int i = 1; i < NOC; ++i){
         thds[i-1] = std::thread(update_sys, std::ref(zones[i]), i, std::ref(box_size), std::ref(collisions), std::ref(wall_collisions), std::ref(wall_impulse), std::ref(left[i]), std::ref(right[i]));
      }
#endif
      update_sys(zones[0], 0, box_size, collisions, wall_collisions, wall_impulse, left[0], right[0]);
#if NOC > 1
      for(int i = 1; i < NOC; ++i){
         thds[i-1].join();
      }
      zones[0].insert(zones[0].end(), left[1].begin(), left[1].end());
      for(int i = 1; i < NOC - 1; ++i){
         zones[i].insert(zones[i].end(), left[i+1].begin(), left[i+1].end());
         zones[i].insert(zones[i].end(), right[i-1].begin(), right[i-1].end());
      }
      zones[NOC-1].insert(zones[NOC-1].end(), right[NOC-2].begin(), right[NOC-2].end());
#endif

//      std::cout << collisions.load() << "   " << wall_collisions.load() << "   " << wall_impulse.load()/TIME_INCREMENT*surface_area << "\n";
      std::cout << collisions.load() << "   " << wall_collisions.load() << "   " << wall_impulse/double(TIME_INCREMENT)*surface_area << "\n";
//      wall_impulse.store(0.0);
      wall_impulse = 0.0;
      collisions.store(0);
      wall_collisions.store(0);
//      std::cin.get();
   }

   SDL_Init(0);

   while(true){}
   return 0;
}
