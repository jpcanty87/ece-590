#include "ndarray.h"
#include <iostream>

ndarray::ndarray(int dim,
        size_t shape[],
        double data[]){
    ndarray::dim = dim;
    ndarray::shape = shape;
    ndarray::data = data;
}

void ndarray::print_ndarray() {
    std::cout << "~~~~~~~~~~~~~~~~~~~~" << '\n';
    for (int i = 0; i != dim; ++i) {
        size_t size = shape[i];
        for (size_t j = 0; j != size; ++j) {
            std::cout << data[j] << '\n';
        } 
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