/* Exercice 1 :
   Denys MERCENIER
   Screen.h
*/

#ifndef        ECRAN_H
#define        ECRAN_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define        NORM      0
#define        GRAS      1

#ifdef CPP
#include <iostream>
using namespace std;
#else
#endif

#include <stdarg.h>


/* fonctions simplifiees de gestion d'ecran */

void EffScreen(void);
int LitChaine(char *, int, int, int, int);
int LitEntier(int *, int, int, int, int);
void AffChaine(const char *, int, int, int);
void Pause(void);
void Trace1(const char *, int, const char *, ...);

#define Trace(...) Trace1(__FILE__,__LINE__,__VA_ARGS__)

void Affiche(const char *, ...);
void SortieErreur(char *, int);
void SauveCurseur(void);
void RestitueCurseur(void);

#endif				/* _ECRAN_H_ */
