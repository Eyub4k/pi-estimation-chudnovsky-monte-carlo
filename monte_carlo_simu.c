#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

double chudnovsky(int terms) {
    double sum = 0.0;
    double factor1, factor2, factor3, factor4, term;
    double pi_inv;
    
    for (int k = 0; k < terms; k++) {
        factor1 = 1.0;  
        for (int i = 1; i <= 6 * k; i++) {
            factor1 *= i;
        }

        factor2 = 545140134 * k + 13591409;
        factor3 = 1.0;
        for (int i = 1; i <= 3 * k; i++) {
            factor3 *= i;
        }

        factor4 = 1.0;
        for (int i = 1; i <= k; i++) {
            factor4 *= i;
        }

        term = factor1 * factor2 / (factor3 * factor4 * pow(640320, 3 * k + 3.0 / 2));
        
        if (term < 1e-20) {
            break;  
        }

        sum += (k % 2 == 0 ? 1 : -1) * term;
    }

    pi_inv = 12 * sum;
    return 1.0 / pi_inv; 
}


int main() {
    int N; 
    int in_circle = 0; 
    double pi_estimate; 

    do {
        printf("Combien de points voulez-vous générer ? (N > 10000) : ");
        scanf("%d", &N);
    } while (N < 10000);

    omp_set_num_threads(8); 
    #pragma omp parallel for reduction(+:in_circle)

    for (int i = 0; i < N; i++) {
        double x = (rand() / (double)RAND_MAX) * 2 - 1; 
        double y = (rand() / (double)RAND_MAX) * 2 - 1; 
        if (x * x + y * y <= 1) { 
            in_circle++;
        }
    }

   
    pi_estimate = 4 * ((double)in_circle / N);
    
    
    printf("Voici l'estimation de pi en fonction de votre N : %f\n", pi_estimate);
    printf("Comme tu peux voir qu'avec la methode de Monte Carlo, on ne peux pas generer beaucoup de decimale,\n donc on vas utiliser l'algorithme de Chudnovsky \n");

    int terms = 100; // Nombre d'itérations
    double pi;
    
    // Parallélisation avec OpenMP
    omp_set_num_threads(8);  // Utilisation de 4 threads
    
    double start = omp_get_wtime();
    pi = chudnovsky(terms);
    double end = omp_get_wtime();
    
    printf("Estimation de pi: %.15f\n", pi);
    printf("Temps d'exécution: %f secondes\n", end - start);

    return 0;
}
