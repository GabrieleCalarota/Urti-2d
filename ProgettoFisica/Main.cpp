#include "MyLibrary.hpp"
#include "Spazio.hpp"
#include "Particella.hpp"


int main(){
  Spazio* s=new Spazio;
  cout<<fixed;
  //cout<<PI<<endl;
  Particella* p1=new Particella((char*)"A",0,20,14.0,10,0,20);
  Particella* p2=new Particella((char*)"B",40,0,7.0,10,-180,20);
  s->add_particella(p2);
  s->add_particella(p1);
  char c;
  s->print_statistics();
  s->check_position();
  do{
  c=getch();
  switch (c){
   case 'a':{s->inc_pace(); break;}
   case 's':{s->avanza_tempo(); s->print_position();  break;}
   case 'd':{s->dec_pace(); break;}
   case 'b':{s->arretra_tempo(); s->print_position(); break;}
   case 'p':{s->print_statistics(); break;}}}
  while (c!='f');
  return 0;
}
