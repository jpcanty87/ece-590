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
    std::string op_name_str = op_name;
    std::string op_type_str = op_type;
    expression *exp = new expression(expr_id, op_name_str, op_type_str, inputs, num_inputs);
    expressions.push_back(*exp);
    if (op_name_str.compare("") != 0) {
        associations[op_name_str] = expr_id;
    } else if (op_type_str.compare("") != 0) {
        associations["value"] = expr_id;
    }
}

int program::add_op_param_double(
    const char *key,
    double value)
{  
    std::string k = key;
    auto search = associations.find(k);
    if (search != associations.end()) {
        values[search->second] = value;
    }
    return 0;
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
    evaluation *eval = new evaluation(expressions, associations, values);
    return eval;
}

void program::print_expressions()
{
    for(auto elem : expressions)
    {
        elem.print_expression();
    }
}

void program::print_assocs() 
{
    std::cout << "++++++++++" << '\n';
    for(auto elem : associations)
    {
    std::cout << elem.first << " -> " << elem.second << "\n";
    }
    std::cout << "++++++++++" << '\n';
}

void program::print_values() 
{
    std::cout << "//////////" << '\n';
    for(auto elem : values)
    {
    std::cout << elem.first << " -> " << elem.second << "\n";
    }
    std::cout << "//////////" << '\n';
}