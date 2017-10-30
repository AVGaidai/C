/** \file */
#include <ncurses.h>
#include <panel.h>


/**
 * \brief Function screen initialization.
 * 
 * To get character-at-a-time input without echoing
 * (most interactive, screen oriented programs want
 * this), the following sequence should be used:
 *   initscr(); cbreak(); noecho();
 * Most programs would additionally use the sequence:
 *   nonl();
 *   intrflush(stdscr, FALSE);
 *   keypad(stdscr, TRUE);
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
    

int init_colors(void)
{
    if (!has_colors())
        return 1;
    
    curs_set(0); /* Invisible cursor */

    if (start_color() == ERR)
        return 1;
    
    if (init_pair(1, COLOR_WHITE, COLOR_BLUE) == ERR)
        return 1;
    
    if (init_pair(2, COLOR_WHITE, COLOR_CYAN) == ERR)
        return 1;
    
    if (init_pair(3, COLOR_WHITE, COLOR_GREEN) == ERR)
        return 1;

    return 0;
}


int main(int argc, char *argv[])
{
    WINDOW *windows[3];
    PANEL *panels[3], *top;
    int i, ch;
    
    if (init_scr()) {
        fprintf(stderr, "Error into init_scr()...\n");
        return 1;
    }

    if (init_colors()) {
        fprintf(stderr, "Error: not support colors!\n");
        endwin();
        return 1;
    }
    
    for (i = 0; i < 3; ++i) {
        windows[i] = newwin(20 + i * 2, 100 - i * 10, 2 + i, i * 10);
        wbkgdset(windows[i], COLOR_PAIR(i + 1));
        wclear(windows[i]);
        mvwprintw(windows[i], 1, 1, "hello world!!! I'am panel %d\n", i);
        box(windows[i], ACS_VLINE, ACS_HLINE);
        wrefresh(windows[i]);

        panels[i] = new_panel(windows[i]);
    }

    set_panel_userptr(panels[0], panels[1]);
    set_panel_userptr(panels[1], panels[2]);
    set_panel_userptr(panels[2], panels[0]);
    
    update_panels();
    mvprintw(0, 0, "Tab -- next panel; F2 -- exit");
    doupdate();

    top = panels[2];
    
    while ( (ch = getch()) != KEY_F(2)) {
        switch(ch) {
        case '\t':
            top = (PANEL *) panel_userptr(top);
            top_panel(top);
            break;
        }

        update_panels();
        doupdate();
    }


    for (i = 0; i < 3; ++i) {
        del_panel(panels[i]);
        delwin(windows[i]);
    }
    
    endwin();
    
    return 0;
}
