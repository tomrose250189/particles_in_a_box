#include "setup.h"

void setup_sys(std::array<std::list<particle*>, NOC>& zones, double box_size_x, std::vector<particle>& ps){
   double wzp[NOC];
   for(int i = 0; i < NOC; ++i){
      wzp[i] = double(i+1)*box_size_x/double(NOC);
   }
   int n = ps.size();
   for(int i = 0; i < n; ++i){
      double px = ps[i].p().x();
      for(int j = 0; j < NOC; ++j){
         if(px <= wzp[j]){
            zones[j].push_back(&(ps[i]));
            break;
         }
      }
   }
}
