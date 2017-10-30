/** \file */
#include <ncurses.h>
#include <panel.h>


/**
 * \brief Function screen initialization.
 *xs
 * \return the integer 1 upon failure and 0 upon successful completion.
 */
int init_scr(void)
{
   /*
    * The initscr code determines the terminal type
    * and initializes all curses data structures 
    */
    if (initscr() == NULL)
        return 1;
   /*
    * The cbreak routine disables line buffering and 
    * erase/kill character-processing (interrupt and
    * flow control characters are unaffected), making
    * characters typed by the user immediately avail‐
    * able to the program
    */ 
    if (cbreak() == ERR)
        return 1;
   /*
    * The echo and noecho routines control whether
    * characters typed by the user are echoed by
    * getch() as they are typed
    */
    if (noecho() == ERR)
        return 1;
   /*
    * The nl and nonl routines control whether the 
    * underlying display device translates the return
    * key into newline on input, and whether it tran-
    * slates newline into return and line-feed on out‐
    * put. Initially, these translations do occur. If
    * you disable them using nonl, curses will be able
    * to make better use of the line-feed capability,
    * resulting in faster cursor motion.
    */
    nonl();
    if (intrflush(stdscr, FALSE) == ERR)
        return 1;
    if (keypad(stdscr, TRUE) == ERR)
        return 1;

    return 0;
}
    


int main(int argc, char *argv[])
{
    WINDOW *windows[3];
    PANEL *panels[3], *top;
    int i, ch;
    
    init_stdscr()


    if (!has_colors()) {
        endwin();
        printf("Error: not support colors!\n");
        return 1;
    }

    curs_set(0);
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLUE);
    init_pair(2, COLOR_GREEN, COLOR_RED);
    init_pair(3, COLOR_BLUE, COLOR_GREEN);
    
    for (i = 0; i < 3; ++i) {
        windows[i] = newwin(20 + i * 2, 100 - i * 10, 2 + i, i * 10);
        wbkgdset(windows[i], COLOR_PAIR(i + 1));
        wclear(windows[i]);
        box(windows[i], ACS_VLINE, ACS_HLINE);
        mvwprintw(windows[i], 1, 1, "hello world!!! I'am panel %d\n", i);
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
