#ifndef ALGEBRA_H
#define ALGEBRA_H

#define MAX_MATRIX_SIZE 100

typedef struct Matrix {
    int rows; // 鐭╅樀鐨勮鏁�
    int cols; // 鐭╅樀鐨勫垪鏁�
    double data[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];  // 鐭╅樀鐨勬暟鎹�
} Matrix;

/**
 * @brief 鍒涘缓鐭╅樀
 * @param rows 鐭╅樀鐨勮鏁�
 * @param cols 鐭╅樀鐨勫垪鏁�
 * @return 鍒濆鍖栧悗鐨勭煩闃�
*/
Matrix create_matrix(int rows, int cols);

/**
 * @brief 鐭╅樀鍔犳硶
 * @param a 鐭╅樀a
 * @param b 鐭╅樀b
 * @return a + b, 濡傛灉a鍜宐鐨勮鏁版垨鍒楁暟涓嶇浉绛夛紝浼氱粰鍑洪敊璇彁绀�"Error: Matrix a and b must have the same rows and cols.\n"骞惰繑鍥炰竴涓┖鐭╅樀
*/
Matrix add_matrix(Matrix a, Matrix b);

/**
 * @brief 鐭╅樀鍑忔硶
 * @param a 鐭╅樀a
 * @param b 鐭╅樀b
 * @return a - b锛屽鏋渁鍜宐鐨勮鏁版垨鍒楁暟涓嶇浉绛夛紝浼氱粰鍑洪敊璇彁绀�"Error: Matrix a and b must have the same rows and cols.\n"骞惰繑鍥炰竴涓┖鐭╅樀
*/
Matrix sub_matrix(Matrix a, Matrix b);

/**
 * @brief 鐭╅樀涔樻硶
 * @param a 鐭╅樀a
 * @param b 鐭╅樀b
 * @return a * b锛屽鏋渁鐨勫垪鏁颁笉绛変簬b鐨勮鏁帮紝浼氱粰鍑洪敊璇彁绀�"Error: The number of cols of matrix a must be equal to the number of rows of matrix b.\n"骞惰繑鍥炰竴涓┖鐭╅樀
*/
Matrix mul_matrix(Matrix a, Matrix b);

/**
 * @brief 鐭╅樀鏁颁箻
 * @param a 鐭╅樀a
 * @param k 鏁発
 * @return a * k
*/
Matrix scale_matrix(Matrix a, double k);

/**
 * @brief 鐭╅樀杞疆
 * @param a 鐭╅樀a
 * @return a鐨勮浆缃煩闃�
*/
Matrix transpose_matrix(Matrix a);

/**
 * @brief 鐭╅樀鐨勮鍒楀紡
 * @param a 鐭╅樀a
 * @return a鐨勮鍒楀紡, 濡傛灉a涓嶆槸鏂归樀锛屼細缁欏嚭閿欒鎻愮ず"Error: The matrix must be a square matrix.\n"骞惰繑鍥�0
*/
double det_matrix(Matrix a);

/**
 * @brief 鐭╅樀鐨勯€�
 * @param a 鐭╅樀a
 * @return a鐨勯€嗙煩闃�, 濡傛灉a涓嶆槸鏂归樀鎴朼鐨勮鍒楀紡涓�0锛屼細缁欏嚭閿欒鎻愮ず"Error: The matrix must be a square matrix.\n"骞惰繑鍥炰竴涓┖鐭╅樀锛屽鏋渁鐨勯€嗙煩闃典笉瀛樺湪锛屼細缁欏嚭閿欒鎻愮ず"Error: The matrix is singular.\n"骞惰繑鍥炰竴涓┖鐭╅樀銆�
*/
Matrix inv_matrix(Matrix a);

/**
 * @brief 鐭╅樀鐨勭З
 * @param a 鐭╅樀a
 * @return a鐨勭З
*/
int rank_matrix(Matrix a);

/**
 * @brief 鐭╅樀鐨勮抗
 * @param a 鐭╅樀a
 * @return a鐨勮抗锛屽鏋渁涓嶆槸鏂归樀锛屼細缁欏嚭閿欒鎻愮ず"Error: The matrix must be a square matrix.\n"骞惰繑鍥�0
*/
double trace_matrix(Matrix a);

/**
 * @brief 鎵撳嵃鐭╅樀锛屾牸寮忎负锛氭寜琛屾墦鍗帮紝姣忎釜鍏冪礌鍗�8涓瓧绗︾殑瀹藉害锛屽皬鏁扮偣鍚庝繚鐣�2浣嶏紝宸﹀榻�
 * @param a 鐭╅樀a
*/
void print_matrix(Matrix a);

#endif