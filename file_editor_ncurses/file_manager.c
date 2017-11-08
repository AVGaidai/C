/** \file */
#include <ncurses.h>
#include <panel.h>

#include "readkey.h"


#define MANAGET 0
#define EDITOR  1


WINDOW *windows[4];
PANEL *panels[4], *top;

int num_file; /* Number of the currently selected file */
int size_dir; /* Size of directory in the files */

/**********************************************************/
/* Key handlers for file manager and file editor          */
/**********************************************************/

void mup(void)
{
    if (num_file > 0) --num_file;
}

void mdown(void)
    if (num_file < (size_dir - 1)) ++num_file;
}



/**
 * \brief Function setting mode: MANAGER; EDITOR.
 *
 * Function setting handler for each using key.
 *
 * \return no value.
 */
void set_mode(int mode)
{
    switch (mode) {
    MANAGER:
        set_handler(mup, KEY_UP);
        set_handler(mdown, KEY_DOWN);
        /* set_handler(mleft, KEY_LEFT); */
        /* set_handler(mright, KEY_RIGHT); */
        /* set_handler(mesc, KEY_ESC); */
        /* set_handler(menter, KEY_ENTER); */
        /* set_handler(mf2, KEY_F(2)); */
        /* set_handler(mtab, KEY_TAB); */
        break;
    EDITOR:
        /* set_handler(eup, KEY_UP); */
        /* set_handler(edown, KEY_DOWN); */
        /* set_handler(eleft, KEY_LEFT); */
        /* set_handler(eright, KEY_RIGHT); */
        /* set_handler(eesc, KEY_ESC); */
        /* set_handler(eenter, KEY_ENTER); */
        /* set_handler(ef2, KEY_F(2)); */
        /* set_handler(etab, KEY_TAB); */
        break;
    }
}

/**********************************************************/
/* Functions for init/exit file manager                   */
/**********************************************************/

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
    
    curs_set(1); /* Invisible cursor */

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
    
    if (init_pair(3, COLOR_WHITE, COLOR_GREEN) == ERR) {
        endwin();
        return 1;
    }

    return 0;
}


/**
 * \brief Function windows initialization.
 *
 * 1 window is info panel;
 * 2 window is fist panel;
 * 3 window is second panel;
 * 4 window is file redactor.
 *
 * \return no value.
 */
void init_windows()
{
    windows[0] = newwin(1, COLS, 0, 0);
    wbkgdset(windows[0], COLOR_PAIR(2));
    wclear(windows[0]);
    mvwprintw(windows[0], 0, 0, "Tab -- next panel; F2 -- exit");
    wrefresh(windows[0]);
    
    windows[1] = newwin(LINES - 1, COLS / 2, 1, 0);
    wbkgdset(windows[1], COLOR_PAIR(1));
    wclear(windows[1]);
    box(windows[1], ACS_VLINE, ACS_HLINE);
    wrefresh(windows[1]);

    windows[2] = newwin(LINES - 1, COLS - COLS / 2, 1, COLS / 2);
    wbkgdset(windows[2], COLOR_PAIR(1));
    wclear(windows[2]);
    box(windows[2], ACS_VLINE, ACS_HLINE);
    wrefresh(windows[2]);

    windows[3] = newwin(LINES, COLS, 0, 0);
    wbkgdset(windows[3], COLOR_PAIR(1));
    wclear(windows[3]);
    wrefresh(windows[3]);
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
    
    for (i = 0; i < 4; ++i)
        panels[i] = new_panel(windows[i]);

    bottom_panel(panels[3]);
    
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

/**
 * \brief Function initialization file maneger.
 *
 * \return the integer 1 upon failure and 0 upon successful completion.
 */
int init_file_manager(void)
{
    if (init_scr()) {
        fprintf(stderr, "Error into init_scr()...\n");
        return 1;
    }

    if (init_colors()) {
        fprintf(stderr, "Error: not support colors!\n");
        return 1;
    }
    
    init_windows();
    init_panels();
    set_mode(MANAGER);
    start_readkey();
    
    print_panels();

    return 0;
}


/**
 * \brief Function delete all panels and windows
 *
 * \return no value.
 */
void exit_file_manager(void)
{
    int i;

    for (i = 0; i < 4; ++i) {
        del_panel(panels[i]);
        delwin(windows[i]);
    }
    
    endwin();
}

