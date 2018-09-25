/** \file */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>



/**
 * \brief Data structure for describe command
 *
 * The "cmd" field stores the command
 * The "argv" field stores the arguments vector of this command
 */
struct command_t {

    char *cmd;
    char **argv;
    
};


/**
 * \brief Data structure for describe command set
 *
 * The "set" field stores the command set command_t type
 * The "quantity" field displays the quantity of commands in the set
 */
struct command_set_t {

    struct command_t *set;
    int quantity;

};


/**
 * \brief This function splits the input command string into commands and their
 * arguments
 *
 * \param "command_set" is a pointer to command_set_t type variable in which
 * all commands and their arguments will be stored
 * \param "str" is at array of char type which is the input command string
 *
 * \return no return value
 */
void string_command_parser(struct command_set_t *command_set, char *str)
{
    int i, cmd_flg, argc;
    size_t l;
    char buf[256];
    
    command_set->set = NULL;
    command_set->quantity = 0;
    cmd_flg = 1;
    
    for (i = 0, l = 0; str[i] != '\0'; ++i) {
        buf[l] = str[i];
        if (str[i] == '|') {
            buf[l++] = '\0';
            if (cmd_flg) {
                command_set->set = (struct command_t *)
                    realloc (command_set->set, sizeof (struct command_set_t) *
                             (command_set->quantity + 1));
                command_set->set[command_set->quantity].cmd = (char *)
                    malloc (l);
                memcpy(command_set->set[command_set->quantity].cmd, &buf, l);
                argc = 0;
                command_set->set[command_set->quantity].argv = (char **)
                    malloc (sizeof(char *));
                command_set->set[command_set->quantity].argv[argc] = (char *)
                    malloc (l + 5);
                memcpy(command_set->set[command_set->quantity].argv[argc],
                       "/bin/", 5);
                memcpy(command_set->set[command_set->quantity].argv[argc] + 5,
                       &buf, l);
            } else if (l > 1) {
                command_set->set[command_set->quantity].argv = (char **)
                    realloc (command_set->set[command_set->quantity].argv,
                             sizeof(char *) * (argc + 1));
                command_set->set[command_set->quantity].argv[argc] = (char *)
                    malloc (l);
                memcpy(command_set->set[command_set->quantity].argv[argc],
                       &buf, l);
            }
            command_set->set[command_set->quantity].argv = (char **)
                realloc (command_set->set[command_set->quantity].argv,
                         sizeof(char *) * (argc + 1));
            command_set->set[command_set->quantity].argv[argc] = NULL;
            l = 0;
            ++argc;
            ++command_set->quantity;
            cmd_flg = 1;
        } else if (str[i] == ' ' && l > 0) {
            buf[l++] = '\0';
            if (cmd_flg) {
                cmd_flg = 0;
                command_set->set = (struct command_t *)
                    realloc (command_set->set, sizeof(struct command_set_t) *
                             (command_set->quantity + 1));
                command_set->set[command_set->quantity].cmd = (char *)
                    malloc (l);
                memcpy(command_set->set[command_set->quantity].cmd, &buf, l);
                argc = 0;
                command_set->set[command_set->quantity].argv = (char **)
                    malloc (sizeof(char *));
                command_set->set[command_set->quantity].argv[argc] = (char *)
                    malloc (l + 5);
                memcpy(command_set->set[command_set->quantity].argv[argc],
                       "/bin/", 5);
                memcpy(command_set->set[command_set->quantity].argv[argc] + 5,
                       &buf, l);
            } else {
                command_set->set[command_set->quantity].argv = (char **)
                    realloc (command_set->set[command_set->quantity].argv,
                             sizeof(char *) * (argc + 1));
                command_set->set[command_set->quantity].argv[argc] = (char *)
                    malloc (l);
                memcpy(command_set->set[command_set->quantity].argv[argc],
                       &buf, l);
            }
            l = 0;
            ++argc;
        } else if (str[i] != ' ') {
            ++l;
        }
    }
    buf[l++] = '\0';
    if (cmd_flg) {
        command_set->set = (struct command_t *)
            realloc (command_set->set, sizeof(struct command_set_t) *
                     (command_set->quantity + 1));
        command_set->set[command_set->quantity].cmd = (char *)
            malloc (l);
        memcpy(command_set->set[command_set->quantity].cmd, &buf, l);
        argc = 0;
        command_set->set[command_set->quantity].argv = (char **)
            malloc (sizeof(char *));
        command_set->set[command_set->quantity].argv[argc] = (char *)
            malloc (l + 5);
        memcpy(command_set->set[command_set->quantity].argv[argc],
               "/bin/", 5);
        memcpy(command_set->set[command_set->quantity].argv[argc] + 5,
               &buf, l);
    } else if (l > 1) {
        command_set->set[command_set->quantity].argv = (char **)
            realloc (command_set->set[command_set->quantity].argv,
                     sizeof(char *) * (argc + 1));
        command_set->set[command_set->quantity].argv[argc] = (char *)
            malloc (l);
        memcpy(command_set->set[command_set->quantity].argv[argc],
               &buf, l);
    }
    ++argc;
    command_set->set[command_set->quantity].argv = (char **)
        realloc (command_set->set[command_set->quantity].argv,
                 sizeof(char *) * (argc + 1));
    command_set->set[command_set->quantity].argv[argc] = NULL;
    ++command_set->quantity;
}


