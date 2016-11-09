typedef enum
{

 RUNNING,
 READY,
 BLOCKED,
 DONE 
}state_thread;


typedef struct thread{

unsigned char *stack_pointer;
unsigned char *stack_base;
void (*initial_function)(void*); 
void *initial_argument1;
state_thread state;

}thread;

void scheduler_begin();
void thread_fork(void(*target)(void*),void *arg);
void yield();
void scheduler_end();

extern struct thread *current_thread;








