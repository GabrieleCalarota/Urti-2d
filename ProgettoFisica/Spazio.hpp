#ifndef SPAZIO_HPP_
#define SPAZIO_HPP_
#include "Mylibrary.hpp"
//const int MAX=500;
class Particella;

struct list{ Particella* p;
             list* next;};
struct data_time{double t;
                 data_time* next;};

class Spazio{
 protected:
  double time;
  double pace;
  int cifre;
  list* head_p;
  data_time* head_t;
 public:
  Spazio();
  void print_statistics();
  void add_particella(Particella*);
  void add_particella(char*,double,double,double,double,double,double);
  void sub_particella(char*);
  void sub_particella(Particella*);
  void dec_pace();
  void inc_pace();
  void avanza_tempo();
  void arretra_tempo();
  void check_position();
  void print_position();
  void choose_collision(Particella*,Particella*);
  void urto_elastico(Particella*,Particella*); 
  void urto_anelastico(Particella*,Particella*);
  void urto_totalmente_anelastico(Particella*,Particella*);
};
#endif
