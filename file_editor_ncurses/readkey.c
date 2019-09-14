#include <ncurses.h>

#define KEY_ESC         '\033'
#define KEY_TAB         '\t'
#define MY_KEY_ENTER    13


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


void set_handler(void (*handler) (), int key) {

    switch (key) {
    case KEY_UP:
        key_module.handler_up = handler;
        break;
    case KEY_DOWN:
        key_module.handler_down = handler;
        break;
    case KEY_LEFT:
        key_module.handler_left = handler;
        break;
    case KEY_RIGHT:
        key_module.handler_right = handler;
        break;
    case KEY_ESC:
        key_module.handler_esc = handler;
        break;
    case MY_KEY_ENTER:
        key_module.handler_enter = handler;
        break;
    case KEY_F(2):
        key_module.handler_f2 = handler;
        break;
    case KEY_TAB:
        key_module.handler_tab = handler;
        break;
    default:
        ;
    }
}


void start_readkey(void)
{
    int ch;
    
    key_module.stop = 0;

    while (!key_module.stop) {
        ch = getch();
        switch (ch) {
        case KEY_UP:
            key_module.handler_up();
            break;
        case KEY_DOWN:
            key_module.handler_down();
            break;
        case KEY_LEFT:
            key_module.handler_left();
            break;
        case KEY_RIGHT:
            key_module.handler_right();
            break;
        case KEY_ESC:
            key_module.handler_esc();
            break;
        case MY_KEY_ENTER:
            key_module.handler_enter();
            break;
        case KEY_F(2):
            key_module.handler_f2();
            break;
        case KEY_TAB:
            key_module.handler_tab();
            break;
        }
    }
}

void stop_readkey(void)
{
    key_module.stop = 1;
}
