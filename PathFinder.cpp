#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include "Screen.h"
#include "Common.dat"
#include "Data.dat"

ESSAGE Message;
ESSAGEMAX Trajet;
int idQ;

int Recherche(int, int, int, int[], int[], int *);
void AffChemin(int[], int);

int main(int argc, char *argv[])
{
    Trace("Dans recherche");
    int rc;
    int CheminSuivit[55];
    int CheminOptimum[55];
    int TailleChemin = 0;
    int Destination;
    idQ = atoi(argv[1]);
    if ((rc =
	 msgrcv(idQ, &Message, sizeof(MESSAGE) - sizeof(long), getpid(),
		0)) == -1) {
	perror("Err. de msgrcv()");
	exit(1);
    }
    Trajet.lType = Message.idProcess;
    Destination = 29;		// A mofifier en fonction de la destination
    Trace("\tDebut de la recherche: % d  vers %d", Message.Depart, Destination);	// pour les tests
    Recherche(Message.Depart, Destination, 0, CheminSuivit,	/* ???? */
	      &(CheminOptimum[1]), &TailleChemin);
    Trace("\tAffichage du resultat (taille %d)", TailleChemin);
    CheminOptimum[0] = Message.Depart;
    AffChemin(CheminOptimum, TailleChemin + 1);
    Trace("\tResultat afficher");
    Trajet.Message[0] = Message.Depart;
    memcpy(Trajet.Message, CheminOptimum,
	   (TailleChemin + 1) * sizeof(int));

    if (msgsnd
	(idQ, &Trajet,
	 sizeof(int) * (TailleChemin + 1) + sizeof(pid_t) + sizeof(int),
	 0) == -1) {
	perror("Err de msgsnd()");
	exit(1);
    }
    exit(0);
}

int Recherche(int NoeudCourant, int NoeudDestination, int TailleActuelle,
	      int CheminSuivit[], int CheminOptimum[], int *TailleChemin)
{
    int rc, Mrc, i;

    if (Noeud[NoeudCourant].Visite)
	return 0;
    if (NoeudCourant == NoeudDestination) {
	if (TailleActuelle < *TailleChemin || *TailleChemin == 0) {
	    memcpy(CheminOptimum, CheminSuivit,
		   TailleActuelle * sizeof(int));
	    *TailleChemin = TailleActuelle;
	    return 1;
	}
	return 0;
    }
    Noeud[NoeudCourant].Visite = 1;

    i = 0;
    while (i < 6 && Noeud[NoeudCourant].Suivant[i] != 0)	// ????
    {
	CheminSuivit[TailleActuelle] = Noeud[NoeudCourant].Suivant[i];
	rc = Recherche(Noeud[NoeudCourant].Suivant[i],
		       NoeudDestination, TailleActuelle + 1,
		       CheminSuivit, CheminOptimum, TailleChemin);
	if (rc != 0)
	    Mrc = rc;
	i++;
    }
    Noeud[NoeudCourant].Visite = 0;
    return Mrc;
}

void AffChemin(int aChemin[], int TailleChemin)
{
    int i = 0;
    char szBuffer[80];
    char szBuffer1[80];

    sprintf(szBuffer, "(%d)   ", TailleChemin);
    while (i < TailleChemin) {
	sprintf(szBuffer1, "%d ", aChemin[i++]);
	strcat(szBuffer, szBuffer1);
    }
    Trace("\t(%d) %s", getpid(), szBuffer);
    return;
}
