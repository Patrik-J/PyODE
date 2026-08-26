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