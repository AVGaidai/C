#include <stdlib.h>

#include <ncurses.h>
#include <panel.h>

#include "readkey.h"

WINDOW *windows[3], *cur_win;
PANEL *panels[3], *top;

int msg_size, msg_maxsize;
char *msg;


/**
 * \brief Function screen initialization.
 *
 * \return the integer 1 upon failure and 0 upon successful completion.
 */
int init_scr(void)
{
    if (initscr() == NULL)
        return 1;
  
    if (cbreak() == ERR)
        return 1;
  
    if (noecho() == ERR)
        return 1;
  
    nonl();

    if (intrflush(stdscr, FALSE) == ERR)
        return 1;

    if (keypad(stdscr, TRUE) == ERR)
        return 1;

    return 0;
}


/**
 * \brief Function colors initialization.
 *
 * Color pairs:
 * 1) White font and blue background.
 * 2) White font and cyan background.
 * 3) White font and green background.
 *
 * \return the integer 1 upon failure and 0 upon successful completion.
 */
int init_colors(void)
{
    if (!has_colors()) {
        endwin();
        return 1;
    }
    
    curs_set(0); /* Invisible cursor */

    if (start_color() == ERR) {
        endwin();
        return 1;
    }
    
    if (init_pair(1, COLOR_WHITE, COLOR_BLUE) == ERR) {
        endwin();
        return 1;
    }
    
    if (init_pair(2, COLOR_BLACK, COLOR_CYAN) == ERR) {
        endwin();
        return 1;
    }
    
    if (init_pair(3, COLOR_WHITE, COLOR_CYAN) == ERR) {
        endwin();
        return 1;
    }

    return 0;
}


/**
 * \brief Function windows initialization.
 *
 * 0 window is info panel;
 * 1 window is print panel;
 * 2 window is scan panel.
 *
 * \return no value.
 */
void init_windows()
{
    windows[0] = newwin(6, 34, LINES / 2 - 3, COLS / 2 - 17);
    wbkgdset(windows[0], COLOR_PAIR(1));
    wclear(windows[0]);
    box(windows[0], ACS_VLINE, ACS_HLINE);
    mvwprintw(windows[0], 2, 2, "Are you sure you want to quit?");
    mvwprintw(windows[0], 3, 2, "             (Y/N)            ");
    wrefresh(windows[0]);

    windows[1] = newwin(LINES - 3, COLS, 0, 0);
    wbkgdset(windows[1], COLOR_PAIR(2));
    wclear(windows[1]);
    box(windows[1], ACS_VLINE, ACS_HLINE);
    wrefresh(windows[1]);

    windows[2] = newwin(3, COLS, LINES - 3, 0);
    wbkgdset(windows[2], COLOR_PAIR(3));
    wclear(windows[2]);
    box(windows[2], ACS_VLINE, ACS_HLINE);
    wrefresh(windows[2]);
}


/**
 * \brief Function panels initialization.
 *
 * N panel associates with N window;
 *
 * \return no value.
 */
void init_panels()
{
    int i;
    
    for (i = 0; i < 3; ++i)
        panels[i] = new_panel(windows[i]);

    top = panels[1];
    top_panel(panels[1]);
    bottom_panel(panels[0]);
    
    /* Connect panels 1 and 2 to switch */
    set_panel_userptr(panels[1], panels[2]);
    set_panel_userptr(panels[2], panels[1]);
}



/**
 * \brief Function print current panels.
 *
 * \return no value.
 */
void print_panels(void)
{
    update_panels();
    doupdate();
}



void mngr_esc_handler(char ch)
{
    top_panel(panels[0]);
    print_panels();

    do {
        ch = getch();
    } while (ch != 'Y' && ch != 'y' && ch != 'N' && ch != 'n');

    if (ch == 'Y' || ch == 'y') {
        stop_readkey();
        msg_size = -1;
        clear();
    } else {
        top_panel(top);
        bottom_panel(panels[0]);
        print_panels();
    }
}

void mngr_enter_handler(char ch)
{
    change_mode();
    top = (PANEL *) panel_userptr(top);
    top_panel(top);

    cur_win = panel_window(top);
    curs_set(1);
    wmove(windows[2], 1, msg_size + 1);
    print_panels();
}

void mngr_bckspc_handler(char ch)
{
    return;
}

void mngr_other_handler(char ch)
{
    return;
}

void scnr_esc_handler(char ch)
{
    change_mode();
    
    top = (PANEL *) panel_userptr(top);
    top_panel(top);

    cur_win = panel_window(top);
    curs_set(0);
    print_panels();
}

void scnr_enter_handler(char ch)
{
    if (msg_size) {
        msg[msg_size++] = '\n';
        wclear(windows[2]);
        box(windows[2], ACS_VLINE, ACS_HLINE);
        wmove(windows[2], 1, 1);
        print_panels();
        stop_readkey();
    }
}

void scnr_bckspc_handler(char ch)
{
    if (msg_size) {
        mvwprintw(cur_win, 1, msg_size--, " ");
        wmove(windows[2], 1, msg_size + 1);
        print_panels();
    }
}

void scnr_other_handler(char ch)
{
    if (ch >= 0x20 && ch <= 0x7E) {
        msg[msg_size] = ch;
        mvwprintw(cur_win, 1, 1 + msg_size++, "%c", ch);
        if (msg_size + 1 == msg_maxsize) {
            msg[msg_size++] = '\n';
            stop_readkey();
        }
        print_panels();
    }
}


void init_env(void)
{
    set_key_handler(MANAGER, KEY_ESC, mngr_esc_handler);
    set_key_handler(MANAGER, MY_KEY_ENTER, mngr_enter_handler);
    set_key_handler(MANAGER, KEY_BACKSPACE, mngr_bckspc_handler);
    set_key_handler(MANAGER, KEY_OTHER, mngr_other_handler);

    set_key_handler(SCANER, KEY_ESC, scnr_esc_handler);
    set_key_handler(SCANER, MY_KEY_ENTER, scnr_enter_handler);
    set_key_handler(SCANER, KEY_BACKSPACE, scnr_bckspc_handler);
    set_key_handler(SCANER, KEY_OTHER, scnr_other_handler);

    set_mode(MANAGER);
}



void initialize(void)
{
    init_scr();
    init_colors();
    init_windows();
    init_panels();
    init_env();

    print_panels();
}


void finalize(void)
{
    int i;

    stop_readkey();
    clear();
    curs_set(1);
    for (i = 0; i < 3; ++i) {
        del_panel(panels[i]);
        delwin(windows[i]);
    }

    endwin();
}



int msg_scan(char *buf, size_t maxsize)
{
    int i;
    msg_size = 0;
    msg_maxsize = maxsize;
    msg = (char *) malloc (maxsize * sizeof(char));
    start_readkey();
    
    for (i = 0; i < msg_size; ++i) {
        buf[i] = msg[i];
    }

    free(msg);
    
    return msg_size;
}



void msg_print(char *buf, size_t lbuf)
{
    int i, c, l;
    
    wclear(windows[1]);
    box(windows[1], ACS_VLINE, ACS_HLINE);
    l = 1;
    c = 1;
    
    for (i = 0; i < lbuf; ++i) { 
        mvwprintw(windows[1], l, c, "%c", buf[i]);
        if (buf[i] == '\n' || c == COLS - 2) {
            ++l;
            c = 1;
            box(windows[1], ACS_VLINE, ACS_HLINE);
            continue;
        }
        ++c;        
    }
    print_panels();
}

