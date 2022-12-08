#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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

// int *mallocMatrix(int length) {

//     int row = length, col = length, i, j, count;
//     int (*arr)[row][col] = calloc(row, sizeof *arr);
//     return **arr;
// }

// struct matrix{
//     int size;
//     long *dataPtr;
// };

// mallocMatrix v1
// struct matrix* mallocMatrix(int length) {
// 	// allocates memory for struct
// 	struct matrix *matrixPtr = (struct matrix *)malloc(sizeof(struct matrix));
// 	// allocates memory for array and sets the ptr as struct member
// 	matrixPtr->dataPtr= (long int *)malloc((length * length) * sizeof(long));
// 	matrixPtr->size= length;
// 	return matrixPtr;
// }

// mallocMatrix v2
// unable to get mallocMatrix working. Think it has to do
// with how accessing columns using pointer is done
// int *mallocMatrix(int length) {

//     int i;
//     int **matr = malloc(length * sizeof(int *));
//     for(i = 0; i < length; i++) {
//         matr[i] = malloc(length * sizeof(int));
//     }
//     return *matr;
// }

// Global variables:
int check = 0; // tracks current case

void printMatrix(int row, int col, int matrix[row][col]) {
    for (long i = 0; i < row; ++i) {
        printf("[");
        long j;
        for (j = 0; j < col-1; ++j) {
            long t1 = matrix[i][j];
            printf("%d,", t1);
        }
        printf("%d", matrix[i][col-1]);
        printf("]\n");
    }
}


// prompt user for matrix operation selection
int userSelect() {
    int n;
    printf("Please select from the following Matrix Calculator Options:\n");
    printf("1. Matrix Addition\n");
    printf("2. Matrix Subtraction\n");
    printf("3. Matrix Multiplication\n");
    printf("4. Transpose Matrix\n");
    printf("5. Determinant of Matrix\n");
    scanf("%d", &n);
    return n;
}

// prompt user for size of matrix
int matrixSize(int *row, int *col, int count) {
    bool bool1 = true; // used to escape loop once N is correct
    int n;
    char c;
    int m;
    while (bool1) {
        if (check < 3) {
            printf("(Note, Matrix size must be NxN square)\n");
        } else if (check >= 5) {
            printf("(Note, Matrix must either be 2x2 or 3x3 square)\n");
        } else {
            printf("(Input Matrix size in the format: NxM)\n");
        }
        printf("Please provide the size of Matrix %d: ", count);
        scanf("%d%c%d", &n, &c, &m);
        printf("\n");
        if (check < 3) {
            if (n != m) {
                printf("Given values for N are incorrect, please try again!\n");
            } else {
                bool1 = false;
            }
        } else if (check >= 5) {
            if (n != m || n<=1 || n>=4 ) {
                printf("Given values for N are incorrect, please try again!\n");
            } else {
                bool1 = false;
            }
        } else {
            bool1 = false;
        }
    }
    *row = n;
    *col = m;
    // if (check < 3) {
    //     return n;
    // } else {
    //     return n, m;
    // }
}

// Test function to fill matrix
void matrixFill(int length, int matrix[length][length]) {
    for (int i=0; i < length; i++) {
        for (int j=0; j < length; j++) {
            matrix[i][j] = j;
            //printf("%d", matrix[i][j]);
        }
        //printf("\n");
    }
    //printf("Fill Complete\n");
}

// prompt user to input numbers for matrix row by row
void matrixInput(int row, int col, int count, int matrix[row][col]) {
    printf("Please provide each given row for matrix %d in the following format:\n", count);
    printf("int1,int2,..., int%d\n", col);
    for (int i=0; i < row; i++) {
        char str[(col*3)];
        printf("Input row %d:\n", (i+1));
        scanf("%s", str);
        // input given row into matrix
        int k = 0;
        int strLen = strlen(str);
        bool negSign = false; 
        for (int j = 0; j < strLen; j++) {
            // check for negative sign from str
            if (str[j] == '-') {
                negSign = true;
                continue;
            }
            // check for non int chars in given str input
            int num = atoi(&str[j]);
            if (negSign) {
                if (num != 0) {
                    matrix[i][k] = -(num);
                    negSign = false;
                    k +=1;
                }
                else if (str[j] == '0') {
                    matrix[i][k] = 0;
                    k +=1;
                    negSign = false;
                }
                else {}
            } else {
                if (num != 0) {
                    matrix[i][k] = num;
                    k +=1;
                }
                else if (str[j] == '0') {
                    matrix[i][k] = 0;
                    k +=1;
                }
                else {}
            }
        }
    }
    printf("\n");
    return;
}

