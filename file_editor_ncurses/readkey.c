#include <ncurses.h>

#define KEY_ESC         '\033'
#define KEY_TAB         '\t'

struct key_module_env {

    int stop;
    
    void (*handler_up)    ();
    void (*handler_down)  ();
    void (*handler_left)  ();
    void (*handler_right) ();
    void (*handler_esc)   ();
    void (*handler_enter) ();
    void (*handler_f2)    ();
    void (*handler_tab)   ();
    
};


struct key_module_env key_module;


void set_handler(void *hanler, int key) {

    switch (key) {
    KEY_UP:
        key_module.handler_up = handler;
        break;
    KEY_DOWN:
        key_module.handler_down = handler;
        break;
    KEY_LEFT:
        key_module.handler_left = handler;
        break;
    KEY_RIGHT:
        key_module.handler_right = handler;
        break;
    KEY_ESC:
        key_module.handler_esc = handler;
        break;
    KEY_ENTER:
        key_module.handler_enter = handler;
        break;
    KEY_F(2):
        key_module.handler_f2 = handler;
        break;
    KEY_TAB:
        key_module.handler_tab = handler;
        break;
    }
}


void start_readkey(void)
{
    int ch;
    
    key_module.stop = 0;

    while (!key_module.stop) {
        ch = getch();
        switch (ch) {
        KEY_UP:
            key_module.handler_up();
            break;
        KEY_DOWN:
            key_module.handler_down();
            break;
        KEY_LEFT:
            key_module.handler_left();
            break;
        KEY_RIGHT:
            key_module.handler_right();
            break;
        KEY_ESC:
            key_module.handler_esc();
            break;
        KEY_ENTER:
            key_module.handler_enter();
            break;
        KEY_F(2):
            key_module.handler_f2();
            break;
        KEY_TAB:
            key_module.handler_tab();
            break;
        }
    }
}

void stop_readkey(void)
{
    key_module.stop = 1;
}
