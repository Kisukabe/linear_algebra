//
//  matrix.cpp
//  my_project
//
//  Created by Hoang Gia Bao on 16/7/25.
//

#include "matrix.h"
#include "macros.h"

#include <iostream>     // Nhập xuất
#include <vector>       // Mảng động 2 chiều
#include <cmath>        // Hàm toán học
#include <stdexcept>    // Xử lý ngoại lệ logic
#include <iomanip>      // In ma trận đẹp
#include <limits>       // So sánh số thực
#include <string>       // Tên biến, thông báo
#include <utility>      // swap()

using namespace std;
// ============== Print and enter function ==============
void cin_vector(Matrix &matrix) {
    cout <<"Nhap ma tran(ma tran duoc lap theo hang): "<< endl;
    FOR_2D(i, j, matrix.row, matrix.col) {
        cin >> matrix.matrix[i][j];
    }
}

void print_matrix(const Matrix &matrix){
    FOR_EACH(i,matrix.row) {
        FOR_EACH(j, matrix.col) {
            cout << matrix.matrix[i][j] << " ";
        }
        cout << endl;
    }
}
// ============== Check function ==============
int check_add_or_subtract_matrix(const Matrix &matrix_A,const Matrix &matrix_B) {
    if (matrix_A.row == matrix_B.row && matrix_A.col == matrix_B.col)
        return 1;
    return 0;
}

int check_square_matrix(const Matrix &matrix){
    if (matrix.row == matrix.col) return 1;
    return 0;
}

int check_multiply_matrix(int col_1,int row_2) {
    if (col_1 == row_2) return 1;
    return 0;
}

int check_identtity_matrix(const Matrix &matrix) {
    if (!check_square_matrix(matrix)) return 0;
    FOR_EACH(i,matrix.row) {
        FOR(j, i+1, matrix.col) {
            if (matrix.matrix[i][j] == 0 || matrix.matrix[j][i] == 0) return 0;
        }
    }
    FOR_EACH(i,matrix.col){
        if (matrix.matrix[i][i] != 1) return 0;
    }
    return 1;
}
// ============== Creative function ==============
Matrix create_zero_matrix(int row, int col) {
    Matrix result;
    result.col = col;
    result.row = row;
    result.matrix = vector<vector<double>>(row,vector<double>(col,0));
    return result;
}
Matrix create_identity_matrix(int size) {
    Matrix result;
    result = create_zero_matrix(size, size);
    FOR_EACH(i, size) {
        result.matrix[i][i]=1;
    }
    return result;
}
// ============== basic calculation function ==============
Matrix compute_matrix(const Matrix &matrix_A,const Matrix &matrix_B,int val) {
    Matrix result = create_zero_matrix(1, 1);
    if (val == 1) {
        // Cong hai ma tran
        result = create_zero_matrix(matrix_A.row,matrix_B.col);
            FOR_2D(i,j,result.row,result.col) {
                result.matrix[i][j] = matrix_A.matrix[i][j] + matrix_B.matrix[i][j];
            }
    }
    else if (val == 2) {
        // Tru hai mai tran
        result = create_zero_matrix(matrix_A.row,matrix_B.col);
            FOR_2D(i,j,result.row,result.col) {
                result.matrix[i][j] = matrix_A.matrix[i][j] - matrix_B.matrix[i][j];
            }
    }
    else if (val == 3) {
        // Nhan hai ma tran
        result = create_zero_matrix(matrix_A.row,matrix_A.col);
            FOR_2D(i, j,result.row, result.col) {
                FOR_EACH(k,matrix_A.col) {
                    result.matrix[i][j] += matrix_A.matrix[i][k]* matrix_B.matrix[k][j];
                }
            }
    }
    return result;
}

Matrix add_matrix(const Matrix &matrix_A,const Matrix &matrix_B){
    if (!check_add_or_subtract_matrix(matrix_A, matrix_B)) {
        throw invalid_argument("Kich thuoc ma tran khong hop le cho phep cong");        return create_zero_matrix(0,0);
    }
    return compute_matrix(matrix_A, matrix_B, 1);
}

Matrix subtract_matrix(const Matrix &matrix_A,const Matrix &matrix_B){
    if (!check_add_or_subtract_matrix(matrix_A, matrix_B))
        throw invalid_argument("Kich thuoc ma tran khong hop le cho phep tru");
    return compute_matrix(matrix_A, matrix_B, 2);
}

