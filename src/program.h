#ifndef PROGRAM_H
#define PROGRAM_H

#include "expression.h"
#include <vector>
#include <map>
#include <string>
#include "ndarray.h"

class evaluation;

class program
{
    std::vector<expression> expressions;
    std::map<std::string, int> associations;
    std::map<int, double> values;
    std::map<int, double> values_ndarray;
    std::map<int, ndarray *> array_values;
    public:
        program();

        void append_expression(
            int expr_id,
            const char *op_name,
            const char *op_type,
            int inputs[],
            int num_inputs);

        // return 0 for success
        int add_op_param_double(
            const char *key,
            double value);

        // return 0 for success
        int add_op_param_ndarray(
            const char *key,
            int dim,
            size_t shape[],
            double data[]);

        evaluation *build();

        void print_expressions();
        void print_assocs();
        void print_values();
}; // class program

#endif // PROGRAM_H
