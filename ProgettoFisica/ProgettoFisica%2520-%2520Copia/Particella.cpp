#include "Particella.hpp"

   Particella::Particella(){
    strcpy(name,(char*)"A");
    x=0;
    y=0;
    //z=0;
    v=0;
    R=1.0;
    angle=0;
    mass=1;}

   Particella::Particella(char* n,double r1,double r2,double m){
    strcpy(name,n);
    x=r1;
    y=r2;
    R=1.0;
    v=0;
    angle=0;
    mass=m;
    }

   Particella::Particella(char* n,double r1,double r2,double r,double speed,double a,double m){
    strcpy(name,n);
    x=r1;
    y=r2;
    v=speed;
    R=r;
    angle=(a/180.0)*PI;
    mass=m;}

  bool Particella::confronta(char* n){
   return (strcmp(n,name)==0);}

  void Particella::ingloba(Particella* p){
    strcat(name,p->get_name());
    mass+=p->get_mass();
    R=max(R,p->get_ray());
    delete p;
   }

   void Particella::print_position(){
     cout<<"La particella "<<name<<" si trova in posizione ( "<<setprecision(2)<<x<<", "<<setprecision(2)<<y<<")\n";}

   void Particella::print_speed(){
     if (v>0.01)
     cout<<"La particella "<<name<<" si muove alla velocità di "<< setprecision(2)<<v<<" m/s, con un angolo di "<<setprecision(2)<< (angle*180.0/PI)<<"° rispetto all'asse +x\n";
    else
      cout<<"La particella "<<name<<" è ferma in posizione ( "<<setprecision(2)<<x<<", "<<setprecision(2)<<y<<")\n";}

   void Particella::get_position(double* r1,double* r2){
      *r1=x;
      *r2=y;}
   double Particella::get_vx(){
    return ((cos(angle)*v));}

   double Particella::get_vy(){
    return ((sin(angle)*v));}

  double Particella::get_x(){return x;}
  double Particella::get_y(){return y;}

  double Particella::get_speed(){return v;}

  double Particella::get_mass(){return mass;}
   void Particella::change_mass(double m){
     mass=m;}
   void Particella::change_speed(double s){v=s;}
   void Particella::change_speed(double vx,double vy){
    v=sqrt((vx*vx)+(vy*vy));}
   void Particella::change_direction(double a,bool t){if (t) angle=a; else angle=(a/180.0)*PI;}
   void Particella::change_direction(double vx,double vy){
   double dir=0; 
   if (vx!=0){
    dir=atan(vy/vx);
    if ((vx<0)&&(vy>=0))
     dir+=PI;
    else if ((vx<0)&&(vy<0))
     dir-=PI;}
    else if (vy!=0){
     if (vy>0)
       dir=PI/2;
     else
       dir=-PI/2;}
     angle=dir; }

  double Particella::get_angle(){ return angle;}

  char* Particella::get_name(){ return name;}
  double Particella::get_ray(){return R;}

  bool Particella::miss_collision(Particella* p){
   double distance=sqrt(pow((x-(p->get_x())),2)+pow((y-(p->get_y())),2));
   double due_r=R+p->get_ray();
   return ((distance-due_r)<0);
   }


  bool Particella::same_position(Particella* p){
   double distance=sqrt(pow((x-(p->get_x())),2)+pow((y-(p->get_y())),2));
   double due_r=R+p->get_ray();
   return (abs(distance-due_r)<errore); }


   void Particella::back_tracking(double t){
    double r1= get_vx();
    double r2= get_vy();
     x-=r1*t;
     y-=r2*t;}
   void Particella::avanza(double t){
     double r1= get_vx();
     double r2= get_vy();
     x+=r1*t;
     y+=r2*t;}
