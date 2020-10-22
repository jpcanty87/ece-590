#include <assert.h>
#include "evaluation.h"
#include <iostream>

evaluation::evaluation(const std::vector<expression> &exprs, const std::map<std::string, int> &assocs)
    : result_(0)
{
    expressions = exprs;
    associations = assocs;
}

void evaluation::add_kwargs_double(
    const char *key,
    double value)
{
    std::string k = key;
    
    auto search = associations.find(k);
    if (search != associations.end()) {
        values[search->second] = value;
    }
}

void evaluation::add_kwargs_ndarray(
    const char *key,
    int dim,
    size_t shape[],
    double data[])
{
}

int evaluation::execute()
{
    double total = 0;
    for (auto& exp: expressions) {
        std::cout << "Evaluation Loop" << '\n';
        int expr_id = exp.get_expr_id();
        std::string op_name = exp.get_op_name();
        std::string op_type = exp.get_op_type();
        int *inputs = exp.get_inputs();
        int num_inputs = exp.get_num_inputs();
        if (op_type.compare("Input") == 0) {
            continue;
        }
        int* end = inputs + num_inputs;
        for (int *p = inputs; p != end; ++p) {
            if (op_type.compare("Add") == 0) {
                total += values[*p];
            }
            else if (op_type.compare("Sub") == 0) {
                total += values[*p];
            }
            else if (op_type.compare("Mul") == 0) {
                total *= values[*p];
            }
            else {
                std::cout << "Incorrect Op Type" << '\n';
                std::cout << op_type << '\n';
                return -1;
            }
        }
    }
    result_ = total;
    return 0;
}

double &evaluation::get_result()
{
    return result_;
}
