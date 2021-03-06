/*CS533 Course Project
 * Thread Queue ADT
 * queue.h
*/

struct queue_node
{
  struct thread *t;
  struct queue_node *next;  
};

struct queue
{
  struct queue_node *head;
  struct queue_node *tail;
};


void thread_enqueue(struct queue * q, struct thread * t);

struct thread * thread_dequeue(struct queue * q);

int is_empty(struct queue * q);
