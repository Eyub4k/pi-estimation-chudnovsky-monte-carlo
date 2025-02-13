# Estimation de π avec Monte Carlo et Chudnovsky

Ce projet implémente deux méthodes d'estimation de la constante mathématique **π** en utilisant les algorithmes **Monte Carlo** et **Chudnovsky**. Le code est écrit en C, et la parallélisation est réalisée avec la bibliothèque **OpenMP** pour améliorer les performances lors de l'exécution.

## Méthodes d'estimation de π

### 1. Méthode de Monte Carlo

La méthode de Monte Carlo repose sur l'idée de simuler des points aléatoires dans un carré et de calculer le rapport des points qui se trouvent à l'intérieur d'un cercle inscrit dans ce carré. Plus il y a de points, plus l'estimation de π devient précise.

Formule utilisée pour l'estimation de π :
\[
\pi \approx 4 \times \frac{\text{Nombre de points à l'intérieur du cercle}}{\text{Nombre total de points générés}}
\]

**Implémentation :**
- Des points aléatoires sont générés dans un carré de côté 2 (de -1 à 1 pour x et y).
- On compte combien de points tombent à l'intérieur du cercle de rayon 1 (c'est-à-dire, les points dont \( x^2 + y^2 \leq 1 \)).
- La valeur de π est ensuite estimée en multipliant le rapport des points à l'intérieur du cercle par 4.

### 2. Algorithme de Chudnovsky

L'algorithme de **Chudnovsky** est une série infinie qui permet d'obtenir des estimations très précises de **π**. Il est basé sur des termes impliquant des factorielles et des puissances.

L'algorithme est donné par la formule suivante :
\[
\frac{1}{\pi} = 12 \sum_{k=0}^{\infty} \frac{(-1)^k (6k)! (545140134k + 13591409)}{(3k)! (k!)^3 (640320^{3k + 3/2})}
\]
L'estimation de **π** peut être obtenue en calculant cette série jusqu'à ce que l'élément de la série soit suffisamment petit.

**Parallélisation avec OpenMP :**
- OpenMP est utilisé pour paralléliser la boucle qui calcule les termes de la série Chudnovsky, afin d'améliorer les performances lors du calcul.

## Explication du Code

### Fonction `chudnovsky`

La fonction `chudnovsky` implémente l'algorithme de Chudnovsky pour l'estimation de π. Elle prend en paramètre le nombre de termes de la série à calculer (`terms`) et retourne une estimation de **π**. 

- Pour chaque terme \(k\), les facteurs nécessaires sont calculés :
    - \( (6k)! \)
    - \( 545140134k + 13591409 \)
    - \( (3k)! \)
    - \( (k!)^3 \)
    - Le facteur de puissance de 640320 est également calculé.
- La somme des termes est accumulée et l'inverse de π est calculé à la fin.

### Fonction `main`

La fonction `main` implémente les deux méthodes :
1. **Monte Carlo** : Génère des points aléatoires et calcule une estimation de **π** en fonction du nombre de points générés.
2. **Chudnovsky** : Utilise l'algorithme de Chudnovsky pour générer une estimation précise de **π** après avoir effectué les calculs de la série.

Les points sont générés en parallèle avec **OpenMP**. Le calcul de l'estimation de **π** pour Monte Carlo est parallélisé avec la directive `#pragma omp parallel for`, et les termes de la série de Chudnovsky sont également parallélisés.

## Exécution

### Compilation
Pour compiler le programme avec OpenMP, il est nécessaire de lier les bibliothèques OpenMP. Si tu utilises **gcc**, voici la commande de compilation :

```bash
gcc -o pi_estimation pi_estimation.c -fopenmp -lm
```
Exécution
Pour exécuter le programme, simplement lancer le fichier compilé avec la commande suivante :

```bash
./pi_estimation
```

Il te demandera d'entrer le nombre de points à générer pour la méthode de Monte Carlo, puis il affichera l'estimation de π obtenue via les deux méthodes.

Résultats attendus
Le programme affichera :

Une estimation de π basée sur la méthode de Monte Carlo.
Une estimation de π basée sur l'algorithme de Chudnovsky.
Le temps d'exécution pour le calcul de π avec l'algorithme de Chudnovsky.
Exemple de sortie possible :
```
Combien de points voulez-vous générer ? (N > 10000) : 100000
Voici l'estimation de pi en fonction de votre N : 3.141600
Comme tu peux voir qu'avec la methode de Monte Carlo, on ne peux pas generer beaucoup de decimale,
 donc on vas utiliser l'algorithme de Chudnovsky 
Estimation de pi: 3.141592653589794
Temps d'exécution: 0.013000 secondes
```
### Performance
La méthode de Monte Carlo est rapide pour des estimations approximatives de π, mais elle devient plus lente et moins précise avec un grand nombre de points.
L'algorithme de Chudnovsky est beaucoup plus rapide et plus précis pour obtenir des valeurs de π avec une grande précision, mais il prend plus de temps à exécuter que Monte Carlo pour des petites valeurs de termes.
Prérequis
OpenMP pour la parallélisation
GCC ou tout autre compilateur compatible avec OpenMP
Limitations
La méthode de Monte Carlo dépend fortement du nombre de points générés. Plus il y a de points, plus l'estimation sera précise, mais il faut aussi plus de temps pour générer ces points.
L'algorithme de Chudnovsky nécessite de nombreux termes pour obtenir une grande précision, mais il est bien plus rapide et précis que Monte Carlo pour des séries longues.


Vous pouvez ajouter un contrôle d'exception pour éviter les valeurs négatives dans les calculs de factorielles.
Tester le programme avec un plus grand nombre de termes pour voir l'impact sur la précision de π.
Optimiser le code en utilisant d'autres techniques de parallélisation ou en améliorant la gestion de la mémoire.

### Contribuer
Si tu souhaites contribuer à ce projet, n'hésite pas à ouvrir une pull request ou à signaler des problèmes dans la section Issues de ce dépôt.
