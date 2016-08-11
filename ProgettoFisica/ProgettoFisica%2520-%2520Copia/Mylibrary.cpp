#include "Mylibrary.hpp"

void initTermios(int echo) 
{
  tcgetattr(0, &old); 
  nuovo = old; 
  nuovo.c_lflag &= ~ICANON; 
  nuovo.c_lflag &= echo ? ECHO : ~ECHO; 
  tcsetattr(0, TCSANOW, &nuovo); 
}

void resetTermios(void) 
{
  tcsetattr(0, TCSANOW, &old);
}

char getch_(int echo) 
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

char getch(void) 
{
  return getch_(0);
}

int kbhit(void)
{ 
  struct termios oldt, newt;
  int ch;
  int oldf;
 
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
 
  ch = getch();
 
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
 
  if((ch) != EOF)
  {
    ungetc(ch, stdin);
    return 1;
    
  }
 
  return 0;
}

void clear_screen(){
cout<<"\033[2J\033[1;1H";
}

double max(double a,double b){
 if (a>b) return a;
 else return b;}
