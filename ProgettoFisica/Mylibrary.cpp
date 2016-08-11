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
