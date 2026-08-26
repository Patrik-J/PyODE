# PyODE

This repository holds a small project to create an extension for Python written in C++ to solve ODEs numerically. Methods with both fixed and adaptive stepsizes are available to the user.

## Installation

To get this thing running, simply run the *generate.py* Python-script, which will use *pybind11* to build a Python package from the C++ source code and install it using pip.  

## Usage

### Fixed stepsize solver: Euler method

```Python

from pyode.fixedstepsizesolver import EulerSolver
from pyode import ODE

def harmonic_oscillator(t, y):
    # y'' = -y
    return -y[0]

# create the ODE
ode = ODE(harmonic_oscillator)

# initial conditions
t0 = 0.0
y0 = [1.0, 0.0]

# init the solvers
euler = EulerSolver(ode)
euler.setInitialConditions(y0, t0)

# show solver info
print(euler)

# storage 
t = [t0]
euler_y = [y0[0]]

# stepsize
h = 0.01

# steps
steps = 5_000

# iterate
for _ in range(steps):
    euler.step(h)
    backward_euler.step(h)
    
    t.append(t[-1] + h)
    euler_y.append(euler.getCurrentSolution()[0])
    
from matplotlib import pyplot as plt

plt.figure(figsize=(8,6))
plt.plot(t, euler_y, label="Euler")
plt.legend()
plt.grid()
plt.show()

```

### Adaptive stepsize solver: Runge-Kutta 4(5)

```Python

from pyode.adaptivestepsizesolver import RK45Solver
from pyode import ODE

def harmonic_oscillator(t, y):
    # y'' = -y
    return -y[0]

# create the ODE
ode = ODE(harmonic_oscillator)

# initial conditions
t0 = 0.0
y0 = [1.0, 0.0]

# stepsize
h = 0.01

# init the solver
rk45 = RK45Solver(ode, 1e-6)

# set initial conditions
rk45.setInitialConditions(y0, t0)
rk45.setInitialStepsize(h)

# show info
print(rk45)

# storage
t = [t0]
y = [y0[0]]

# max steps
max_steps = 10_000

while len(t) < max_steps:
    rk45.step()
    t.append(rk45.getCurrentTime())
    y.append(rk45.getCurrentSolution()[0])
    
from matplotlib import pyplot as plt

plt.figure(figsize=(8, 6))
plt.plot(t, y, label="Runge-Kutta 4(5)")
plt.legend()
plt.grid()
plt.show()

```