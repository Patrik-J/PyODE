from pyode import ODE, EulerSolver, RK4Solver

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
rk4 = RK4Solver(ode)
rk4.setInitialConditions(y0, t0)

# show solver info
print(euler)
print(rk4)

# storage 
t = [t0]
euler_y = [y0[0]]
rk4_y = [y0[0]]

# stepsize
h = 0.01

# steps
steps = 5_000

# iterate
for _ in range(steps):
    euler.step(h)
    rk4.step(h)
    
    t.append(t[-1] + h)
    euler_y.append(euler.getCurrentSolution()[0])
    rk4_y.append(rk4.getCurrentSolution()[0])
    
from matplotlib import pyplot as plt

plt.figure(figsize=(8,6))
plt.plot(t, euler_y, label="Euler")
plt.plot(t, rk4_y, label="Runge-Kutta 4")
plt.legend()
plt.grid()
plt.show()