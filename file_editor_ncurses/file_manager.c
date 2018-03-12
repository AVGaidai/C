/** \file */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <string.h>

#include <ncurses.h>
#include <panel.h>

#include "singly_linked_list/sllist.h"
#include "file_manager.h"
#include "readkey.h"


#define MANAGER 0 
#define EDITOR  1

WINDOW *curr_window, *curr_frame;
WINDOW *windows[6];
PANEL *panels[6], *top;

int Y1, Y2;
char *curr_pd;


struct sllist *curr_tab; /* Pointer to the currently selected tab */

/*********************************************************/
/* Other functions                                       */
/*********************************************************/

/**
 * \brief Function to open and print content of directory.
 *
 * \param pd is path of directory.
 * \param tab is current tab.
 *
 * \return the integer 1 upon failure and 0 upon successful completion.
 */
int open_dir(const char *pd, struct sllist *tab)
{
    char *command, *payload;
    char fname[255];
    size_t len;
    FILE *fp;
    int i, nmemb;

    if (curr_window == windows[1]) {
        Y1 = 2;
    } else {
        Y2 = 2;
    }
    wclear(curr_window);
    box(curr_window, ACS_VLINE, ACS_HLINE);
    wrefresh(curr_window);
    wclear(curr_frame);
    wrefresh(curr_frame);
    
    len = strlen(pd);
    command = (char *) malloc((25 + len) * sizeof(char));
    memcpy((void *) command, (const void *) "dir -1a > /tmp/.dir_tmp ",
           24 * sizeof(char));
    memcpy((void *) (command + 24), (const void *) pd, len * sizeof(char));
    command[24 + len] = '\0';
    system(command);
    free(command);
    
    fp = fopen("/tmp/.dir_tmp", "r");
    if (fp == NULL) return 1;
    
    sllist_free(tab);
    
    nmemb = 0;
    payload = malloc(sizeof(char));
    while(fgets(fname, 255, fp) != NULL) {
        len = strlen(fname);
        payload = realloc((void *) payload, len * sizeof(char));
        memcpy((void *) payload, (const void *) fname, len * sizeof(char));
        payload[len - 1] = '\0';
        sllist_insert_back(tab, (const void *) payload, len * sizeof(char));
        ++nmemb;
    }
    fclose(fp);
    sllist_drop_ptr(tab);
    free(payload);
    
    for (i = 0 ; i < nmemb; ++i) {
        payload = (char *) sllist_get_curr(tab, &len);
        sllist_next_node(tab);
        payload[len] = '\0';
        mvwprintw(curr_window, i + 1, 1, "%s", payload);
        free(payload);
    }
    sllist_drop_ptr(tab);
    payload = (char *) sllist_get_curr(tab, &len);
    wprintw(curr_frame, "%s", payload);
    free(payload);

    if (curr_frame == windows[3]) {
        mvwin(curr_frame, Y1, 1);
        top_panel(panels[1]);
        top_panel(panels[3]);
    } else {
        mvwin(curr_frame, Y2, COLS / 2 + 1);
        top_panel(panels[2]);
        top_panel(panels[4]);
    }
    
    return 0;
}



/*********************************************************/
/* Key handlers for file manager and file editor         */
/*********************************************************/

/**
 * \brief Handler for KEY_UP in manager mode.
 *
 * \return no value.
 */
void mup(void)
{
    char *payload;
    size_t size;
    
    if (sllist_prev_node(curr_tab)) {
        return;
    } else if (curr_frame == windows[3]) {
        mvwin(curr_frame, --Y1, 1);
        payload = (char *) sllist_get_curr(curr_tab, &size);      
        top_panel(panels[1]);
        top_panel(panels[3]);
    } else {
        mvwin(curr_frame, --Y2, COLS / 2 + 1);
        payload = (char *) sllist_get_curr(curr_tab, &size);
        top_panel(panels[2]);
        top_panel(panels[4]);
    }
    payload[size] = '\0';
    wclear(curr_frame);
    wprintw(curr_frame, "%s", payload);
    free(payload);
    print_panels();
}

/**
 * \brief Handler for KEY_DOWN in manager mode.
 *
 * \return no value.
 */
void mdown(void)
{
    char *payload;
    size_t size;
    
    if (sllist_next_node(curr_tab)) {
        return;
    } else if (curr_frame == windows[3]) {
        mvwin(curr_frame, ++Y1, 1);
        payload = (char *) sllist_get_curr(curr_tab, &size);      
        top_panel(panels[1]);
        top_panel(panels[3]);
    } else {
        mvwin(curr_frame, ++Y2, COLS / 2 + 1);
        payload = (char *) sllist_get_curr(curr_tab, &size);
        top_panel(panels[2]);
        top_panel(panels[4]);
    }
    payload[size] = '\0';
    wclear(curr_frame);
    wprintw(curr_frame, "%s", payload);
    free(payload);
    print_panels();
}

/**
 * \brief Handler for KEY_LEFT in manager mode.
 *
 * \return no value.
 */
void mleft(void)
{
    ;
}

