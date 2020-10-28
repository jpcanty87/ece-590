#ifndef EVALUATION_H
#define EVALUATION_H

#include "expression.h"
#include "ndarray.h"

class evaluation
{
    public:
        evaluation(
            const std::vector<expression> &exprs, 
            const std::map<std::string, int> &assocs, 
            std::map<int, double> &vals,
            std::map<int, ndarray *> &array_vals);

        void add_kwargs_double(
            const char *key,
            double value);

        void add_kwargs_ndarray(
            const char *key,
            int dim,
            size_t shape[],
            double data[]);

        // return 0 for success
        int execute();

        // return the variable computed by the last expression
        double &get_result();
        int get_dim();
        size_t *get_shape();
        double *get_data();

        void print_assocs();

        void print_values();

        void print_result();

        void print_array_attrs();

        bool is_eval_scalar();

        ndarray *evaluate_ndarrays(std::list<ndarray *> arrays, std::string op_type);

    private:
        std::map<int, double> values;
        std::map<std::string, int> associations;
        std::vector<expression> expressions;
        std::map<int, ndarray *> array_values;
        double result_;
        int dim_;
        size_t *shape_;
        double *data_;
}; // class evaluation

#endif // EVALUATION_H
