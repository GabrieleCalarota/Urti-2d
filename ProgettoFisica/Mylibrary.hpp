#ifndef MYLIBRARY_HPP_
#define MYLIBRARY_HPP_
#include <iostream>
using namespace std;
#include <stdio.h>
#include <cmath>
#include <cstring>
#include <termios.h>
#include <iomanip>
const double PI=3.141592654;
static struct termios old, nuovo;
void initTermios(int echo);
void resetTermios(void);
char getch_(int echo);

char getch(void);


#endif
