import numpy as np
import easynn as nn
import easynn_golden as golden

# Create a numpy array of 10 rows and 5 columns.
# Set the element at row i and column j to be i+j.
def Q1():
    elements = np.zeros((10,5))
    for i in range(10):
        for j in range(5):
            elements[i][j] = i + j
    return elements

# Add two numpy arrays together.
def Q2(a, b):
    return a + b

# Multiply two 2D numpy arrays using matrix multiplication.
def Q3(a, b):
    return np.matmul(a, b)

# For each row of a 2D numpy array, find the column index
# with the maximum element. Return all these column indices.
def Q4(a):
    return np.argmax(a, axis=1)

# Solve Ax = b.
def Q5(A, b):
    return np.matmul(np.linalg.inv(A), b)

# Return an EasyNN expression for a+b.
def Q6():
    a = nn.Input("a")
    b = nn.Input("b")
    return a + b

# Return an EasyNN expression for a+b*c.
def Q7():
    a = nn.Input("a")
    b = nn.Input("b")
    c = nn.Input("c")
    return a + b * c

# Given A and b, return an EasyNN expression for Ax+b.
def Q8(A, b):
    A_node = nn.Input("A")
    x = nn.Input("x")
    b_node = nn.Input("b")
    expression = A_node * x + b_node
    cc = expression.compile(golden.Builder())
    return cc(A = A, b = b)

# Given n, return an EasyNN expression for x**n.
def Q9(n):
    x = nn.Input("x")
    expression = x
    if (n > 1):
        for i in range(n - 1):
            expression = x * expression
    return expression

# Return an EasyNN expression to compute
# the element-wise absolute value |x|.
def Q10():
    x = nn.Input("x")
    return (x * x) / x
