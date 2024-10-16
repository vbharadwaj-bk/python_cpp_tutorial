# calling_code.py
import cppimport 
import cppimport.import_hook
import my_extension

import numpy as np
import numpy.linalg as la

def hello_world():
    my_extension.hello_world(5)
    my_extension.print_double(3.14)

def greet_and_return5():
    result = my_extension.greet_and_return5("John Doe")
    print(f"Function call returned {result}.")

def test_f_norm():
    rng = np.random.default_rng()
    X = rng.standard_normal(size=(500, 5), dtype=np.float64)
    f_norm_extension = my_extension.f_norm(X)
    f_norm_numpy = la.norm(X, 'fro')
    print(f"F norm by Python extension is {f_norm_extension:3f}.")
    print(f"F norm by Numpy is {f_norm_numpy:3f}.")

def add3_mutate():
    X = np.ones(shape=(2, 2), dtype=np.float64)
    print(X)
    my_extension.add3(X)
    print(X)

def add3_returncopy():
    X = np.ones(shape=(2, 2), dtype=np.float64)
    print(X)
    Y = my_extension.add3_returncopy(X)
    print(Y)

if __name__=='__main__':
    hello_world()
    greet_and_return5()
    test_f_norm()
    add3_mutate()
    add3_returncopy()