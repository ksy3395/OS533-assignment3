#include<stdio.h>
#include<stdlib.h>

#include"scheduler.h"
#include"queue.h"
#define STACK_SIZE 1048576


struct thread *current_thread, *new_thread,*next_thread;
struct queue ready_list;

void threadswitch(thread *old, thread *new);
void threadstart(thread *old, thread *new);

void yield()
{

     	
    if (current_thread->state != DONE)
	{
		current_thread->state = READY;
       
                thread_enqueue(&ready_list, current_thread);
	}
       
         next_thread = thread_dequeue(&ready_list);

         next_thread->state = RUNNING;

     struct thread *temp = current_thread;
		current_thread = next_thread;
 		next_thread = temp;

      	threadswitch(next_thread,current_thread);

        if (next_thread->state == DONE)
        {
              free((next_thread->stack_base));
              free(next_thread);
	    	
	      printf("\nIn free");	
	
        }
       	
} 

void thread_wrap()
{

 current_thread->initial_function(current_thread->initial_argument1); 

 current_thread->state = DONE;

 yield();
}

void scheduler_begin()
{
    
    current_thread = (thread*)malloc(sizeof(thread));

    current_thread->stack_base = malloc(STACK_SIZE);
 
    current_thread->stack_pointer = (current_thread->stack_base) + STACK_SIZE;
	
    current_thread->state = RUNNING;
    
    ready_list.head = NULL;
 
    ready_list.tail = NULL;
}

void scheduler_end()
{

     while(is_empty(&ready_list)== 0)

	{
  
		yield();

	}
}    


void thread_fork(void(*target)(void*), void *arg )
{
	new_thread = (thread*)malloc(sizeof(thread));
	
        new_thread->stack_base = malloc(STACK_SIZE);

        new_thread->stack_pointer = (new_thread->stack_base) + STACK_SIZE;

	new_thread->initial_argument1 = arg;
 
        new_thread->initial_function = target;

	current_thread->state = READY;
        
        thread_enqueue(&ready_list,current_thread);

        new_thread->state = RUNNING;

        struct thread *temp = current_thread;

       current_thread = new_thread;

     new_thread = temp;

	threadstart(new_thread,current_thread);
}


      
		 

