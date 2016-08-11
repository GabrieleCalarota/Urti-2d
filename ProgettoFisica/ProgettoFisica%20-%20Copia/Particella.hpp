#ifndef PARTICELLA_HPP_
#define PARTICELLA_HPP_
#include "Mylibrary.hpp"
const double errore=0.0001;
class Particella{
 protected:
  char name[20];
  double x;
  double y;
  double R;
  //int z;
  double v;
  double angle; // +180° --> - 179°
  double mass; 
 public:
   Particella();
   Particella(char*,double,double,double);
   Particella(char*,double,double,double,double,double,double);
   double get_x();
   double get_y();
   double get_mass();
   double get_ray();
   void change_mass(double);
   void change_speed(double);
   void change_speed(double,double);
   void change_direction(double,double);
   void change_direction(double,bool);
   char* get_name();
   bool confronta(char*);
   void print_position();
   void print_speed();
   double get_angle();
   double get_speed();
   void get_position(double*,double*);
   void avanza(double);
   bool same_position(Particella*);
   bool miss_collision(Particella*);
   void ingloba(Particella*);
   void back_tracking(double);
   double get_vx();
   double get_vy();
};
#endif
