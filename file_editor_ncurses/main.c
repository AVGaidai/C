#include "file_manager.h"


int main(int argc, char *argv[])
{
    if (init_file_manager())
        return 0;
    
    exit_file_manager();

    return 0;
}
