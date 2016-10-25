#ifndef SPAZIO_HPP_
#define SPAZIO_HPP_
#include "Mylibrary.hpp"
class Particella;

struct Vec{ Particella* p;};

const double ERRORE=0.001;
const double MAX_PACE=1.0;
const int PROB_ANELASTICO=30;

class Spazio{
 protected:
  double time;
  double pace;
  Vec *a;
  int num_part;
  int dim_part;
 public:
  Spazio();
  void print_statistics(ofstream&);
  double get_time();
  void add_particella(Particella*);
  void sub_particella(Particella*);
  void dec_pace();
  void inc_pace();
  void avanza_tempo(ofstream&);
  bool system_scattering();
  bool controllo(Particella*,Particella*);
  bool controllo_system_escape(Particella*, Particella*);
  bool check_collision(Particella**,Particella**);
  bool in_collisione(Particella*,Particella*);
  void collision(Particella*,Particella*);
  bool check_system();
  void urto_elastico_generale(Particella*,Particella*);
  void urto_totalmente_anelastico(Particella*,Particella*);
};
#endif
