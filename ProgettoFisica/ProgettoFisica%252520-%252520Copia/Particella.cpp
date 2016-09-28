#include "Particella.hpp"


   Particella::Particella(char* n,double r1,double r2,double r,double speed,double a,double m,int c){
     strcpy(name,n);
     x=r1;
     y=r2;
     R=r;
     angle=(a/180.0)*PI;   
     vx=speed*cos(angle);
     vy=speed*sin(angle);
     mass=m;
     color=c;}

  void Particella::ingloba(Particella* p){
    strcat(name,p->get_name());
    mass+=p->get_mass();
    R=max(R,p->get_ray());
    delete p;}


  void Particella::save_position_and_speed(ofstream& out){
     out<<x<<"\t"<<y<<"\t"<<get_speed()<<"\t"<< (angle*180.0/PI)<<"\t"<<R*3.5<<"\t"<<color<<"\t\r\n";}

  void Particella::get_position(double* r1,double* r2){
      *r1=x;
      *r2=y;}

  double Particella::get_vx(){
    return vx;}

  double Particella::get_vy(){
    return vy;}

  double Particella::get_x(){return x;}

  double Particella::get_y(){return y;}

  double Particella::get_speed(){return (sqrt(vx*vx+vy*vy));}

  double Particella::get_mass(){return mass;}

  void Particella::change_mass(double m){
     mass=m;}

  void Particella::change_speed(double s){vx=s*cos(angle); vy=s*sin(angle);}

  void Particella::change_speed(double sx,double sy){
    vx=sx; vy=sy;}

  void Particella::change_direction(double a,bool t){    //Angolo in radianti (t=true), Angolo in gradi (t=false)
     if (t) 
        angle=a; 
     else 
        angle=(a/180.0)*PI;}

   void Particella::change_direction(double vx,double vy){
     double dir=0; 
     if (vx!=0){
        dir=atan(vy/vx);
     if ((vx<0)&&(vy>=0))
        dir+=PI;
     else 
       if ((vx<0)&&(vy<0))
         dir-=PI;}
       else 
          if (vy!=0){
            if (vy>0)
              dir=PI/2;
            else
              dir=-PI/2;}
            angle=dir;}

  double Particella::get_angle(){ 
    return angle;}

  char* Particella::get_name(){ 
    return name;}

  double Particella::get_ray(){
    return R;}


  void Particella::back_tracking(double t){
     x-=vx*t;
     y-=vy*t;}

  void Particella::avanza(double t){
     x+=vx*t;
     y+=vy*t;}
