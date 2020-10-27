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

    size_t size = 0;
    for (int i = 0; i != dim; ++i) {
        int y = 0;
        size_t j = size;
        size += shape[i];
        for (j; j != size; ++j) {
            std::cout << y++ << ": " << data[j] << '\n';
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