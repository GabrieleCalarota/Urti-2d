#ifndef MYLIBRARY_HPP_
#define MYLIBRARY_HPP_
#include <iostream>
using namespace std;
#include <stdio.h>
#include <cmath>
#include <cstring>
#include <termios.h>
#include <iomanip>
#include <unistd.h>
#include <fcntl.h>
#include <ctime>
#include <cstdlib>
const double PI=3.141592654;
static struct termios old, nuovo;
void initTermios(int echo);
void resetTermios(void);
char getch_(int echo);
int kbhit(void);
char getch(void);
void clear_screen();
double max(double,double);

#endif
