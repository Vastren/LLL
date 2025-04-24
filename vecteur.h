#ifndef OPERATIONS_VECTEURs_H
#define OPERATIONS_VECTEURs_H

/* --------------------- Fonctions vectorielles --------------------- */

/* Structure représentant un réseau de vecteurs */
typedef struct {
    double** base ;    int len ;
} reseau ;

double pdt_scalaire(double* v1, double* v2, int n) ;
double norme(double* v, int n) ;
void multiplication_vecteur(double* v, double scalaire, double* resultat, int n) ;
void somme_vecteur(double* v1, double* v2, double* resultat, int n) ;
void soustraction_vecteur(double* v1, double* v2, double* resultat, int n) ;

/* --------------------- Fonctions du réseau --------------------- */

reseau initialiser_reseau (double** base, int len) ;
int length (reseau reseau) ;
void free_reseau (reseau reseau) ;
double* nieme_vecteur_reseau (reseau reseau, int n) ;
double* copie_nieme_vecteur_reseau (reseau reseau, int n) ;


#endif