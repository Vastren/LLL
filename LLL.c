#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <assert.h>
#include "affichage.h"
#include "LLL.h"


/* --------------------- Algorithme LLL --------------------- */


/* Production de la matrice des vecteurs issus du procédé de Gram-Schmidt (unicité avec u[i][i] = 1) */
void gram_schmidt (reseau reseau, double** u, double* a) {
    int n = reseau.len ;
    double** b = malloc(sizeof(double*)*n) ;
    double* projection = malloc(sizeof(double)*n) ;

    for (int i=0 ; i<n ; i++) {
        b[i] = malloc(sizeof(double)*n) ;
        u[i] = calloc(n, sizeof(double)) ;
        for (int j=0 ; j<n ; j++) {
            b[i][j] = reseau.base[i][j] ;
        }

        /* Calcul de b*_i et des u_i,j */
        for (int j=0 ; j<i ; j++) {
            u[i][j] = pdt_scalaire(reseau.base[i], b[j], n)/a[j] ;
            multiplication_vecteur(b[j], u[i][j], projection, n) ;
            soustraction_vecteur(b[i], projection, b[i], n) ;
        }

        /* Calcul de || b*_i || */
        a[i] = pdt_scalaire(b[i], b[i], n) ;
    }

    for (int i=0 ; i<n ; i++) {
        free(b[i]) ;
    }
    free(b) ;
    free(projection) ;
}

/* Réduit le vecteur b_k par rapport au vecteur b_l */
void reduction (reseau reseau, double** u, int k, int l) {
    int n = reseau.len ;
    double* vecteur = malloc(sizeof(double)*n) ;

    /* Réduction du vecteur b_k en b_k = b_k − [u_k,l]*b_l */
    multiplication_vecteur(reseau.base[l], round(u[k][l]), vecteur, n) ;
    soustraction_vecteur(reseau.base[k], vecteur, reseau.base[k], n) ;

    /* Modification des u_k,j */
    for (int j=0 ; j<l ; j++) {
        u[k][j] -= round(u[k][l])*u[l][j] ;
    }
    u[k][l] -= round(u[k][l]) ;

    free(vecteur) ;
}

/* Echange deux vecteurs du réseau et met à jour les coefficients et normes associés */
void echanger (reseau reseau, double** u, double* a,  int k) {
    int n = reseau.len ;
    double temp_u = u[k][k-1] ;
    double temp_a = a[k] + temp_u*temp_u*a[k-1] ;

    /* Calcul des nouvelles normes au carré et de u_k,(k-1)*/
    u[k][k-1] = temp_u * a[k-1] / temp_a ;
    a[k] = a[k-1]*a[k] / temp_a ;
    a[k-1] = temp_a ;

    for (int j=0 ; j<n ; j++) {
        double temp ;

        /* Echange des b_k */
        temp = reseau.base[k-1][j] ;
        reseau.base[k-1][j] = reseau.base[k][j] ;
        reseau.base[k][j] = temp ;

        /* Echange des u_k,j et u_(k-1),j pour j dans [0, k-2] */
        if (j <= k-2) {
            temp = u[k-1][j] ;
            u[k-1][j] = u[k][j] ;
            u[k][j] = temp ;
        }

        /* Modification des u_j,(k-1) et u_j,k pour j dans [k+1, n-1] */
        if (j >= k+1) {
            temp = u[j][k-1] ;
            u[j][k-1] = u[k][k-1]*u[j][k-1] + (1 - u[k][k-1]*temp_u)*u[j][k] ;
            u[j][k] = temp - temp_u*u[j][k] ;
        }
    }
}

/* Exécute l'algorithme LLL sur un réseau de vecteurs */
void LLL (reseau reseau) {
    assert(reseau.len > 1) ;
    int n = reseau.len ;
    double** u = malloc(sizeof(double*)*n) ;
    double* a = malloc(sizeof(double)*n) ;

    gram_schmidt(reseau, u, a) ;

    int k = 1 ;
    while (k < n) {
        reduction(reseau, u, k, k-1) ;
        if ((0.75 - u[k][k-1]*u[k][k-1])*a[k-1] > a[k]) {
            echanger(reseau, u, a, k) ;
            if (k > 1) {
                k -- ;
            }
        } else {
            for (int l=k-2 ; l>-1 ; l--) {
                /*reduction(reseau, u, k, l) ;*/
                if (u[k][l] > 0.5 || u[k][l] < -0.5) {
                    reduction(reseau, u, k, l) ;
                }
            }
            k ++ ;
        }
    }

    for (int i=0 ; i<n ; i++) {
        free(u[i]) ;
    }
    free(u) ;
    free(a) ;
}


