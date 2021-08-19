#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Process: Each process has a name and has an execution time.
 *          We keep track of how long the process still needs
 *          to run on the processor. "remaining_time" is the
 *          remaining execution time of the process.
 */
typedef struct
{
    char *name;
    int starting_time;
    int remaining_time;
} Process;
/*
 *
 */
typedef struct Node
{
    Process data;
    struct Node* next;
} Node;
/*
 *
 */
typedef struct
{
    Node* Head;
    Node* Tail;
} Queue;
/*
 *
 */
Node* newNode(Process data)
{
    Node* n = malloc(sizeof(Node));
    n->next = NULL;
    n->data = data;

    return n;
}
/*
*
*/
Queue* init()
{
    Queue* q = malloc(sizeof(Queue));
    q->Head = NULL;
    q->Tail = NULL;
    return q;
}
/*
 *
 */
int isEmpty(Queue *q)
{
    if(q->Tail  == NULL)
    {
        return 1;
    }
    else return 0;
}
/*
 *
 */
Process dequeue(Queue *q)
{
    Node *temp = q->Head;
    if(!q->Head) printf("Error occured. Underflow.");
    else if(q->Head->next == NULL) //Only one element in queue
    {
        q->Tail = NULL;
        q->Head = NULL;
    }
    else q->Head = q->Head->next;
    Process x = temp->data;
    free(temp);
    return x;
}
/*
 *
 */
void enqueue(Queue *q, Process x)
{
    Node *n = newNode(x);
    if (!n) return;
    if(q->Head == NULL) // we are adding the first element
    {
        q->Tail = n;
        q->Head=n;
    }
    else
    {
        q->Tail->next=n;
        q->Tail=n;
    }
}
/*
 *
 */
void destroy(Queue *q)
{
    while(q->Head != NULL)
    {
        Node* temp = q->Head;
        q->Head = q->Head->next;
        free(temp);
    }
    free(q->Head);
    free(q->Tail);
    free(q);
}
/*
 * RoundRobin Scheduling
 */
void RoundRobin(char* filename)
{
    Queue* q = init();
    int time_slots;
    int number_of_processes = 0;
    int current_time = 0;
    Process arr[100];
    FILE* fp = fopen(filename, "r");
    if(!fp)
    {
        printf("ERROR! CANNOT OPEN FILE!\n");
        return;
    }
    char* garbage;
    if(!fgets(garbage, 23, fp))
    {
        printf("ERROR! CHECK FILE FORMAT!\n");
        return;
    }
    fscanf(fp, "%d", &time_slots);
    while(!feof(fp))
    {
        arr[number_of_processes].name = malloc(20);
        fscanf(fp, "%s %d %d", arr[number_of_processes].name, &arr[number_of_processes].starting_time, &arr[number_of_processes].remaining_time);
        number_of_processes++;
    }
    while(current_time < time_slots)
    {
        for(int i = 0; i < number_of_processes; i++)
        {
            if(arr[i].starting_time == current_time)
            {
                enqueue(q, arr[i]);
            }
        }
        if(!isEmpty(q))
        {
            Process temp = dequeue(q);
            printf("%s   (%d-->%d)", temp.name, current_time, current_time + 1);
                        temp.remaining_time--;
            if(temp.remaining_time > 0)
            {
                printf("\n");
                enqueue(q, temp);
            }
            else
            {
                printf(" %s aborts\n", temp.name);
            }
        }
        else if(isEmpty(q))
        {
            printf("idle (%d-->%d)\n", current_time, current_time + 1);
        }
        current_time++;
    }

}
/*
 *
 */

int main()
{
    char filename[261];
    puts("Enter file name or Ctrl+Z to exit:");
    puts("----------------------------------");
    while(fgets(filename, 260, stdin) != NULL)
    {
        filename[strlen(filename)-1]='\0';
   //     if(fopen(filename,"r"))
            RoundRobin(filename);

     /*   else
        {
            puts("File Not Found!");
            puts("----------------------------------");
        }*/
        puts("Enter file name or Ctrl+Z to exit:");
        puts("----------------------------------");
    }

    return 0;
}


