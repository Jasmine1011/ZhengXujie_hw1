#include "algebra.h"
#include <stdio.h>
#include <math.h>

Matrix create_matrix(int row, int col)
{
    Matrix m;
    m.rows = row;
    m.cols = col;
    return m;
}

Matrix add_matrix(Matrix a, Matrix b)
{
    if (a.rows != b.rows || a.cols != b.cols){
        printf("Error: Matrix a and b must have the same rows and cols.\n");
        return create_matrix(0, 0);
    }
    Matrix result = create_matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++){
        for (int j = 0; j < a.cols; j++){
            result.data[i][j] = a.data[i][j] + b.data[i][j];
        }
    }
    return result;
}

Matrix sub_matrix(Matrix a, Matrix b)
{
    if (a.rows != b.rows || a.cols != b.cols){
        printf("Error: Matrix a and b must have the same rows and cols.\n");
        return create_matrix(0, 0);
    }
    Matrix result = create_matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++){
        for (int j = 0; j < a.cols; j++){
            result.data[i][j] = a.data[i][j] - b.data[i][j];
        }
    }
    return result;
}

Matrix mul_matrix(Matrix a, Matrix b)
{
    if (a.cols != b.rows){
        printf("Error: The number of cols of matrix a must be equal to the number of rows of matrix b.\n");
        return create_matrix(0, 0);
    }
    Matrix result = create_matrix(a.rows, b.cols);
    for (int i = 0; i < a.rows; i++){
        for (int j = 0; j < b.cols; j++){
            double sum=0;
            for (int k = 0; k < a.cols; k++){
                sum += a.data[i][k] * b.data[k][j];
            }
            result.data[i][j] = sum;
        }
    }
    return result;
}

Matrix scale_matrix(Matrix a, double k)
{
    Matrix result = create_matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++){
        for (int j = 0; j < a.cols; j++){
            result.data[i][j] = a.data[i][j] * k;
        }
    }
    return result;
}

Matrix transpose_matrix(Matrix a)
{
    Matrix result = create_matrix(a.cols, a.rows);
    for (int i = 0; i < a.rows; i++){
        for (int j = 0; j < a.cols; j++){
            result.data[j][i] = a.data[i][j];
        }
    }
    return result;
}

double det_matrix(Matrix a)
{
    if (a.rows != a.cols){
        printf("Error: The matrix must be a square matrix.\n");
        return 0;
    }
    int n = a.rows;
    if (n == 1){
        return a.data[0][0];
    }
    if (n == 2){
        return a.data[0][0] * a.data[1][1] - a.data[0][1] * a.data[1][0];
    }
    double det = 0;
    int sign = 1;
    for (int i = 0; i < n; i++){
        Matrix submatrix = create_matrix(n - 1, n - 1);
        for (int j = 1; j < n; j++){
            for (int k = 0; k < n; k++){
                if (k < i){
                    submatrix.data[j - 1][k] = a.data[j][k];
                } else if (k > i){
                    submatrix.data[j - 1][k - 1] = a.data[j][k];
                }
            }
        }
        det += sign * a.data[0][i] * det_matrix(submatrix);
        sign = -sign;
    }
    return det;
}

Matrix inv_matrix(Matrix a) 
{
    if (a.rows != a.cols) {
        printf("Error: The matrix must be a square matrix.\n");
        return create_matrix(0, 0);
    }
    double det = det_matrix(a);
    if (fabs(det) < 1e-6) {
        printf("Error: The matrix is singular.\n");
        return create_matrix(0, 0);
    }
    int n = a.rows;
    Matrix inv = create_matrix(n, n);
    Matrix adj = create_matrix(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            Matrix minor = create_matrix(n-1, n-1);
            for (int row = 0, mi = 0; row < n; row++) {
                if (row == i) continue;
                for (int col = 0, mj = 0; col < n; col++) {
                    if (col == j) continue;
                    minor.data[mi][mj++] = a.data[row][col];
                }
                mi++;
            }
            adj.data[j][i] = pow(-1, i + j) * det_matrix(minor); // 直接转置填充
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            inv.data[i][j] = adj.data[i][j] / det;
        }
    }
    return inv;
}

int rank_matrix(Matrix a) 
{
    Matrix mat = create_matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            mat.data[i][j] = a.data[i][j];
        }
    }
    int rank = 0;
    int lead = 0;
    for (int r = 0; r < a.rows && lead < a.cols; r++) {
        int i = r;
        while (fabs(mat.data[i][lead]) < 1e-6) {
            i++;
            if (i == a.rows) {
                i = r;
                lead++;
                if (lead == a.cols) break;
            }
        }
        if (lead == a.cols) break;
        for (int j = 0; j < a.cols; j++) {
            double tmp = mat.data[i][j];
            mat.data[i][j] = mat.data[r][j];
            mat.data[r][j] = tmp;
        }
        double pivot = mat.data[r][lead];
        for (i = r + 1; i < a.rows; i++) {
            double factor = mat.data[i][lead] / pivot;
            for (int j = lead; j < a.cols; j++) {
                mat.data[i][j] -= factor * mat.data[r][j];
                if (fabs(mat.data[i][j]) < 1e-6) mat.data[i][j] = 0.0;
            }
        }
        lead++;
        rank++;
    }
    return rank;
}

double trace_matrix(Matrix a) 
{
    if (a.rows != a.cols) {
        printf("Error: The matrix must be a square matrix.\n");
        return 0.0;
    }
    double trace = 0.0;
    for (int i = 0; i < a.rows; i++) {
        trace += a.data[i][i];
    }
    return trace;
}

void print_matrix(Matrix a)
{
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            // 按行打印，每个元素占8个字符的宽度，小数点后保�?2位，左对�?
            printf("%-8.2f", a.data[i][j]);
        }
        printf("\n");
    }
}