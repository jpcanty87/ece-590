#ifndef NDARRAY_H
#define NDARRAY_H

#include <vector>
#include <string>
#include <map>
#include <list>

class ndarray
{
public:
    ndarray(
        int dim,
        size_t shape[],
        double data[]);
    void print_ndarray();
    void partial_print_ndarray(size_t stop);
    int get_dim();
    size_t *get_shape();
    double *get_data();
    size_t get_total_size();
    void populate_ndarray(int dim,
        size_t shape[],
        double data[]);
    void add_data(ndarray * array);
    void sub_data(ndarray * array);
    void mul_data(ndarray * array);
    void relu();
    void flatten();

private:
    int dim;
    size_t *shape;
    double *data;
    size_t total_size;
}; // class expression

#endif // NDARRAY_H
