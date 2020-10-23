#ifndef EVALUATION_H
#define EVALUATION_H

#include "expression.h"

class evaluation
{
    public:
        evaluation(const std::vector<expression> &exprs, const std::map<std::string, int> &assocs, std::map<int, double> &vals);

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

        void print_assocs();

        void print_values();

        void print_result();

    private:
        std::map<int, double> values;
        std::map<std::string, int> associations;
        std::vector<expression> expressions;
        double result_;
}; // class evaluation

#endif // EVALUATION_H
