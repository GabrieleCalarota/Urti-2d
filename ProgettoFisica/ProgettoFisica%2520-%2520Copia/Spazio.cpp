  #include "Spazio.hpp"
  #include "Particella.hpp"

  Spazio::Spazio(){
   time=0;
   pace=0.1;
   cifre=1;
   head_p=NULL;
   head_t=NULL;}

  void Spazio::print_statistics(){
   list* temp=head_p;
   while (temp!=NULL){
      temp->p->print_position();
      temp->p->print_speed();
      temp= temp->next;}
   }
void Spazio::print_grafic(){
  list* temp=head_p;
  double min_x=head_p->p->get_x()-head_p->p->get_ray();
  double max_x=min_x+(2*head_p->p->get_ray());
  double max_y=head_p->p->get_y()+head_p->p->get_ray();
  double min_y=max_y-(2*head_p->p->get_ray());
  int cont=0;
  while (temp!=NULL){
    if (temp->p->get_x()-temp->p->get_ray()<min_x)
     min_x=temp->p->get_x()-temp->p->get_ray();
    if (temp->p->get_x()+temp->p->get_ray()>max_x)
     max_x=temp->p->get_x()+temp->p->get_ray();
   if (temp->p->get_y()-temp->p->get_ray()<min_y)
     min_y=temp->p->get_y()-temp->p->get_ray();
   if (temp->p->get_y()+temp->p->get_ray()>max_y)
     max_y=temp->p->get_y()+temp->p->get_ray();
   temp=temp->next;
   cont++;}
  struct cfr{ int xmin; int xmax; int ymin; int ymax; int xc; int yc; char name[20];};
  cfr c[cont];
  temp=head_p;
  for (int i=0;i<cont;i++){
   int r=(int)temp->p->get_ray();
   int xc=(int)temp->p->get_x();
   int yc=(int)temp->p->get_y();
   c[i].xmin=xc-r;
   c[i].xmax=xc+r;
   c[i].ymin=yc-r;
   c[i].ymax=yc+r;
   c[i].xc=xc;
   c[i].yc=yc;
   strcpy(c[i].name,temp->p->get_name());
   temp=temp->next;}
 cout<<"\n";
 /*for (int i=(int)max_y;i>=(int)min_y;i--){
  cout<<"\t\t";
  for (int j=(int)min_x;j<=(int)max_x;j++){
   bool print=false;
    for (int s=0;s<cont;s++){
    if ((!print)&&(c[s].xc==j)&&(c[s].ymax==i)&&(c[s].ymax>c[s].ymin)) {
      cout<<c[s].name[0];
      print=true;
      c[s].ymax--;}
      if ((c[s].yc==i)&&(c[s].xmin==j)&&(c[s].xmin<c[s].xmax)) {
      cout<<c[s].name[0];
      print=true;
      c[s].xmin++;} }
     if (!print)
      cout<<" "; }
   cout<<"\n";}*/
for (int i=20;i>=-20;i--){
  cout<<"\t\t";
  for (int j=-80;j<=80;j++){
   bool print=false;
    for (int s=0;s<cont;s++){
    if ((!print)&&(c[s].xc==j)&&(c[s].ymax==i)&&(c[s].ymax>c[s].ymin)) {
      cout<<c[s].name[0];
      print=true;
      c[s].ymax--;}
      if ((c[s].yc==i)&&(c[s].xmin==j)&&(c[s].xmin<c[s].xmax)) {
      cout<<c[s].name[0];
      print=true;
      c[s].xmin++;} }
     if (!print)
      if (i==0&&j==0)
       cout<<"O";
      else
        cout<<" "; }
   cout<<"\n";}
}
   
  void Spazio::print_position(){
   list* temp=head_p;
   while (temp!=NULL){
      temp->p->print_position();
      temp= temp->next;}}
  void Spazio::add_particella(Particella* p){
    list* temp=new list;
   temp->p=p;
   temp->next=head_p;
   head_p=temp;}

  void Spazio::add_particella(char* n,double r1,double r2,double r,double v,double a,double m){
   Particella* p=new Particella(n,r1,r2,r,v,a,m);
   list* temp=new list;
   temp->p=p;
   temp->next=head_p;
   head_p=temp;}

  void Spazio::sub_particella(char* n){
   bool flag=true;
   list* temp=head_p;
   while ((temp!=NULL)&&flag){
     if (temp->p->confronta(n)){
       flag=false;
       if (temp==head_p){
          head_p=head_p->next;
          delete temp;}
       else{
       list* temp2=head_p;
       while (temp2->next!=temp) 
          temp2=temp2->next;
       temp2->next=temp->next;
       delete temp;}} 
     else
       temp=temp->next;} 
     }
  void Spazio::sub_particella(Particella* k){
   if (head_p!=NULL){
    if (head_p->p==k){ 
     list* temp=head_p;
     head_p=head_p->next;
     delete temp;}
    else{
     list* temp=head_p;
     while (temp->next->p!=k)
       temp=temp->next;
     list* temp2=temp->next;
     temp->next=temp2->next;
     //delete temp2;
     }}
     }

  void Spazio::dec_pace(){
   pace=pace/10;
   if (pace<1)
     cifre++;
   cout<<"Ora il passo è di "<<setprecision(cifre)<<pace<<" s.\n";}
  void Spazio::inc_pace(){
    if (cifre>1)
      cifre--;
    pace=pace*10;
    cout<<"Ora il passo è di "<<setprecision(cifre)<<pace<<" s.\n";}

  void Spazio::avanza_tempo(){
   time+=pace;
   data_time* tmp=new data_time;
   tmp->t=pace;
   tmp->next=head_t;
   head_t=tmp;
   list *temp=head_p;
   while (temp!=NULL){
    temp->p->avanza(pace);
    temp=temp->next;}
    check_position();}

  void Spazio::choose_collision(Particella* p1,Particella* p2){
   cout<<"Che tipo di collisione stanno avendo le due particelle?\n\t1) Elastico\n\t2) Anelastico\n\t3) Totalmente Anelastico\n";
   char c;
   do
    c=getch();
   while ((c!='1')&&(c!='2')&&(c!='3'));
   switch (c){
    case ('1'):{ urto_elastico(p1,p2); break;}
    case ('2'):{ urto_anelastico(p1,p2); break;}
    case ('3'):{ urto_totalmente_anelastico(p1,p2); break;}} }

 void Spazio::urto_anelastico(Particella* p1,Particella* p2){
  cout<<"COLLISIONE TOTALMENTE ANELASTICA tra "<<p1->get_name()<<" e "<<p2->get_name()<<" al tempo "<<setprecision(3)<<time<<" s\n";
  cout<<"Indica quale velocità dopo l'urto conosci tra:\n\t1) "<<p1->get_name()<<"\n\t2) "<<p2->get_name()<<"\n";
  char c;
  do
   c=getch();
  while ((c!='1')&&(c!='2'));
   double m1=p1->get_mass();
    double m2=p2->get_mass();
    double v1x=p1->get_vx();
    double v2x=p2->get_vx();
    double v1y=p1->get_vy();
    double v2y=p2->get_vy();

    double v1xf,v2xf,v1yf,v2yf,v1f,v2f,dir;
  cout<<"Inserisci la velocità dopo l'urto della particella ";
  switch (c){
   case '1':{ cout<<p1->get_name()<<"\n"; cin>>v1f; cout<<"Ora inserisci la direzione:\n"; 
               do
                 cin>>dir;
               while ((dir<-179)||(dir>180));
               p1->change_speed(v1f);
               p1->change_direction(dir,false);
               v1xf=p1->get_vx();
               v1yf=p1->get_vy();
               v2xf=((v1x*m1+v2x*m2)-v1xf*m1)/m2;
               v2yf=((v1y*m1+v2y*m2)-v1yf*m1)/m2;
               p2->change_speed(v2xf,v2yf);
               p2->change_direction(v2xf,v2yf);
                break;}
   case '2':{ cout<<p2->get_name()<<"\n"; cin>>v2f; cout<<"Ora inserisci la direzione:\n"; 
               do
                 cin>>dir;
               while ((dir<-179)||(dir>180));
               p2->change_speed(v2f);
               p2->change_direction(dir,false);
               v2xf=p2->get_vx();
               v2yf=p2->get_vy();
               v1xf=((v1x*m1+v2x*m2)-v2xf*m2)/m1;
               v1yf=((v1y*m1+v2y*m2)-v2yf*m2)/m1;
               p1->change_speed(v1xf,v1yf);
               p1->change_direction(v1xf,v1yf); break;}}
  }


  void Spazio::urto_totalmente_anelastico(Particella* p1,Particella* p2){
   cout<<"COLLISIONE TOTALMENTE ANELASTICA tra "<<p1->get_name()<<" e "<<p2->get_name()<<" al tempo "<<setprecision(3)<<time<<" s\n";
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
    p1->change_direction(vxf,vyf);
   }
  void Spazio::urto_elastico_generale(Particella* p1,Particella* p2){
   cout<<"COLLISIONE ELASTICA tra "<<p1->get_name()<<" e "<<p2->get_name()<<" al tempo "<<setprecision(3)<<time<<" s\n";
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
    
    double m_retta_congiungente;
    bool m_infinito=(x2==x1);
    double teta_r;
    if (!m_infinito){
      m_retta_congiungente=(y2-y1)/(x2-x1);
      teta_r=atan(m_retta_congiungente);}
    else{teta_r=PI/2;}
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
    }

  void Spazio::urto_elastico(Particella* p1,Particella* p2){
    cout<<"COLLISIONE ELASTICA tra "<<p1->get_name()<<" e "<<p2->get_name()<<" al tempo "<<setprecision(3)<<time<<" s\n";
    double m1=p1->get_mass();
    double m2=p2->get_mass();
    double y1=p1->get_y();
    double y2=p2->get_y();
    //double dir1=p1->get_angle();
    //double dir2=p2->get_angle();
    double x1=p1->get_x();
    double x2=p2->get_x();
    double v1x=p1->get_vx();
    double v2x=p2->get_vx();
    double v1y=p1->get_vy();
    double v2y=p2->get_vy();
    
    double m_retta_congiungente;
    bool m_infinito=(x2==x1);
    double teta_r;
    if (!m_infinito){
      m_retta_congiungente=(y2-y1)/(x2-x1);
      teta_r=atan(m_retta_congiungente);}
    else{teta_r=PI/2;}
    double m_perpendicolare;
    bool m_perpendicolare_infinito=(y2==y1);
    double teta_t;
    if (!m_perpendicolare_infinito){ 
      m_perpendicolare=(x1-x2)/(y2-y1);
      teta_t=atan(m_perpendicolare);}
    else{teta_t=PI/2;}

    Particella* p=new Particella((char*)"Fittizia",x1,y1,m1);
    double v1y_fittizio=v1y-v2y;
    double v1x_fittizio=v1x-v2x;
    p->change_speed(v1x_fittizio,v1y_fittizio);
    p->change_direction(v1x_fittizio,v1y_fittizio);
    double v1_fittizio=p->get_speed();
    double dir1_f=p->get_angle();

    double teta_temp=teta_t-dir1_f;
    double teta_1_f=teta_t;
    double teta_2_f=teta_r;
    double v1f=v1_fittizio*cos(teta_temp);
    double v2f=v1_fittizio*sin(teta_temp);
    if (v1f<0)
     teta_1_f-=PI;
    if (v2f<0)
     teta_2_f+=PI;

    /*if ((dir1_f>PI/2)||(dir1_f<(-PI/2)))
     teta_2_f=PI-teta_r;
    else
      teta_2_f=teta_r;*/

    
    double v1fx=v1f*cos(teta_1_f)+v2x;
    double v1fy=v1f*sin(teta_1_f)+v2y;
    p1->change_speed(v1fx,v1fy);
    p1->change_direction(v1fx,v1fy);
   
    double v2fx=v2f*cos(teta_2_f)+v2x;
    double v2fy=v2f*sin(teta_2_f)+v2y;
    p2->change_speed(v2fx,v2fy);
    p2->change_direction(v2fx,v2fy);
    
    
  /*  double v1xf=((m1-m2)*v1x+(2*m2*v2x))/(m1+m2);
    double v2xf=((m2-m1)*v2x+(2*m1*v1x))/(m1+m2);
    
    double v1yf=((m1-m2)*v1y+(2*m2*v2y))/(m1+m2);
    double v2yf=((m2-m1)*v2y+(2*m1*v1y))/(m1+m2);
*/
   }

  void Spazio::check_position(){
   list* temp1=head_p;
   bool flag=false;
   while ((temp1!=NULL)&&(!flag)){
     list* temp2=temp1->next;
     while ((temp2!=NULL)&&!flag){
       if (temp1->p->miss_collision(temp2->p)){
          cout<<"Collisione mancata tra la particella "<<temp1->p->get_name()<<" e la particella "<<temp2->p->get_name()<<"\n";
        arretra_tempo();
        dec_pace();
        flag=true;}
       else{ if (temp1->p->same_position(temp2->p)){
        cout<<"La particella "<<temp1->p->get_name()<<" di massa "<<setprecision(2)<<temp1->p->get_mass()<<" kg in posizione ( "<<setprecision(2)<<temp1->p->get_x()<<", "<<setprecision(2)<<temp1->p->get_y()<<") sta collidendo con la";
        cout<<" particella "<<temp2->p->get_name()<<" di massa "<<setprecision(2)<<temp2->p->get_mass()<<" kg in posizione ( "<<setprecision(2)<<temp2->p->get_x()<<", "<<setprecision(2)<<temp2->p->get_y()<<")\n";
        temp1->p->print_speed();
        temp2->p->print_speed();
        //choose_collision(temp1->p,temp2->p);  
        int prob=rand()%1000+1;
        if (prob<500)
         urto_totalmente_anelastico(temp1->p,temp2->p);
        else    
         urto_elastico_generale(temp1->p,temp2->p);
        print_statistics();
       }}
       temp2=temp2->next;} 
     temp1=temp1->next;}
    }

 

  void Spazio::arretra_tempo(){
   if (time>0){
     double t=head_t->t;
     data_time* tmp=head_t;
     head_t=head_t->next;
     delete tmp;
     time-=t;
     list* temp=head_p;
     while (temp!=NULL){
    temp->p->back_tracking(t);
    //check_position();
    temp=temp->next;}
     } }
