#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>


struct command_t {

    char *cmd;
    char **argv;
};


struct command_set_t {

    struct command_t *set;
    int quantity;

};


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
                    realloc (command_set->set, command_set->quantity + 1);
                command_set->set[command_set->quantity].cmd = (char *)
                    malloc (l);
                memcpy(command_set->set[command_set->quantity].cmd, &buf, l);
                argc = 0;
                command_set->set[command_set->quantity].argv = (char **)
                    malloc (sizeof(char *));
            } else if (l > 0) {
                command_set->set[command_set->quantity].argv = (char **)
                    realloc (command_set->set[command_set->quantity].argv,
                             sizeof(char *) * (argc + 1));
                command_set->set[command_set->quantity].argv[argc] = (char *)
                    malloc (l);
                memcpy(command_set->set[command_set->quantity].argv[argc],
                       &buf, l);
                ++argc;
            }
            command_set->set[command_set->quantity].argv = (char **)
                realloc (command_set->set[command_set->quantity].argv,
                         sizeof(char *) * (argc + 1));
            command_set->set[command_set->quantity].argv[argc] = NULL;
            l = 0;
            ++command_set->quantity;
            cmd_flg = 1;
        } else if (str[i] == ' ' && l > 0) {
            buf[l++] = '\0';
            if (cmd_flg) {
                cmd_flg = 0;
                command_set->set = (struct command_t *)
                    realloc (command_set->set, command_set->quantity + 1);
                command_set->set[command_set->quantity].cmd = (char *)
                    malloc (l);
                memcpy(command_set->set[command_set->quantity].cmd, &buf, l);
                argc = 0;
                command_set->set[command_set->quantity].argv = (char **)
                    malloc (sizeof(char *));
            } else {
                command_set->set[command_set->quantity].argv = (char **)
                    realloc (command_set->set[command_set->quantity].argv,
                             sizeof(char *) * (argc + 1));
                command_set->set[command_set->quantity].argv[argc] = (char *)
                    malloc (l);
                memcpy(command_set->set[command_set->quantity].argv[argc],
                       &buf, l);
                ++argc;
            }
            l = 0;
        } else if (str[i] != ' ') {
            ++l;
        }
    }
    buf[l++] = '\0';
    if (cmd_flg) {
        command_set->set = (struct command_t *)
            realloc (command_set->set, command_set->quantity + 1);
        command_set->set[command_set->quantity].cmd = (char *)
            malloc (l);
        memcpy(command_set->set[command_set->quantity].cmd, &buf, l);
        argc = 0;
        command_set->set[command_set->quantity].argv = (char **)
            malloc (sizeof(char *));
    } else {
        command_set->set[command_set->quantity].argv = (char **)
            realloc (command_set->set[command_set->quantity].argv,
                     sizeof(char *) * (argc + 1));
        command_set->set[command_set->quantity].argv[argc] = (char *)
            malloc (l);
        memcpy(command_set->set[command_set->quantity].argv[argc],
               &buf, l);
        ++argc;
    }
    command_set->set[command_set->quantity].argv = (char **)
        realloc (command_set->set[command_set->quantity].argv,
                 sizeof(char *) * (argc + 1));
    command_set->set[command_set->quantity].argv[argc] = NULL;
    ++command_set->quantity;
}


int main(int argc, char *argv[])
{
    struct command_set_t command_set;

    int i, j, fd[2];
    pid_t p;
    
    printf("%d\n", argc);
    if (argc < 2) {
        printf("No commands!\n");
        return 0;
    }

    string_command_parser(&command_set, argv[1]);

    for (i = 0; i < command_set.quantity; ++i) {
        printf("%s ", command_set.set[i]);
        for (j = 0; command_set.set[i].argv[j] != NULL; ++j) {
            printf("%s ", command_set.set[i].argv[j]);
        }
        printf("\n");
    }

    pipe(fd);
    close(fd[0]);
    close(fd[1]);
    
    
    /* for (i = 0; i < command_set.quantity; ++i) { */
    /*     fork(); */
    /*     if (getpid() != p) { */
    /*         dup2(fd[0], 0); */
    /*         close(fd[0]); */
    /*         close(fd[1]); */
            execvp(command_set.set[i].cmd, command_set.set[i].argv);
    /*         break; */
    /*     } */
    /* } */

    /* if (getpid() == p) */
    /*     wait(&i); */
    
    return 0;
}
