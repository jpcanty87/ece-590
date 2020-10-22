#include "program.h"
#include "evaluation.h"
#include "expression.h"
#include <iostream>
#include <vector>
#include <map>

program::program()
{
}

void program::append_expression(
    int expr_id,
    const char *op_name,
    const char *op_type,
    int inputs[],
    int num_inputs)
{
    expression *exp = new expression(expr_id, op_name, op_type, inputs, num_inputs);
    expressions.push_back(*exp);
    std::string op = op_name;
    if (op.compare("") != 0) {
        associations[op] = expr_id;
    }
}

int program::add_op_param_double(
    const char *key,
    double value)
{  
    std::string k = key;
    std::cout << "Program" << '\n';
    std::cout << k << '\n';
    std::cout << value << '\n';
    return -1;
}

int program::add_op_param_ndarray(
    const char *key,
    int dim,
    size_t shape[],
    double data[])
{
    return -1;
}

evaluation *program::build()
{   
    evaluation *eval = new evaluation(expressions, associations);
    return eval;
}
