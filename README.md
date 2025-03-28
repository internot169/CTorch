# CTorch

## Running the code

To install the package from test PyPi, run

```
pip install -i https://test.pypi.org/simple/ toyml-internot169==0.0.1
```

## Architectural Choices
For the architecture, I've created an abstraction called a Predictor which encompasses all of the individual algorithms under one umbrella. Each Predictor takes in a set of parameters (matrices, vectors, activations) and performs operations on given inputs based on the parameters. Each separate machine learning model will perform its own set of operations. Encapsulating the matrices, vectors, and activations within a Predictor allows the Predictor to easily modify the matrix and vector parameters to better fit the data. It also allows for easy modularity in implementing new algorithms - the same code for the optimization loop works for every individual predictor. This also allows the data to be housed externally (fed in as an input to each predictor), which prevents data leakage. Data that the model should never see will never be seen by the model. Lastly, the internal housing of the matrices and vectors allows for the addition of backpropagation history, which is a slight improvement on pure numerical differentiation.

I exported this C++ package to Python using nanobind - all of the package is bound to specifically named functions in Python. Users of the package in python can access the C++ code by just using Python. I deployed this code to PyPi using the hatch and twirl libraries. 

The demo consists of example usage of my initial work from the midterm deliverable and my work from the second half of the study. Initially, it focuses on gradient descent on multivariable functions. This is a machine learning scenario where the computer knows all of the input data and information and thus can calculate the exact solution. The rest of the code is focused on applications that work with real data. The computer doesn't know all of the input data, and thus the fitting process is more difficult.

![image](https://github.com/user-attachments/assets/5f95bb96-b541-420e-b68f-83d34c0813d0)
