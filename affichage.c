#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <assert.h>
#include "affichage.h"


/* --------------------- Fonctions d'affichage --------------------- */


/* Affiche la base d'un réseau */
void print_reseau (reseau reseau) {
    printf("[ ") ;
    for (int i=0 ; i<reseau.len ; i++) {
        printf("[ ") ;
        for (int j=0 ; j<reseau.len-1 ; j++) {
            printf("%lf, ", reseau.base[i][j]) ;
        }
        printf("%lf ]\n", reseau.base[i][reseau.len-1]) ;
    }
    printf(" ]\n") ;
}

/* Affiche une matrice de double */
void print_matrice (double** m, int len) {
    printf("[ ") ;
    for (int i=0 ; i<len ; i++) {
        printf("[ ") ;
        for (int j=0 ; j<len-1 ; j++) {
            printf("%lf, ", m[i][j]) ;
        }
        printf("%lf ]\n", m[i][len-1]) ;
    }
    printf(" ]\n") ;
}

/* Affiche un tableau de double */
void print_tab (double* m, int len) {
    printf("[ ") ;
    for (int i=0 ; i<len-1 ; i++) {
        printf("%lf, ", m[i]) ;
    }
    printf("%lf ]\n", m[len-1]) ;
}