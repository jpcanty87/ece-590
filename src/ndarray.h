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
    int get_dim();
    size_t *get_shape();
    double *get_data();

private:
    int dim;
    size_t *shape;
    double *data;
}; // class expression

#endif // NDARRAY_H
