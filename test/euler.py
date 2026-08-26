from pyode.fixedstepsizesolver import EulerSolver, BackwardEulerSolver
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
backward_euler = BackwardEulerSolver(ode)
backward_euler.setInitialConditions(y0, t0)

# show solver info
print(euler)
print(backward_euler)

# storage 
t = [t0]
euler_y = [y0[0]]
bw_euler_y = [y0[0]]

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
    bw_euler_y.append(backward_euler.getCurrentSolution()[0])
    
from matplotlib import pyplot as plt

plt.figure(figsize=(8,6))
plt.plot(t, euler_y, label="Euler")
plt.plot(t, bw_euler_y, label="Backward Euler")
plt.legend()
plt.grid()
plt.show()