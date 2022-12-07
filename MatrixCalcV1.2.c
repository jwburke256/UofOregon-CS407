#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 4
typedef long array_t[N][N];
void transpose(array_t a) {
    for (long i = 0; i < N; ++i) {
        for (long j = 0; j < i; ++j) {
            long t1 = a[i][j];
            long t2 = a[j][i];
            a[i][j] = t2;
            a[j][i] = t1;
        }
    }
}

void transposeOpt(array_t a) {
    for (long i = 0; i < N; ++i) {
        long int *rp = &a[i][0];
        long int *cp = &a[0][i];
        for (long j = 0; j < i; ++j) {
            long t1 = *cp;
            long t2 = *rp;
            *cp = t2;
            *rp = t1;
            rp += 1;
            cp += N;
        }

    }
}

void printArray(array_t a) {
    for (long i = 0; i < N; ++i) {
        printf("[");
        for (long j = 0; j < N-1; ++j) {
            long t1 = a[i][j];
            printf("%d,", t1);
        }
        printf("%d", a[i][N-1]);
    printf("]\n");
    }
}
/////////////////////////////////////////////////////////////////////
//#define N 4
// typedef long matrix[N][N];

int *mallocMatrix(int length) {

    int row = length, col = length, i, j, count;
    int (*arr)[row][col] = calloc(row, sizeof *arr);
    return **arr;
}



// struct matrix{
//     int size;
//     long *dataPtr;
// };

// struct matrix* mallocMatrix(int length) {
// 	// allocates memory for struct
// 	struct matrix *matrixPtr = (struct matrix *)malloc(sizeof(struct matrix));
// 	// allocates memory for array and sets the ptr as struct member
// 	matrixPtr->dataPtr= (long int *)malloc((length * length) * sizeof(long));
// 	matrixPtr->size= length;
// 	return matrixPtr;
// }

void printMatrix(int *matr1, int size_t) {
    printf("test\n");
    for (long i = 0; i < size_t; ++i) {
        printf("[");
        for (long j = 0; j < size_t-1; ++j) {
            long t1 = (&matr1)[i][j];
            printf("%d,", t1);
        }
        printf("%d", (&matr1)[i][size_t-1]);
        printf("]\n");
    }
}


// prompt user for matrix operation selection
int userSelect() {
    int n;
    printf("Please select from the following Matrix Calculator Options:\n");
    printf("1. Matrix Addition\n");
    printf("2. Matrix Subtraction\n");
    scanf("%d", &n);
    return n;
}

// prompt user for size of matrix
int matrixSize(int count) {
    bool bool1 = true; // used to escape loop once N is correct
    int n;
    char c;
    int m;
    while (bool1) {
        printf("(Note, Matrix size must be NxN square)\n");
        printf("Please provide the size of Matrix %d: ", count);
        scanf("%d%c%d", &n, &c, &m);
        printf("\n");
        if (n != m) {
            printf("Given values for N are incorrect, please try again!\n");
        } else {
            bool1 = false;
        }
    }
    return n;
}

// prompt user to input numbers for matrix row by row
void matrixInput(int *matrix, int size, int count) {
    // loop to prompt row by row
    int length = size+1; 
    //str scanfStr = "";
    printf("Please provide each given row for matrix %d in the following format:\n", count);
    printf("int1,int2,..., int%d\n", length);
    for (long i=0; i < length; i++) {
        char str[(length*2)-1];
        printf("Input row %d:\n", (i+1));
        scanf("%s", str);
        bool bool1 = true; // bool to keep track if given row was correct
        // input given row into matrix
        long k = 0;
        for (long j = 0; j < length; j++) {
            // check for commas in given str input
            if (str[j] != ',') {
                (&matrix)[i][k] = (long) str[j];
                k +=1;
            }
        }
        printf("\n");
    }
    return;
}

// simple matrix addition
void matrixAddition(int * matr1, int * matr2, int size) {
    // operation will overwrite first given matrix
    for (long i=0; i < size; i++) {
        for (long j = 0; j < size; j++) {
            (&matr1)[i][j] = (&matr1)[i][j] + (&matr2)[i][j];
        }
    }
    return;
}

void matrixSubtraction(int * matr1, int * matr2, int size) {
    // operation will overwrite first given matrix
    for (long i=0; i < size; i++) {
        for (long j = 0; j < size; j++) {
            (&matr1)[i][j] = (&matr1)[i][j] - (&matr2)[i][j];
        }
    }
    return;
}


void matrixOps(int n) {
    switch (n) {
        case 1: ;
        {
            int size1, size2;
            size1 = matrixSize(1);
            size2 = matrixSize(2);
            // #undef N
            // #define N size1
            int *matrixPtr1 = mallocMatrix(size1);
            int *matrixPtr2 = mallocMatrix(size2);
            // long matr1[size1][size1];
            // long matr2[size2][size2];
            matrixInput(matrixPtr1, size1, 1);
            printMatrix(matrixPtr1, size1);
            // matrixInput(matr2, size2, 2);
            // matrixAddition(matr1, matr2, size1);
            // printMatrix(matr1);
            break;
        }
        case 2: ;
        {
            int size1, size2;
            size1 = matrixSize(1);
            size2 = matrixSize(2);
            #undef N
            #define N size1
            int *matrixPtr1 = mallocMatrix(size1);
            int *matrixPtr2 = mallocMatrix(size2);
            // long matr1[size1][size1];
            // long matr2[size2][size2];
            matrixInput(matrixPtr1, size1, 1);
            matrixInput(matrixPtr2, size2, 2);
            matrixSubtraction(matrixPtr1, matrixPtr2, size1);
            printMatrix(matrixPtr1, size1);
            break;
        }
        default:
            break;
    }
}



// simple matrix subtraction

// simple matrix multiplication/division

// transpose of matrix

// inverse of the matrix

// determinant

// rank of the matrix

// Col of A and Nul of A


int main() {

    int n;
    n = userSelect();
    //printf("%d", n);
    matrixOps(n);

//     array_t a = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15,
// 16}};
//     printArray(a);
//     printf("\n");
//     transpose(a);
//     printArray(a);
//     printf("\n");
//     array_t b = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15,
// 16}};
//     transposeOpt(b);
//     printArray(b);
}