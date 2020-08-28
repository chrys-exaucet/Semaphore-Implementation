
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#include"semaphore.h"

int main()
{


  int choix , reponse;
  int i =0 ;
int j=0;
sharedResource=0;
Semaphore sem ;

 semInitialiser(&sem);

Node processus [15];



do
{
        system("cls");
        system("color 0D");


        printf("\n|*************************************************************************************************|\n");
        printf("\n|*************************************************************************************************|\n");
        printf("\n|            1:   Ajout de nouveaux processus concurents                                          |\n");
        printf("\n|            2:   Liberation de la ressource                                                      |\n");
        printf("\n|            3:    Visualisation de la file d'attente                                             |\n");
        printf("\n|            4:    Quitter                                                                        |\n");
        printf("\n**************************************************************************************************\n");



        printf(" Entrer votre choix :  ");
        scanf("%d",&choix);

        system("cls");
        system("color 8F");



        switch(choix)
        {
/*********************************************sortie du programme********************************************************/
            case 0 :
                        system("color 0A");

                        printf("\n A bientot\n");
                        exit(0);

                        break ;
/**********************************************************************************************************************/


           case 1 :

                       processus[i] =processusInitialiser() ;
                       showProcessus(processus[i]);

                       outOfMyCriticalRegion(processus [i]);
                        P(&sem,processus [i]);

                        if((sem.waitingQueue.counter==0 )|| sem.counter>0)
                        {

                            inMyCriticalRegion(processus[i]);
                            j=i;
                        }


                        else
                        {
                            printf("\nThe shared resource is used. You are going to the semaphore waiting queue\n");

                        }

                        i++;
                        break ;
/********************************************vérification de l'état de la file***************************************/

            case 2 :
                        system("color 0C") ;

                        if(sem.waitingQueue.counter==0)
                            {
                               printf(" shared resource already  available\n");
                            }
                        else
                            {

                                V(&sem);
                                outOfMyCriticalRegion(processus [j]);
                                printf(" shared resource now  available       \n");// ressource libérée et processus suivant la prend
                               P(&sem,*(sem.waitingQueue.out));
                               inMyCriticalRegion(*(sem.waitingQueue.out));

                            }


                        break ;

/*******************************************Enfilage****************************************************/

            case 3 :

                        showSemaphoreState(sem);
                        break;



/**********************************************invalidation de l'entree******************************************/

            default:
                        system("color 0B") ;

                        printf("entree invalide\n");
                        break;

        }
/***************************************************************************************************************/

    printf("\n Entrer 1 pour retourner au menu principal:  ");
    scanf("%d",&reponse);


}while(reponse==1);     // condition de continuité
return 0 ;
}


