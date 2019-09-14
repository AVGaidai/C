#ifndef FILE_MANAGER_H
#define FILE_MANAGET_H

#include <ncurses.h>
#include <panel.h>


/**
 * \brief Function print current panels.
 *
 * \return no value.
 */
void print_panels(void);

/**
 * \brief Function initialization file maneger.
 *
 * \return the integer 1 upon failure and 0 upon successful completion.
 */
int init_file_manager(void);

/**
 * \brief Function delete all panels and windows
 *
 * \return no value.
 */
void exit_file_manager(void);


#endif
