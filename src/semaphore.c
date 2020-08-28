#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include"semaphore.h"



void semInitialiser(Semaphore* sem)
{
    sem->counter=1;
    sem->waitingQueue=queueSemInitialiser();
}

/**************************************************/

Queue queueSemInitialiser()
{
    Queue queue ;
    queue.in = NULL ;
    queue.out = NULL ;
    queue.counter = 0 ;
    return queue ;
}

/****************************************************/
void semEnfiler(Queue * r_queue, Node node)
{
     Node * ptrNode ;
     ptrNode = ( Node * ) malloc ( sizeof ( Node ) ) ;
     *ptrNode= node ;
     ptrNode->suivant = NULL ;
     r_queue->counter ++ ;
if (r_queue->counter == 1 )
    {
        r_queue->in = ptrNode ;
        r_queue->out = ptrNode;
    }
else
    {
         r_queue->in->suivant = ptrNode ;
         r_queue->in = ptrNode ;
    }

}


/**********************************************************/
Node* lireTete(Queue queue)
{
    return queue.out ;
}

/************************************************************/
int semEstVide(Queue queue)
{
    if(queue.counter==0)
        return 1;
    else
        return 0;
}
/*************************************************************/

void  semDefiler(Queue * r_queue)
{
    Node * q ;
    if ( 1 != semEstVide( *r_queue ) )
        {
            q =r_queue->out ;
            r_queue->out = q->suivant ;
            free ( q ) ;
            r_queue->counter -- ;
            if ( r_queue->counter == 0 )
                {
                    r_queue->in = NULL ;
                }

        }
}

/************************************************/
void  semVider(Queue * r_queue)
{
    if(1==semEstVide(* r_queue))
    {
        return ;
    }
        else
        {
            semDefiler(r_queue);
            semVider(r_queue);
        }

}
/***********************************operation sur le semaphore*****************/
void P(Semaphore * sem, Node processus)
{

    sem->counter=(sem->counter)-1;
    if(0>sem->counter)
              semEnfiler(&(sem->waitingQueue),processus);

}
/*******************************************/

void V(Semaphore * sem)
{

sem->counter=(sem->counter)+1;

    if(0>sem->counter)
              semDefiler(&(sem->waitingQueue));


}
/**********************************************/

void showSemaphoreState(Semaphore sem)
{


printf("%d process in the semaphore waiting queue.\n", sem.waitingQueue.counter);
 afficher( (sem.waitingQueue)) ;

}
/********************************************/

void afficher ( Queue  queue )
 {
      Node * p;
      p = queue.out ;
     while ( p != NULL )
        {
            showProcessus(*p);
            p = p->suivant ;
        }
}
/*************************************************/

void inMyCriticalRegion(Node nodeProcessus)
{

sharedResource++;
printf("Process: ");
showProcessus( nodeProcessus);
printf(" \t is runing in the critical region \n ");
printf("\t the shared ressource is updated : %d \n", sharedResource);

}
/*******************************************************/

void outOfMyCriticalRegion(Node nodeProcessus)
{
printf("Process: ");
showProcessus( nodeProcessus);
printf(" \t is runing out of the critical region \n ");
}
/*************************************************/

Node processusInitialiser()
{
    Node nodeProcessus;

printf("Enter the processus characteristics\n");

                        printf("id:  ");
                        scanf("%d",&(nodeProcessus.processus.id));

                        printf("\n program name  :  ");
                        scanf("%s",&nodeProcessus.processus.programName);

                        printf("\n priority :  ");
                        scanf("%d",&nodeProcessus.processus.priority);

                        printf("\n execution time:    ");
                        scanf("%d",&nodeProcessus.processus.executionTime);

nodeProcessus.suivant=NULL;
    return nodeProcessus;
}
/*******************************************/

void showProcessus(Node node)
{
    printf("{\"id\":%d," "\"program name\":%s,""\"priority\":%d,""\"execution time\":%d}\n",node.processus.id,node.processus.programName,node.processus.priority,node.processus.executionTime);
}


/***************************FIN*****************************/
