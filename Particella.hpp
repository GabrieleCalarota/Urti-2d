#ifndef PARTICELLA_HPP_
#define PARTICELLA_HPP_
#include "MyLibrary.hpp"

class Particella{
 protected:
  char name[20];
  double x;
  double y;
  double R;
  double vx;
  double vy;
  double angle; 
  double mass; 
  int color;
 public:
   Particella(char*,double,double,double,double,double,double,int);
   double get_x();
   double get_y();
   double get_mass();
   double get_ray();
   void change_mass(double);
   void change_speed(double);
   void change_speed(double,double);
   void change_direction(double,double);
   void change_direction(double,bool);
   void save_position_and_speed(ofstream&);
   char* get_name();
   double get_angle();
   double get_speed();
   void get_position(double*,double*);
   void avanza(double);
   void ingloba(Particella*);
   void back_tracking(double);
   double get_vx();
   double get_vy();
};
#endif
