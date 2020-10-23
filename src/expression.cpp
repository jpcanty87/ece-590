#include "expression.h"
#include <iostream>

expression::expression(
    int expr_id,
    std::string op_name,
    std::string op_type,
    int *inputs,
    int num_inputs)
{
    expression::expr_id = expr_id;
    expression::op_name = op_name;
    expression::op_type = op_type;
    int* end = inputs + num_inputs;
    for (int *p = inputs; p != end; ++p) {
        expression::inputs.push_back(*p);
    }
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

std::string expression::get_op_name() {
    return op_name;
}

std::string expression::get_op_type() {
    return op_type;
}

std::list<int> expression::get_inputs() {
    return inputs;
}
    
int expression::get_num_inputs() {
    return inputs.size();
}

void expression::print_expression() {
    std::cout << "###########" << '\n';
    std::cout << "expr_id: " << expr_id << '\n';
    std::cout << "op_type: " << op_type << '\n';
    std::cout << "op_name: " << op_name << '\n';
    print_inputs();
    std::cout << "###########" << '\n';
}

void expression::print_inputs() {
    
    std::cout << "inputs:" << '\n';
    for(auto elem : inputs)
    {
    std::cout << elem << "\n";
    }
}
