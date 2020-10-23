#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <vector>
#include <string>
#include <map>
#include <list>

class evaluation;

class expression
{
    friend class evaluation;
public:
    expression(
        int expr_id,
        std::string op_name,
        std::string op_type,
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
    std::string get_op_name();
    std::string get_op_type();
    std::list<int> get_inputs();
    int get_num_inputs();
    void print_expression();
    void print_inputs();

private:
    int expr_id;
    std::string op_name;
    std::string op_type;
    std::list<int> inputs;
}; // class expression

#endif // EXPRESSION_H