/* --------------------- Fonctions d'exemples et de tests --------------------- */


/* Affiche un exemple de réduction LLL à partir d'une base donnée */
void print_exemple (double** base, int n) {
    reseau r = {.base = base, .len = n} ;

    printf("Exemple %d : base de dimension %d :\n\n", n-1, n) ;
    printf("Base initiale :\n") ;
    print_reseau(r) ;
    printf("\n") ;
    LLL(r) ;
    printf("Base réduite (LLL) :\n") ;
    print_reseau(r) ;
    printf("\n") ;

    double** u = malloc(sizeof(double*)*n) ;
    double* a = malloc(sizeof(double)*n) ;
    gram_schmidt(r, u, a) ;

    print_matrice(u, n) ;
    printf("\n") ;

    // Condition 1
    bool c1 = true ;
    for (int i=0 ; i<n ; i++) {
        for (int j=0 ; j<i ; j++) {
            if (!(u[i][j] <= 0.5 && u[i][j] >= -0.5)) {
                printf("La condition 1 n'est pas vérifiée pour u_%d,%d = %lf \n", i, j, u[i][j]) ;
                c1 = false ;
            }
        }
    }
    if (c1) {
        printf("La condition 1 est vérifiée\n") ;
    }


    // Condition 2
    bool c2 = true ;
    for (int i=0 ; i<n ; i++) {
        if (i >= 1) {
            if (!(a[i] >= (3/4-u[i][i-1]*u[i][i-1])*a[i-1])) {
                printf("La condition 2 n'est pas vérifiée pour i = %d : %lf < %lf\n", i, a[i], (3/4-u[i][i-1]*u[i][i-1])*a[i-1]) ;
                c2 = false ;
            }
        }
    }
    if (c2) {
        printf("La condition 2 est vérifiée\n") ;
    }

    printf("\n") ;
}

/* Lance une batterie de tests sur l'algorithme LLL */
void batterie_de_test (int k) {
    bool check = true ;
    for (int m=0 ; m<k ; m++) {
        int n = rand() % 1000 + 2 ;
        double** base = malloc(sizeof(double*)*n) ;
        double** base_copie = malloc(sizeof(double*)*n) ;
        for (int i=0 ; i<n ; i++) {
            base[i] = malloc(sizeof(double)*n) ;
            base_copie[i] = malloc(sizeof(double)*n) ;
            for (int j=0 ; j<n ; j++) {
                base[i][j] = ((float)(rand())/(float)(RAND_MAX)) * 100000 ;
                base_copie[i][j] = base[i][j] ;
            }
        }

        reseau r = {.base = base, .len = n} ;
        LLL(r) ;

        double** u = malloc(sizeof(double*)*n) ;
        double* a = malloc(sizeof(double)*n) ;
        gram_schmidt(r, u, a) ;

        bool b = true ;
        
        // Condition 1
        for (int i=0 ; i<n ; i++) {
            for (int j=0 ; j<i ; j++) {
                if (!(u[i][j] <= 0.5 && u[i][j] >= -0.5)) {
                    printf("La condition 1 n'est pas vérifiée pour u_%d,%d = %lf \n", i, j, u[i][j]) ;
                    b = false ;
                }
            }
        }


        // Condition 2
        for (int i=0 ; i<n ; i++) {
            if (i >= 1) {
                if (!(a[i] >= (3/4-u[i][i-1]*u[i][i-1])*a[i-1])) {
                    printf("La condition 2 n'est pas vérifiée pour i = %d : %lf < %lf\n", i, a[i], (3/4-u[i][i-1]*u[i][i-1])*a[i-1]) ;
                    b = false ;
                }
            }
        }

        if (!b) {
            check = false ;
            printf("Base initiale : \n") ;
            print_matrice(base_copie, n) ;
            printf("\n") ;
            printf("Base réduite (LLL) : \n") ;
            print_reseau(r) ;
            printf("\n") ;
            printf("Matrice U : \n") ;
            print_matrice(u, n) ;
            printf("\n") ;
        }

        for (int i=0 ; i<n ; i++) {
            free(base[i]) ;
            free(base_copie[i]) ;
            free(u[i]) ;
        }
        free(base) ;
        free(base_copie) ;
        free(u) ;
        free(a) ;
    }

    if (check) {
        printf("Les %d test ont été passé avec succès !!!\n", k) ;
    }
}