/**
 * \brief This main function of task
 *
 * \param "argc" is a counter of the command string parametrs
 * \param "argv" is a command string in format 
 * "cmd <arg> ... <arg> <|> cmd <arg> ... <arg> ...".
 * The command string must be in double qutes! The quntity 
 * a commands and their argument is unlimited, but maximum
 * total length of the one command (with their arguments) is
 * 256 characters 
 *
 * \return 0 on success or 1 on failure
 */
int main(int argc, char *argv[])
{
    struct command_set_t command_set;

    int i, j, status, **fd;
    pid_t cp;
    
    if (argc < 2) {
        printf("No commands!\n");
        return 1;
    }

    string_command_parser(&command_set, argv[1]);
    
    if (command_set.quantity == 1) {
        cp = fork();
        if (cp == 0) {
            execvp(command_set.set[0].cmd, command_set.set[0].argv);
        }
        waitpid(cp, &status, 0);
    } else {
        fd = (int **) malloc (sizeof(int *) * (command_set.quantity - 1));
        for (i = 0; i < command_set.quantity - 1; ++i) {
            fd[i] = (int *) malloc (sizeof(int) * 2);
            pipe(fd[i]);
        }

        cp = fork();
        if (cp == 0) {
            dup2(fd[0][1], 1);
            close(fd[0][0]);
            execvp(command_set.set[0].cmd, command_set.set[0].argv);
        } else {
            close(fd[0][1]);
            waitpid(cp, &status,0);
        }
        
        for (i = 1; i < command_set.quantity - 1; ++i) {
            cp = fork();
            if (cp == 0) {
                dup2(fd[i - 1][0], 0);
                dup2(fd[i][1], 1);
                close(fd[i][0]);
                execvp(command_set.set[i].cmd, command_set.set[i].argv);
            } else {
                close(fd[i][1]);
                waitpid(cp, &status, 0);
            }
        }

        cp = fork();
        if (cp == 0) {
            dup2(fd[i - 1][0], 0);
            execvp(command_set.set[i].cmd, command_set.set[i].argv);
        } else {
            waitpid(cp, &status,0);
        }

        for (i = 0; i < command_set.quantity - 1; ++i) {
            free(fd[i]);
        }
        free(fd);
    }

    for (i = 0; i < command_set.quantity; ++i) {
        for (j = 0; command_set.set[i].argv[j] != NULL; ++j) {
            free(command_set.set[i].argv[j]);
        }
        free(command_set.set[i].argv);
    }
    free(command_set.set);
    
    return 0;
}
