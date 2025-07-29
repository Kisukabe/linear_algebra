//
//  matrix.hpp
//  my_project
//
//  Created by Hoang Gia Bao on 16/7/25.
//

#ifndef matrix_h
#define matrix_h
#include <vector>
#include <stdio.h>
#include <string>
// khai báo struct
struct Matrix {
    int row,col;
    std::vector<std::vector<double>> matrix;
};
//=====Function Declaration=====
// ============== Print and enter function
void cin_vector(Matrix& matrix);
void print_matrix(const Matrix &matrix);
// ============== Check function
int check_square_matrix(const Matrix &matrix);
int check_multiply_matrix(int col_1,int row_2);
int check_identtity_matrix(const Matrix &matrix);
// ============== Creative function
Matrix create_zero_matrix(int row, int col);
Matrix create_identity_matrix(int size);
// ============== basic calculation function
Matrix compute_matrix(const Matrix &matrix_A,const Matrix& matrix_B,int val);
Matrix add_matrix(const Matrix &matrix_A,const Matrix &matrix_B);
Matrix subtract_matrix(const Matrix &matrix_A,const Matrix &matrix_B);
Matrix multiply_matrix(const Matrix &matrix_A,const Matrix &matrix_B);
Matrix scalar_matrix(Matrix &matrix, double alpha);
Matrix power_matrix(const Matrix &matrix,int n);
//=============== calculate expression
std::string enter_expression(std::string& expression);
std::string insert_character(std::string& expression,char character, int index);
std::string adjust_expression(std::string& expression);
std::string reverse_string(std::string& s);
Matrix calculate_expression(const Matrix &matrix);
//========
//type 1
void swap_values(double &a,double &b);
//type 2
void scale_row(double alpha,int row, Matrix& matrix);
//type 3
void add_multiple_of_row(int row1, int row2, double beta, Matrix& matrix);
void Transposition_row (Matrix& matrix,int row1, int row2);
void calculate_rank(Matrix& matrix);
#endif /* matrix_hpp */
