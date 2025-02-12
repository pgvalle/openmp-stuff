#include "../common.h"

#define SPACING 8

#define ELEM_MAX 10

#define L_ROWS 500
#define L_COLS_R_ROWS 500
#define R_COLS 500

int L[L_ROWS][L_COLS_R_ROWS],
    R[L_COLS_R_ROWS][R_COLS],
    A[L_ROWS][R_COLS];

char fmt[1024]; // to show matrices properly aligned

void mul();
void p1_mul();
void init();
void print_LR();
void print_A();

int main() {
    double start, delta;

    srand(time(NULL));
    init();
    //print_LR();

    // =============================================
    start = omp_get_wtime();
    mul();
    delta = omp_get_wtime() - start;

    printf("non-parallel\n");
    //print_A();
    printf("took %lf seconds\n", delta / 1000);

    return 0;
}

void mul() {
    for (int i = 0; i < L_ROWS; i++) {
        for (int j = 0; j < R_COLS; j++) {
            for (int k = 0; k < L_COLS_R_ROWS; k++) { 
                A[i][j] += L[i][k] * R[k][j];
            }
        }
    }
}

void p1_mul() {

}

void init() {
    sprintf(fmt, "%%%dd ", SPACING);

    for (int i = 0; i < L_ROWS; i++) {
        for (int j = 0; j < L_COLS_R_ROWS; j++) {
            L[i][j] = rand() % ELEM_MAX + 1;
        }
    }

    for (int i = 0; i < L_COLS_R_ROWS; i++) {
        for (int j = 0; j < R_COLS; j++) {
            R[i][j] = rand() % ELEM_MAX + 1;
        }
    }

    memset(A, 0, sizeof(A));
}

void print_LR() {
    printf("left mat\n");
    for (int i = 0; i < L_ROWS; i++) {
        for (int j = 0; j < L_COLS_R_ROWS; j++) {
            printf(fmt, L[i][j]);
        }
        printf("\n");
    }

    printf("right mat\n");
    for (int i = 0; i < L_COLS_R_ROWS; i++) {
        for (int j = 0; j < R_COLS; j++) {
            printf(fmt, R[i][j]);
        }
        printf("\n");
    }
}

void print_A() {
    for (int i = 0; i < L_ROWS; i++) {
        for (int j = 0; j < R_COLS; j++) {
            printf(fmt, A[i][j]);
        }
        printf("\n");
    }
}