#ifndef READKEY_H
#define READKEY_H

#include <ncurses.h>

#define KEY_ESC         '\033'
#define KEY_TAB         '\t'
#define MY_KEY_ENTER    13


void set_handler(void (*) (), int);
void start_readkey(void);
void stop_readkey(void);

#endif
