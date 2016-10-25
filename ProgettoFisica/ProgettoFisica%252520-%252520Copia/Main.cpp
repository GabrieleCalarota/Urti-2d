#include "MyLibrary.hpp"
#include "Spazio.hpp"
#include "Particella.hpp"
int main(){
  Spazio* s=new Spazio();
  srand(time(NULL));
  ofstream out("Output.txt", ios::out);
  
  //nome,x(m),y(m),raggio(m),velocità (m/s),angolo (°),massa (kg),colore (n random)
  Particella* p1=new Particella((char*)"A",2,15,2.0,1,-90,10,1);
  Particella* p2=new Particella((char*)"B",2,-10,2.0,7,0,20,7);
  Particella* p3=new Particella((char*)"C",10,1,2.0,3,1,8,42);
  Particella* p4=new Particella((char*)"D",-9,9,2,2,9,9,31);
  Particella* p5=new Particella((char*)"E",-3,-7,2,3,45,6,13);
  Particella* p6=new Particella((char*)"F",-25,-25,2,5,70,4,19);

  
  s->add_particella(p6);
  s->add_particella(p5);
  s->add_particella(p4);
  s->add_particella(p3);
  s->add_particella(p2);
  s->add_particella(p1);
  
  
  s->print_statistics(out);
  bool flag=s->check_system();
  
  if (flag){
 // while (!s->system_scattering())           Prende i dati, finchè 2 o più particelle si stanno avvicinando
    while (s->get_time()<50)
       s->avanza_tempo(out); }
  else
    cout<<"SISTEMA IMPOSSIBILE\n";


  out.close();
  return 0;
}
