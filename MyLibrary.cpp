#include "MyLibrary.hpp"


double dist(double x1,double y1,double x2,double y2){
  double dx=x2-x1;
  double dy=y2-y1;
 return (sqrt((dx*dx)+(dy*dy)));}

double max(double a,double b){
   if (a>b)
     return a;
   else 
     return b;}
