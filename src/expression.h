#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <vector>
#include <string>
#include <map>

class evaluation;

class expression
{
    friend class evaluation;
public:
    expression(
        int expr_id,
        const char *op_name,
        const char *op_type,
        int *inputs,
        int num_inputs);

    void add_op_param_double(
        const char *key,
        double value);

    void add_op_param_ndarray(
        const char *key,
        int dim,
        size_t shape[],
        double data[]);
    int get_expr_id();
    const char *get_op_name();
    const char *get_op_type();
    int *get_inputs();
    int get_num_inputs();

private:
    int expr_id;
    const char *op_name;
    const char *op_type;
    int *inputs;
    int num_inputs;
}; // class expression

#endif // EXPRESSION_H