/**
 * \brief Handler for KEY_RIGHT in manager mode.
 *
 * \return no value.
 */
void mright(void)
{
    ;
}

/**
 * \brief Handler for KEY_ESC in manager mode.
 *
 * \return no value.
 */
void mesc(void)
{
    int ch;

    ch = getch();
    if (ch == 'y' || ch == 'Y') {
        stop_readkey();
    }
}

/**
 * \brief Handler for KEY_ENTER in manager mode.
 *
 * \return no value.
 */
void menter(void)
{
    char *command, *payload;
    size_t size, len;
    int test, i;
    FILE *fp;

    payload = (char *) sllist_get_curr(curr_tab, &size);
    payload[size] = '\0';
    
    len = strlen(curr_pd);
    memcpy((void *) (curr_pd + len + 1), (const void *) payload,
           (size + len) * sizeof(char));
    curr_pd[len] = '/';
    curr_pd[size + len + 1] = '\0';
    
    command = (char *) malloc((10 + size + len) * sizeof(char));
    memcpy((void *) command, (const void *) "test -d ", 8 * sizeof(char));
    memcpy((void *) (command + 8), (const void *) curr_pd,
           (size + len + 1) * sizeof(char));
    command[size + len + 9] = '\0';
    system(command);
    free(command);
    
    system("echo $? > /tmp/.test_tmp");

    fp = fopen("/tmp/.test_tmp", "r");
    if (fp == NULL) return;
    fscanf(fp, "%d", &test);
    fclose(fp);
    
    if (test == 0) {
        if (strcmp((const char *) payload, ".") == 0) {
            curr_pd[len] = '\0';
        } else if (strcmp((const char *) payload, "..") == 0) {
            for (i = len - 1; curr_pd[i] != '/'; --i);
            curr_pd[i] = '\0';
        }
        open_dir(curr_pd, curr_tab);
    } else {
        curr_pd[len] = '\0';
    }

    print_panels();
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
    case MANAGER:
        set_handler(mup, KEY_UP);
        set_handler(mdown, KEY_DOWN);
        set_handler(mleft, KEY_LEFT);
        set_handler(mright, KEY_RIGHT);
        set_handler(mesc, KEY_ESC);
        set_handler(menter, MY_KEY_ENTER);
        /* set_handler(mf2, KEY_F(2)); */
        /* set_handler(mtab, KEY_TAB); */
        break;
    case EDITOR:
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


/*********************************************************/
/* Functions file manager                                */
/*********************************************************/


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
 * 1 window is fist panel;
 * 2 window is second panel;
 * 3 window is frame for selected file in tab_1;
 * 4 window is frame for selected file in tab_2;
 * 5 window is file redactor.
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

    Y1 = 2;
    windows[3] = newwin(1, COLS / 2 - 2, Y1, 1);
    wbkgdset(windows[3], COLOR_PAIR(3));
    wclear(windows[3]);
    wrefresh(windows[3]);

    Y2 = 2;
    windows[4] = newwin(1, COLS - COLS / 2 - 2, Y2, COLS / 2 + 1);
    wbkgdset(windows[4], COLOR_PAIR(3));
    wclear(windows[4]);
    wrefresh(windows[4]);
    
    windows[5] = newwin(LINES, COLS, 0, 0);
    wbkgdset(windows[5], COLOR_PAIR(1));
    wclear(windows[5]);
    wrefresh(windows[5]);
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
    
    for (i = 0; i < 6; ++i)
        panels[i] = new_panel(windows[i]);

    bottom_panel(panels[5]);
    
    /* Connect panels 3 and 4 to switch */
    set_panel_userptr(panels[3], panels[4]);
    set_panel_userptr(panels[4], panels[3]);
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
    struct sllist tab_1, tab_2;
    char pd1[256], pd2[256];
    FILE *fp;
    
    if (init_scr()) {
        fprintf(stderr, "Error into init_scr()...\n");
        return 1;
    }

    if (init_colors()) {
        fprintf(stderr, "Error: not support colors!\n");
        return 1;
    }

    system("pwd > /tmp/.pwd_tmp");
    fp = fopen("/tmp/.pwd_tmp", "r");
    fscanf(fp, "%s", pd1);
    fclose(fp);
    memcpy((void *) pd2, (const void *) pd1, 256 * sizeof(char));
    
    init_windows();
    init_panels();
    set_mode(MANAGER);

    sllist_init(&tab_1);
    sllist_init(&tab_2);
    curr_window = windows[2];
    curr_frame = windows[4];
    open_dir(pd1, &tab_2);
    curr_window = windows[1];
    curr_frame = windows[3];
    open_dir(pd2, &tab_1);
    curr_tab = &tab_1;
    curr_pd = pd1;
    print_panels();
    start_readkey();

    sllist_free(&tab_1);
    sllist_free(&tab_2);
    
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

    stop_readkey();
    
    for (i = 0; i < 4; ++i) {
        del_panel(panels[i]);
        delwin(windows[i]);
    }
    
    endwin();
}

