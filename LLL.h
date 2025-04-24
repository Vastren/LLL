#ifndef LLL_H
#define LLL_H

#include "vecteur.h"

/* --------------------- Algorithme LLL --------------------- */

void gram_schmidt(reseau reseau, double** u, double* a) ;
void reduction(reseau reseau, double** u, int k, int l) ;
void echanger(reseau reseau, double** u, double* a, int k) ;
void LLL(reseau reseau) ;

/* --------------------- Fonctions d'exemples et de tests --------------------- */

void print_exemple(double** base, int n) ;
void batterie_de_test(int k) ;


#endif