// simple matrix addition
void matrixAddition(int length1, int length2, int matrix1[length1][length1],
                     int matrix2[length2][length2]) {
    // operation will overwrite first given matrix
    for (long i=0; i < length1; i++) {
        for (long j = 0; j < length1; j++) {
            matrix1[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
    return;
}

// simple matrix subtraction
void matrixSubtraction(int length1, int length2, int matrix1[length1][length1],
                     int matrix2[length2][length2]) {
    // operation will overwrite first given matrix
    for (long i=0; i < length1; i++) {
        for (long j = 0; j < length1; j++) {
            matrix1[i][j] = matrix1[i][j] - matrix2[i][j];
        }
    }
    return;
}

// matrix multiplication
void matrixMultiplication(int row1, int col1, int row2, int col2, int matrix1[row1][col1],
                     int matrix2[row2][col2], int matrix3[row1][col2]) {
    //first loop multiplies matrix1 by column 1
    //outside loop adds column multiplication operation
    for (int c=0; c < col2; c++) {
        for (int i=0; i < row1; i++) {
            int result = 0;
            for (int j=0; j < row2; j++) {
                // matrix1 traverses down the row i
                // matrix 2 traverses down column c
                result += matrix1[i][j] * matrix2[j][c];
            }
            matrix3[i][c] = result;
        }        
    }
}

// transpose of matrix
void matrixTranspose(int row1, int col1, int matrix1[row1][col1],
                     int matrix1T[col1][row1]) {
    for (int i=0; i < row1; i++) {
        for (int j=0; j < col1; j++) {
            matrix1T[j][i] = matrix1[i][j];
        }
    }
}

// determinant of 2x2 Matrix
int deter2x2(int pos1, int pos2, int row1, int col1,
             int matrix1[row1][col1]) {
    int result;
    result = (matrix1[pos1][pos2] * matrix1[(pos1)+1][(pos1)+1]) 
            - (matrix1[pos1][(pos1)+1] * matrix1[(pos1)+1][pos1]);
    return result;
}

void matrixOps(int n) {
    switch (n) {
        case 1: ;
        {
            check = 1;
            int size1, size2;
            matrixSize(&size1, &size1, 1);
            matrixSize(&size2, &size2, 2);
            int matrix1[size1][size1];
            int matrix2[size2][size2];
            matrixInput(size1, size1, 1, matrix1);
            matrixInput(size2, size2, 2, matrix2);
            matrixAddition(size1, size2, matrix1, matrix2);
            printMatrix(size1, size1, matrix1);
            break;
        }
        case 2: ;
        {
            check = 2;
            int size1, size2;
            matrixSize(&size1, &size1, 1);
            matrixSize(&size2, &size2, 2);
            int matrix1[size1][size1];
            int matrix2[size2][size2];
            matrixInput(size1, size1, 1, matrix1);
            matrixInput(size2, size2, 2, matrix2);
            matrixSubtraction(size1, size2, matrix1, matrix2);
            printMatrix(size1, size1, matrix1);
            break;
        }
        case 3: ;
        {
            check = 3;
            int row1, col1, row2, col2;
            label1:
            matrixSize(&row1, &col1, 1);
            matrixSize(&row2, &col2, 2);
            //check given row and column sizes to see if mult is possible
            if (col1 != row2) {
                printf("Column size of first matrix must match Row size of second.\n");
                printf("Please input Matrices again.\n");
                printf("\n");
                goto label1;
            }
            int matrix1[row1][col1];
            int matrix2[row2][col2];
            int matrix3[row1][col2];
            matrixInput(row1, col1, 1, matrix1);
            printf("Matrix 1:\n");
            printMatrix(row1, col1, matrix1);
            printf("\n");
            matrixInput(row2, col2, 2, matrix2);
            printf("Matrix 2:\n");
            printMatrix(row2, col2, matrix2);
            printf("\n");
            matrixMultiplication(row1, col1, row2, col2, matrix1, matrix2, matrix3);
            printMatrix(row1, col2, matrix3);
            break;
        }
        case 4: ;
        {
            check = 4;
            int row1, col1;
            matrixSize(&row1, &col1, 1);
            int matrix1[row1][col1];
            int matrix1T[col1][row1];
            matrixInput(row1, col1, 1, matrix1);
            printf("Matrix 1:\n");
            printMatrix(row1, col1, matrix1);
            printf("\n");
            matrixTranspose(row1, col1, matrix1, matrix1T);
            printf("Matrix 1 Transposed:\n");
            printMatrix(col1, row1, matrix1T);
            printf("\n");
        }
        case 5: ;
        {
            check = 5;
            int size1;
            matrixSize(&size1, &size1, 1);
            int matrix1[size1][size1];
            matrixInput(size1, size1, 1, matrix1);
            printf("Matrix 1:\n");
            printMatrix(size1, size1, matrix1);
            printf("\n");
            // determine if Matrix is 2x2 or 3x3
            if (size1 == 2) {
                int deter = deter2x2(0, 0, size1, size1, matrix1);
                printf("Determinant of given 2x2 Matrix is: %d\n", deter);
            } else if (size1 == 3) {

            } else {}
        }
        default:
            break;
    }
}




// limit determinant and inverse to only 2x2 and 3x3 matrices

// inverse of the matrix

// determinant

// rank of the matrix

// Col of A and Nul of A


int main() {

    int n;
    n = userSelect();
    matrixOps(n);

}