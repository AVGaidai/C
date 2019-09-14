#include <ncurses.h>

#include "readkey.h"


struct mode_env {

    void (*esc)    (char);
    void (*enter)  (char);
    void (*bckspc) (char);
    void (*other)  (char);
    
};


struct mode_env env[2];

int cur_mode = MANAGER;

int stop_flg;

void set_key_handler(int mode, int key, void (*handler) (char))
{
    mode = mode % 2;
    
    switch (key) {
    case KEY_ESC :
        env[mode].esc = handler;
        break;
    case MY_KEY_ENTER :
        env[mode].enter = handler;
        break;
    case KEY_BACKSPACE :
        env[mode].bckspc = handler;
        break;
    case KEY_OTHER :
        env[mode].other = handler;
        break;
    default :
        break;
    }
}


int set_mode(int mode) {
    cur_mode = mode % 2;

    return cur_mode;
}

int change_mode(void) {
    cur_mode = (cur_mode + 1) % 2;

    return cur_mode;
}


/* int m_esc_handler(void *arg) */
/* { */
/*     int ch; */

/*     /\* print warrning box with pull (Y/N) *\/ */
/*     do { */
/*         ch = getch(); */
/*     } while (ch != 'Y' && ch != 'y' && ch != 'N' && ch != 'n'); */

/*     if (ch == 'Y' || ch == 'y') { */
/*         return -1; */
/*     } */

/*     return 0; */
/* } */


/* int m_enter_handler(void *arg) */
/* { */
/*     /\* set input message box *\/ */
/*     cur_mode = SCANER; */

/*     return 0; */
/* } */


/* int m_bckspc_handler(void *arg) */
/* { */
/*     return 0; */
/* } */


/* int m_other_handler(void *arg) */
/* { */
/*     return 0; */
/* } */


/* int s_esc_handler(void *arg) */
/* { */
/*     /\* set manager box *\/ */
/*     cur_mode = MANAGER; */

/*     return 0; */
/* } */


/* int s_enter_handler(void *arg) */
/* { */
/*     int i = *((int *) arg); */
/*     return i; */
/* } */

/* int s_bckspc_handler(void *arg) */
/* { */
/*     int i = *((int *) arg); */

/*     if (i > 0) { */
/*         return 1; */
/*     } */
/*     /\* edit input box *\/ */
/*     return 0; */
/* } */


/* int s_other_handler(void *arg)  */
/* { */
/*     char ch = *((char *) arg); */
    
/*     if (ch >= 0x20 && ch <= 0x7E) { */
/*         return (int) ch; */
/*     } */

/*     return 0; */
/* } */


/* void init_env(void) { */

/*     cur_mode = MANAGER; */


/*     env[MANAGER].esc = m_esc_handler; */
/*     env[MANAGER].enter = m_enter_handler; */
/*     env[MANAGER].bckspc = m_bckspc_handler; */
/*     env[MANAGER].other = m_other_handler; */
    
/*     env[SCANER].esc = s_esc_handler; */
/*     env[SCANER].enter = s_enter_handler; */
/*     env[SCANER].bckspc = s_bckspc_handler; */
/*     env[SCANER].other = s_other_handler; */
/* } */



void start_readkey(void)
{
    int ch;
    
    stop_flg = 0;
    while (!stop_flg) {
        ch = getch();

        switch (ch) {
        case KEY_ESC :
            env[cur_mode].esc(ch);
            break;
        case MY_KEY_ENTER :
            env[cur_mode].enter(ch);
            break;
        case KEY_BACKSPACE :
            env[cur_mode].bckspc(ch);
            break;
        default:
            env[cur_mode].other(ch);
        }
    }
}
        

void stop_readkey(void)
{
    stop_flg = 1;
}
