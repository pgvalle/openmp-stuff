#include "../common.h"


double calculate_pi(int steps); // sequential
double p1_calculate_pi(int steps); // parallel
double p2_calculate_pi(int steps); // parallel with reduction

int main() {
    double start, delta, result;

    // ===================================
    printf("non-parallel\n");

    start = omp_get_wtime();
    result = calculate_pi(100000000);
    delta = omp_get_wtime() - start;

    printf("pi: %lf\n", result);
    printf("took %lf seconds\n", delta / 1000);

    // ===================================
    printf("\nparallel v1\n");

    start = omp_get_wtime();
    result = p1_calculate_pi(100000000);
    delta = omp_get_wtime() - start;

    printf("pi: %lf\n", result);
    printf("took %lf seconds\n", delta / 1000);

    // ===================================
    printf("\nparallel v2\n");

    start = omp_get_wtime();
    result = p1_calculate_pi(100000000);
    delta = omp_get_wtime() - start;

    printf("pi: %lf\n", result);
    printf("took %lf seconds\n", delta / 1000); 

    return 0;
}

// sequential
double calculate_pi(int steps) {
    double sum = 0, step = 1.0 / steps;

    for (int i = 0; i < steps; i++) {
        double x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }

    return step * sum;
}

// parallel
double p1_calculate_pi(int steps) {
    double pi = 0, step = 1.0 / steps;
    omp_set_num_threads(4);

    #pragma omp parallel
    {
        double sum = 0;

        #pragma omp for
        for (int i = 0; i < steps; i++) {
            double x = (i + 0.5) * step;
            sum += 4.0 / (1.0 + x * x);
        }

        #pragma omp critical
        pi += sum * step;
    }

    return pi;
}

// parallel with reduction
double p2_calculate_pi(int steps) {
    double sum = 0, step = 1.0 / steps;

    #pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < steps; i++) {
        double x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }

    return step * sum;
}