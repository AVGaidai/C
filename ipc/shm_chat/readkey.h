#ifndef READKEY_H
#define READKEY_H


#define MANAGER 0
#define SCANER  1

#define KEY_ESC      '\033'
#define KEY_TAB      '\t'
#define MY_KEY_ENTER 13
#define KEY_OTHER    -1


void set_key_handler(int, int, void (*) (char));
int set_mode(int);
int change_mode(void);

void start_readkey(void);
void stop_readkey(void);


#endif
        
