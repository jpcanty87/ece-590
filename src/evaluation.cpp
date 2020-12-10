#include <assert.h>
#include "evaluation.h"
#include <iostream>
#include "ndarray.h"

evaluation::evaluation(
    const std::vector<expression> &exprs,
    const std::map<std::string, int> &assocs,
    std::map<int, double> &vals,
    std::map<int, ndarray *> &array_vals)
    : result_(0), dim_(0), shape_(nullptr), data_(nullptr)
{
    expressions = exprs;
    associations = assocs;
    values = vals;
    array_values = array_vals;
}

void evaluation::add_kwargs_double(
    const char *key,
    double value)
{
    std::string k = key;

    auto search = associations.find(k);
    if (search != associations.end())
    {
        values[search->second] = value;
    }
}

void evaluation::add_kwargs_ndarray(
    const char *key,
    int dim,
    size_t shape[],
    double data[])
{
    std::string k = key;

    auto search = associations.find(k);
    if (search != associations.end())
    {
        ndarray *array = new ndarray(dim, shape, data);
        array_values[search->second] = array;
    }
}

int evaluation::execute()
{
    double total = 0;
    for (auto &exp : expressions)
    {
        total = 0;
        int expr_id = exp.get_expr_id();
        std::string op_name = exp.get_op_name();
        std::string op_type = exp.get_op_type();
        std::list<int> inputs = exp.get_inputs();
        auto search = associations.find(op_name);
        if (op_type.compare("Input") == 0 || op_type.compare("Const") == 0 || search != associations.end())
        {
            if (is_eval_scalar())
            {
                total = values[expr_id];
            }
            else
            {
                if (op_type.compare("Input2d") == 0)
                {
                    dim_ = array_values[expr_id]->get_dim();
                    data_ = array_values[expr_id]->get_data();
                    shape_ = new size_t[4];
                    size_t N = array_values[expr_id]->get_shape()[0];
                    size_t H = array_values[expr_id]->get_shape()[1];
                    size_t W = array_values[expr_id]->get_shape()[2];
                    size_t C = array_values[expr_id]->get_shape()[3];
                    shape_[0] = N;
                    shape_[1] = C;
                    shape_[2] = H;
                    shape_[3] = W;
                }
                else
                {
                    if (array_values.find(expr_id) != array_values.end())
                    {
                        dim_ = array_values[expr_id]->get_dim();
                        data_ = array_values[expr_id]->get_data();
                        shape_ = array_values[expr_id]->get_shape();
                    }
                    else
                    {
                        std::cout << "$$$$$$$" << '\n';
                        std::cout << "unable to find array value" << '\n';
                        std::cout << "$$$$$$$" << '\n';
                    }
                }
            }
            continue;
        }
        bool firstLoop = true;
        std::list<ndarray *> arrays;
        for (auto input : inputs)
        {
            if (is_eval_scalar())
            {
                if (op_type.compare("Add") == 0)
                {
                    total += values[input];
                }
                else if (op_type.compare("Sub") == 0)
                {
                    if (firstLoop)
                    {
                        total = values[input];
                    }
                    else
                    {
                        total -= values[input];
                    }
                }
                else if (op_type.compare("Mul") == 0)
                {
                    if (total == 0 && firstLoop)
                    {
                        total = 1;
                    }
                    total *= values[input];
                }
                else
                {
                    std::cout << "Incorrect Op Type" << '\n';
                    return -1;
                }
                firstLoop = false;
            }
            else
            {
                arrays.push_back(array_values[input]);
            }
        }
        values[expr_id] = total;
        array_values[expr_id] = evaluate_ndarrays(arrays, op_type);
        dim_ = array_values[expr_id]->get_dim();
        data_ = array_values[expr_id]->get_data();
        shape_ = array_values[expr_id]->get_shape();
    }
    result_ = total;
    return 0;
}

ndarray *evaluation::evaluate_ndarrays(std::list<ndarray *> arrays, std::string op_type)
{
    ndarray *result;
    bool firstLoop = true;
    int count = 0;
    for (auto array : arrays)
    { 
        std::cout << "-------" << '\n';
        std::cout << op_type << '\n';
        std::cout << "-------" << '\n';
        if (firstLoop)
        {
            result = new ndarray(array->get_dim(), array->get_shape(), array->get_data());
            firstLoop = false;
            continue;
        }
        if (op_type.compare("Add") == 0)
        {
            result->add_data(array);
        }
        else if (op_type.compare("Sub") == 0)
        {
            result->sub_data(array);
        }
        else if (op_type.compare("Mul") == 0)
        {
            result->mul_data(array);
        }
        else if (op_type.compare("ReLU") == 0)
        {
            result = new ndarray(array->get_dim(), array->get_shape(), array->get_data());
            result->relu();
        }
        else if (op_type.compare("Flatten") == 0)
        {
            result = new ndarray(array->get_dim(), array->get_shape(), array->get_data());
            result->flatten();
        }
        else
        {
            std::cout << "Incorrect Op Type" << '\n';
            return nullptr;
        }
    }
    return result;
}

double &evaluation::get_result()
{
    return result_;
}

int evaluation::get_dim()
{
    return dim_;
}

size_t *evaluation::get_shape()
{
    return shape_;
}

double *evaluation::get_data()
{
    return data_;
}

void evaluation::print_assocs()
{
    std::cout << "++++++++++" << '\n';
    for (auto elem : associations)
    {
        std::cout << elem.first << " -> " << elem.second << "\n";
    }
    std::cout << "++++++++++" << '\n';
}

void evaluation::print_values()
{
    std::cout << "//////////" << '\n';
    for (auto elem : values)
    {
        std::cout << elem.first << " -> " << elem.second << "\n";
    }
    std::cout << "//////////" << '\n';
}

void evaluation::print_result()
{
    std::cout << "$$$$$$$" << '\n';
    std::cout << result_ << '\n';
    std::cout << "$$$$$$$" << '\n';
}

bool evaluation::is_eval_scalar()
{
    return array_values.empty();
}

void evaluation::print_array_attrs()
{
    std::cout << "~~~~~~~" << '\n';
    for (auto elem : array_values)
    {
        std::cout << elem.first << "\n";
        elem.second->print_ndarray();
    }
    std::cout << "~~~~~~" << '\n';
}
