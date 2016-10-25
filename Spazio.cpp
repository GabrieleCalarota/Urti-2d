  #include "Spazio.hpp"
  #include "Particella.hpp"

  Spazio::Spazio(){
    time=0;
    pace=0.1;
    num_part=0;
    dim_part=6;
    a=new Vec[dim_part];
    for (int i=0;i<dim_part;i++)
      a[i].p=NULL;}

  void Spazio::print_statistics(ofstream& out){
    for (int i=0;i<num_part;i++)
       a[i].p->save_position_and_speed(out);
    out<<"\r\n\r\n";}                           //STAT_BLOCKS (GNUPLOT): divide un blocco dall'altro per refreshare il grafico

  void Spazio::add_particella(Particella* p){
    if (num_part<dim_part){
      a[num_part].p=p;
      num_part++;}
    else{
      dim_part*=2;
      Vec* b=new Vec[dim_part];
      for (int i=0;i<num_part;i++)
         b[i]=a[i];
      b[num_part].p=p;
      num_part++;
      for (int j=num_part;j<dim_part;j++)
         b[j].p=NULL;
      delete a;
      a=new Vec[dim_part];
      for (int i=0;i<dim_part;i++)
        a[i]=b[i];
      delete b;}}

 
  void Spazio::sub_particella(Particella* k){
    int i=-1;
    while ((i<num_part)&&(a[i+1].p!=k))
       i++;
    for (int j=i+1;j<(num_part-1);j++)
      a[j]=a[j+1];
    num_part--;
    a[num_part].p=NULL;}


  void Spazio::dec_pace(){
   pace=pace/10;}


  void Spazio::inc_pace(){
    pace=pace*10;}

  bool Spazio::system_scattering(){
    bool flag=true;
    for (int i=0;(i<num_part)&&(flag);i++)
      for (int j=i+1; (j<num_part)&&(flag);j++)
        flag=controllo_system_escape(a[i].p,a[j].p);
    return flag;}

  bool Spazio::controllo_system_escape(Particella* p1, Particella* p2){
     double D=dist(p1->get_x(),p1->get_y(),p2->get_x(),p2->get_y());
     p1->avanza(pace);
     p2->avanza(pace);
     double new_D=dist(p1->get_x(),p1->get_y(),p2->get_x(),p2->get_y());
     p1->back_tracking(pace);
     p2->back_tracking(pace);
     return (new_D>D);}

  bool Spazio::controllo(Particella* p1,Particella* p2){
    double old_dx=p2->get_x()-p1->get_x();
    double old_dy=p2->get_y()-p1->get_y();
    p1->avanza(pace);
    p2->avanza(pace);
    double dx=p2->get_x()-p1->get_x();
    double dy=p2->get_y()-p1->get_y();
    double D=dist(p1->get_x(),p1->get_y(),p2->get_x(),p2->get_y());
    double due_r=p1->get_ray()+p2->get_ray();
    p1->back_tracking(pace);
    p2->back_tracking(pace);
    if (D-due_r<0) 
      return false;
    else
      if ((abs(dx-old_dx)<=ERRORE)&&(abs(dy-old_dy)<=ERRORE))
        return true;
      else
        return (((dx*old_dx>=0)&&(dy*old_dy>=0)));}

  double Spazio::get_time(){
     return time;}

  void Spazio::avanza_tempo(ofstream& out){
    bool flag;
    do{
      flag=true;
      for (int i=0;(i<num_part)&&(flag);i++)
        for (int j=i+1;(j<num_part)&&(flag);j++)
          flag=controllo(a[i].p,a[j].p);
      if (!flag){
         dec_pace();}}
    while (!flag);
    time+=pace;
    for (int i=0;i<num_part;i++)
      a[i].p->avanza(pace);
    print_statistics(out);
    Particella* p1,*p2;
    if (check_collision(&p1,&p2)){
     collision(p1,p2);
     print_statistics(out);}
    do{
     flag=true;
     for (int i=0;(i<num_part)&&(flag);i++)
       for (int j=i+1;(j<num_part)&&(flag);j++)
         flag=controllo(a[i].p,a[j].p);
     if (flag){
      if (pace<MAX_PACE){
        for (int i=0;i<num_part;i++)
          a[i].p->avanza(pace);
        time+=pace;
        inc_pace();
        print_statistics(out);}
      else
        flag=false;}}
    while (flag);}
  

  void Spazio::urto_totalmente_anelastico(Particella* p1,Particella* p2){
    cout<<"COLLISIONE TOTALMENTE ANELASTICA tra "<<p1->get_name()<<" e "<<p2->get_name()<<" al tempo "<<time<<" s\n";
    double m1=p1->get_mass();
    double m2=p2->get_mass();
    double v1x=p1->get_vx();
    double v2x=p2->get_vx();
    double v1y=p1->get_vy();
    double v2y=p2->get_vy();
    
    double vxf=(m1*v1x+m2*v2x)/(m1+m2);
    double vyf=(m1*v1y+m2*v2y)/(m1+m2);
    sub_particella(p2);
    p1->ingloba(p2);
    p1->change_speed(vxf,vyf);
    p1->change_direction(vxf,vyf);}

  
  void Spazio::urto_elastico_generale(Particella* p1,Particella* p2){
    cout<<"COLLISIONE ELASTICA tra "<<p1->get_name()<<" e "<<p2->get_name()<<" al tempo "<<time<<" s";
    double m1=p1->get_mass();
    double m2=p2->get_mass();
    double y1=p1->get_y();
    double y2=p2->get_y();
    double x1=p1->get_x();
    double x2=p2->get_x();
    double v1x=p1->get_vx();
    double v2x=p2->get_vx();
    double v1y=p1->get_vy();
    double v2y=p2->get_vy();
    cout<<" in posizione "<<x2<<","<<y2<<"\n";

    double m_retta_congiungente;
    bool m_infinito=(x2==x1);
    double teta_r;
    if (!m_infinito){
      m_retta_congiungente=(y2-y1)/(x2-x1);
      teta_r=atan(m_retta_congiungente);}
    else{
      teta_r=PI/2;}


    double v1_i_par=v1x*cos(teta_r)+v1y*sin(teta_r);
    double v2_i_par=v2x*cos(teta_r)+v2y*sin(teta_r);
    double v2_f_par=(2*m1/(m1+m2))*v1_i_par+((m2-m1)/(m1+m2)*v2_i_par);
    double v1_f_par=((m1-m2)/(m2+m1)*v1_i_par)+(2*m2/(m1+m2)*v2_i_par);
    double v2_f_perp=-v2x*sin(teta_r)+v2y*cos(teta_r);
    double v1_f_perp=-v1x*sin(teta_r)+v1y*cos(teta_r);
    double v1_f_x=(v1_f_par*cos(teta_r)-v1_f_perp*sin(teta_r));
    double v1_f_y=(v1_f_par*sin(teta_r)+v1_f_perp*cos(teta_r));
    double v2_f_x=(v2_f_par*cos(teta_r)-v2_f_perp*sin(teta_r));
    double v2_f_y=(v2_f_par*sin(teta_r)+v2_f_perp*cos(teta_r));
    
    p1->change_speed(v1_f_x,v1_f_y);
    p1->change_direction(v1_f_x,v1_f_y);
    p2->change_speed(v2_f_x,v2_f_y);
    p2->change_direction(v2_f_x,v2_f_y);

    //cout<<"Particella "<<p1->get_name()<<" velocità "<<p1->get_speed()<<" direzione "<<p1->get_angle()*180/PI<<endl;
    //cout<<"Particella "<<p1->get_name()<<" velocità "<<p1->get_speed()<<" direzione "<<p1->get_angle()*180/PI<<endl;
    }

  

  bool Spazio::in_collisione(Particella* p1,Particella* p2){
    double D=dist(p1->get_x(),p1->get_y(),p2->get_x(),p2->get_y());
    double due_r=p1->get_ray()+p2->get_ray();
    return (((D-due_r)<=ERRORE)&&(D-due_r>=0));}


  bool Spazio::check_collision(Particella** p1,Particella** p2){
   bool flag=false; 
   for (int i=0;(i<num_part)&&(!flag);i++)
     for (int j=i+1;(j<num_part)&&(!flag);j++){
       flag=in_collisione(a[i].p,a[j].p);
       if (flag){
        *p1=a[i].p;
        *p2=a[j].p;}}
   return flag;}


  void Spazio::collision(Particella* p1,Particella* p2){
    int prob=rand()%100+1;
    if (prob<PROB_ANELASTICO)
        urto_totalmente_anelastico(p1,p2);
    else    
        urto_elastico_generale(p1,p2);}
 
  bool Spazio::check_system(){
   bool flag=true;
   for (int i=0;(i<num_part)&&(flag);i++)
     for (int j=i+1;(j<num_part)&&(flag);j++){
       double D=dist(a[i].p->get_x(),a[i].p->get_y(),a[j].p->get_x(),a[j].p->get_y());
       double due_r=a[i].p->get_ray()+a[j].p->get_ray();
       flag=(D-due_r>0);}
   return flag;}
