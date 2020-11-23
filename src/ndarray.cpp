#include "ndarray.h"
#include <iostream>

ndarray::ndarray(int dim,
        size_t shape[],
        double data[])
        : total_size(0){
    populate_ndarray(dim, shape, data);
}

void ndarray::populate_ndarray(int di,
        size_t sha[],
        double da[]) {
    size_t total = 1;
    shape = new size_t[di];
    for(int i = 0; i < di; ++i) {
        size_t size = sha[i];
        shape[i] = size;
        total *= size;
    }
    double* a = new double[total];
    data = a;
    dim = di;
    total_size = total;

    for(size_t i = 0; i < total_size; ++i)
        data[i] = da[i];
}

void ndarray::print_ndarray() {
    std::cout << "~~~~~~~~~~~~~~~~~~~~" << '\n';
    int i = 1;
    for (size_t size = 0; size < total_size; ++size) {
        std::cout << i++ << ": " << data[size] << '\n';
    }
    std::cout << "~~~~~~~~~~~~~~~~~~~~" << '\n';
}

void ndarray::partial_print_ndarray(size_t stop) {
    std::cout << "~~~~~~~~~~~~~~~~~~~~" << '\n';
    int i = 1;
    for (size_t size = --total_size; size > total_size - stop; --size) {
        std::cout << size << ": " << data[size] << '\n';
    }
    std::cout << "~~~~~~~~~~~~~~~~~~~~" << '\n';
}


void ndarray::add_data(ndarray * array) {
    double * ext_data = array->get_data();
    size_t ext_total_size = array->get_total_size();
    if (total_size == ext_total_size) {
        for (size_t size = 0; size < total_size; ++size) {
            double old_data = data[size];
            double ext_data_val = ext_data[size];
            data[size] = old_data + ext_data_val;
        }
    } else {
        std::cout << "SOMETHING IS TERRIBLY WRONG" << '\n';
    }
}

void ndarray::sub_data(ndarray * array) {
    double * ext_data = array->get_data();
    size_t ext_total_size = array->get_total_size();
    if (total_size == ext_total_size) {
        for (size_t size = 0; size < total_size; ++size) {
            double old_data = data[size];
            double ext_data_val = ext_data[size];
            data[size] = old_data - ext_data_val;
        }
    } else {
        std::cout << "SOMETHING IS TERRIBLY WRONG" << '\n';
    }
    
}

//x1 * x2
void ndarray::mul_data(ndarray * array) {
    double * ext_data = array->get_data();
    size_t ext_total_size = array->get_total_size();

    size_t left_rows = shape[0];
    size_t left_cols = shape[1];
    size_t right_cols = array->get_shape()[1];
    size_t new_row_count = left_rows;
    size_t new_col_count = right_cols;
    size_t vector_size = left_cols;
    size_t new_size = new_row_count * new_col_count;
    double * new_data = new double[new_size];
    size_t new_global_index = 0;
    for (size_t i = 0; i < new_row_count; i++) {
        for (size_t j = 0; j < new_col_count; j++) {
            double sum = 0;
            size_t vector_index = j;
            size_t row_index = i * vector_size;

            for (size_t k = 0; k < vector_size; k++) {
                double left_data = data[row_index];
                double right_data = ext_data[vector_index];
                sum += left_data * right_data;

                row_index++;
                vector_index += new_col_count;
            }

            new_data[new_global_index] = sum;
            new_global_index++;
        }
    }
    delete data;
    shape[0] = new_row_count;
    shape[1] = new_col_count;
    data = new_data;
    total_size = new_size;
    // print_ndarray();
}

void ndarray::relu() {
    for (size_t i = 0; i < total_size; i++)
        if (data[i] < 0)
            data[i] = 0;
}

void ndarray::flatten() {
    size_t * new_shape = new size_t[2];
    new_shape[0] = shape[0];
    size_t shape_total = 1;
    for (int i = 1; i < dim; i++) {
        shape_total *= shape[i];
    }
    new_shape[1] = shape_total;
    delete shape;
    shape = new_shape;
    dim = 2;
}

int ndarray::get_dim() {
    return dim;
}

size_t *ndarray::get_shape() {
    return shape;
}

double *ndarray::get_data() {
    return data;
}

size_t ndarray::get_total_size() {
    return total_size;
}