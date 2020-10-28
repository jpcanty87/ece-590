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

void ndarray::mul_data(ndarray * array) {
    print_ndarray();
    array->print_ndarray();
    double * ext_data = array->get_data();
    size_t ext_total_size = array->get_total_size();

    size_t rows = shape[0];
    size_t cols = shape[1];
    size_t ext_rows = array->get_shape()[0];
    size_t ext_cols = array->get_shape()[1];
    for (size_t size = 0; size < total_size; ++size) {
        double old_data = data[size];
        double ext_data_val = ext_data[size];
        data[size] = old_data * ext_data_val;
    }
    
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