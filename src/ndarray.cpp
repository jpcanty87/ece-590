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

int ndarray::get_dim() {
    return dim;
}

size_t *ndarray::get_shape() {
    return shape;
}

double *ndarray::get_data() {
    return data;
}