Matrix multiply_matrix(const Matrix &matrix_A,const Matrix &matrix_B){
    if (!check_multiply_matrix(matrix_A.col, matrix_B.row))
        throw invalid_argument("Kich thuoc ma tran khong hop le cho phep nhan");
    return compute_matrix(matrix_A, matrix_B, 3);
}
Matrix scalar_matrix(Matrix &matrix, int alpha) {
    Matrix result;
    result = create_zero_matrix(matrix.row, matrix.col);
    FOR_2D(i, j, matrix.row, matrix.col) {
        result.matrix[i][j] = matrix.matrix[i][j]*alpha;
    }
    return result;
}

Matrix power_matrix(const Matrix &matrix,int n) {
    Matrix result_matrix = matrix;
    if (!check_square_matrix(matrix)) {
        cout << "Kich thuoc ma tran khong hop le:" << endl;
        return result_matrix;
    }
    else {
        if (n==0) return create_identity_matrix(matrix.col);
        else if (n==1) return matrix;
        else {
            Matrix result_matrix = matrix;
            for (int i = 0; i < n; i++){
                result_matrix = compute_matrix(result_matrix,matrix,3);
            }
        }
    }
    return result_matrix;
}

//=============== calculate expression ===============
string enter_expression(string& expression){
    cout << "enter expression" << endl;
    cin.ignore();
    getline(cin, expression);
    return expression;
}
string insert_character(string& expression,char character, int index){
    expression += ' ';
    for (unsigned long long i = expression.length() - 1; i > index; i--){
        expression[i] = expression[i - 1];
    }
    expression[index] = character;
    return expression;
}
string adjust_expression(string& expression){
    for (int i = 0; i < expression.length(); i++){
        if (expression[i] == 'x' && expression[i - 1] == ' '){
            insert_character(expression, '1', i - 1);
        }
        if (expression[i] == 'x' && expression[i + 1] == ' '){
            insert_character(expression, '1', i + 1);
        }
        else if (i == expression.length() - 1 && expression[i - 1] == ' '){
            expression += "x0";
        }
    }
    return expression;
}
string reverse_string(string& s){
    string result = "";
    for (unsigned long long i = (s.length() - 1); i >= 0; i--){
        result += s[i];
    }
    return result;
}
Matrix calculate_expression(const Matrix &matrix){
    string expression = enter_expression(expression);
    Matrix result = create_zero_matrix(matrix.row, matrix.col);
    for (int i = 0; i < expression.length(); i++){
        if (expression[i] == 'x'){
            string exponential = "";
            string number = "";
            for (int j = i + 1; j < expression.length();j++){
                if(expression[j] != ' '){
                    exponential += expression[j];
                }
                else break;
            }
            for (int j = i - 1; j >= 0; j--){
                if(expression[j] != ' '){
                    number += expression[j];
                }
                else break;
            }
            number = reverse_string(number);
            Matrix temp_result = power_matrix(matrix, stoi(exponential));
            temp_result = scalar_matrix(temp_result, stoi(number));
            result = add_matrix(result, temp_result);
        }
    }
    return result;
}
//============
// Hoán vị hai chỉ số (thường dùng để đổi vị trí hai hàng)
void swap_values(double &a,double &b) {
    double index;
    index=b;
    b=a;
    a=index;
}
// Nhân một hàng với một hằng số alpha
void scale_row(double alpha,int row, Matrix& matrix) {
    for (int i = 0; i<matrix.col; ++i) {
        matrix.matrix[row][i] = alpha*matrix.matrix[row][i];
    }
}
// Cộng một bội số của hàng này vào hàng khác: row1 += beta * row2
void add_multiple_of_row(int row1, int row2, double beta, Matrix& matrix) {
    for (int i = 0; i<matrix.col; ++i) {
        matrix.matrix[row1][i] -= beta * matrix.matrix[row2][i];
    }
}

void Transposition_row (Matrix& matrix,int row1, int row2) {
    for (int i = 0;i < matrix.col; i++) {
        swap_values(matrix.matrix[row1][i], matrix.matrix[row2][i]);
    }
}

void calculate_rank(Matrix& matrix){
    for (int i = 0; i < matrix.row; i++){
        if ( abs(matrix.matrix[i][i]) < EPS){
               // Tìm hàng bên dưới có phần tử khác 0 ở cột i để swap lên
            for (int k = i + 1; k < matrix.row; k++){
                if ( abs(matrix.matrix[k][i]) > EPS ){
                    Transposition_row(matrix,i,k);
                    break;
                   }
               }
            if ( abs(matrix.matrix[i][i]) < EPS) continue; // Vẫn không tìm được, bỏ qua bước này
           }
        for (int j = i + 1; j < matrix.row; j++){
            add_multiple_of_row(j, i,matrix.matrix[j][i]/matrix.matrix[i][i], matrix);
           }
           cout << "---------------------------------" << endl;
        print_matrix(matrix);
       }
}

// check git
