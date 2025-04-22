#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include "vecteur.h"


/* --------------------- Fonctions vectorielles --------------------- */


/* Calcul du produit scalaire de deux vecteurs de taille n */
double pdt_scalaire (double* v1, double* v2, int n) {
    double pdt = 0 ;
    for (int i=0 ; i<n ; i++) {
        pdt += v1[i]*v2[i] ;
    }
    return pdt ;
}

/* Calcul de la norme d’un vecteur de taille n */
double norme (double* v, int n) {
    return sqrt(pdt_scalaire(v, v, n)) ;
}

/* Multiplication d’un vecteur de taille n par un scalaire, le résultat est ajouté dans 'resultat'*/
void multiplication_vecteur (double* v, double scalaire, double* resultat, int n) {
    for (int i=0 ; i<n ; i++) {
        resultat[i] = scalaire*v[i] ;
    }
}

/* Addition de deux vecteurs de taille n, le résultat est ajouté dans 'resultat' */
void somme_vecteur (double* v1, double* v2, double* resultat, int n) {
    for (int i=0 ; i<n ; i++) {
        resultat[i] = v1[i]+v2[i] ;
    }
}

/* Soustraction de deux vecteurs de taille n, le résultat est ajouté dans 'resultat' */
void soustraction_vecteur (double* v1, double* v2, double* resultat, int n) {
    for (int i=0 ; i<n ; i++) {
        resultat[i] = v1[i]-v2[i] ;
    }
}

/* --------------------- Fonctions du réseau --------------------- */

/* Initialise un réseau */
reseau initialiser_reseau (double** base, int len) {
    reseau r = {.base = base, .len = len} ;
    return r ;
}

/* Renvoie la taille du réseau */
int length (reseau reseau) {
    return reseau.len ;
}

/* Supprime le réseau */
void free_reseau (reseau reseau) {
    for (int i=0 ; i<reseau.len ; i++) {
        free(reseau.base[i]) ;
    }
    free(reseau.base) ;
}

/* Renvoie le nième vecteur de la base du réseau */
double* nieme_vecteur_reseau (reseau reseau, int n) {
    assert(n < reseau.len) ;
    return reseau.base[n] ;
}

/* Renvoie une copie du nième vecteur de la base du réseau */
double* copie_nieme_vecteur_reseau (reseau reseau, int n) {
    assert(n < reseau.len) ;
    double* copie = malloc(sizeof(double)*reseau.len) ;
    for (int i=0 ; i<reseau.len ; i++) {
        copie[i] = reseau.base[n][i] ;
    }
    return copie ;
}