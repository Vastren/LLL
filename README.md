# 📐 Algorithme de Réduction de Lattice (LLL)

Ce projet implémente l'algorithme **LLL (Lenstra–Lenstra–Lovász)** en langage **C**. Il permet de réduire une base d’un réseau euclidien tout en conservant la structure du réseau. Cet algorithme est utilisé dans plusieurs domaines comme la cryptographie, la théorie des nombres et la recherche opérationnelle.

---

## 🗂 Structure du Projet

| Fichier         | Description |
|------------------|-------------|
| `LLL.c`          | Contient l'implémentation de l’algorithme LLL ainsi que des fonctions de test (exemples, batteries de tests). |
| `vecteur.c`      | Implémente les opérations vectorielles et les fonctions de gestion de réseau (produit scalaire, norme, addition, soustraction, etc.). |
| `affichage.c`    | Gère l’affichage formaté des vecteurs, matrices et réseaux. |
| `*.h` (manquants ici) | Doivent contenir les définitions de structures (`reseau`) et les prototypes de fonctions. |

---

## 🔧 Compilation

Tu peux compiler ce projet avec `gcc` :

```bash
gcc -o lll_main LLL.c vecteur.c affichage.c -lm
```

> **Note** : L’option `-lm` est utilisée pour inclure la bibliothèque mathématique (`math.h`).

---

## 🚀 Exécution

Le fichier `LLL.c` contient des fonctions principales que utilisables dans un `main()` pour tester l’algorithme :

### Exemple de réduction

```c
print_exemple(base, n);
```

Affiche une base initiale, applique la réduction LLL, et affiche la base réduite ainsi que les matrices intermédiaires (Gram-Schmidt).

### Tests automatiques

```c
batterie_de_test(k);
```

Effectue `k` tests aléatoires en générant des bases de dimension aléatoire et vérifie que les conditions de l’algorithme LLL sont respectées.

---

## 📚 Références

- **Lenstra, Lenstra, Lovász (1982)** — *Factoring polynomials with rational coefficients*
- [Wikipedia — Algorithme LLL](https://fr.wikipedia.org/wiki/Algorithme_LLL)
- [Wikipedia (en) — LLL Algorithm](https://en.wikipedia.org/wiki/Lenstra–Lenstra–Lovász_lattice_basis_reduction_algorithm)

---
