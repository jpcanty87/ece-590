#include "expression.h"
#include <iostream>

expression::expression(
    int expr_id,
    const char *op_name,
    const char *op_type,
    int *inputs,
    int num_inputs)
{
    expression::expr_id = expr_id;
    expression::op_name = op_name;
    expression::op_type = op_type;
    expression::inputs = inputs;
    expression::num_inputs = num_inputs;
}

void expression::add_op_param_double(
    const char *key,
    double value)
{ 
    std::string k = key;
    std::cout << "Expression" << '\n';
    std::cout << k << '\n';
    std::cout << value << '\n';
}

void expression::add_op_param_ndarray(
    const char *key,
    int dim,
    size_t shape[],
    double data[])
{
}

int expression::get_expr_id () {
    return expr_id;
}

const char *expression::get_op_name() {
    return op_name;
}

const char *expression::get_op_type() {
    return op_type;
}

int *expression::get_inputs() {
    return inputs;
}
    
int expression::get_num_inputs() {
    return num_inputs;
}
