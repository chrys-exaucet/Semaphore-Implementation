#ifndef SEMAPHORE_H_INCLUDED
#define EXAMEN_H_INCLUDED

/* déclaration de la ressource partagée*/
int sharedResource;

/* structure d'un processus */

typedef struct processus
 {
    char programName[20];
    int id;
    int executionTime;
    int priority ;
    struct processus * suivant ;

 }Processus ;

typedef Processus DataType;

/* node*/

typedef struct node
 {
     DataType processus;
    struct node * suivant;
 }Node;


 typedef struct queue
{
     int counter ;
      Node  * in ;
      Node * out ;
}Queue ;



typedef struct semaphore
 {
    int counter ;
    Queue waitingQueue ;

 }Semaphore;

 /****************************************************/

void semInitialiser(Semaphore* sem);
Queue queueSemInitialiser();
void semEnfiler(Queue * r_queue, Node node);
int semEstVide(Queue queue);

Node * lireTete(Queue queue);
void  semDefiler(Queue * r_queue);
void  semVider(Queue * r_queue);


void afficher ( Queue  queue );
/*Operation sur le sémaphore */

void P(Semaphore * sem, Node processus);
void V(Semaphore * sem);


void showSemaphoreState(Semaphore sem);
void inMyCriticalRegion(Node nodeProcessus);
void outOfMyCriticalRegion(Node nodeProcessus);

Node processusInitialiser();
void showProcessus(Node processus);

#endif // SEMAPHORE_H_INCLUDED
