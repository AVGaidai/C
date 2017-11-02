

struct key_module_env {

    pthread_t thr;
    void (*handler_up)    ();
    void (*handler_down)  ();
    void (*handler_left)  ();
    void (*handler_right) ();
