from pyode import ODE, EulerSolver, RK4Solver

from matplotlib import pyplot as plt

def harmonic_oscillator(t, y):
    # y'' = -y
    return -y[0]

# create the ODE
ode = ODE(harmonic_oscillator)

# initial conditions
t0 = 0.0
y0 = [1.0, 0.0]

# set the solver
solver1 = EulerSolver(ode)
solver1.setInitialConditions(y0, t0)

solver2 = RK4Solver(ode)
solver2.setInitialConditions(y0, t0)


# show info
print(solver1)
print(solver2)

# storage
all_t_1 = [t0]
all_y_1 = [y0[0]]

all_t_2 = [t0]
all_y_2 = [y0[0]]


# stepsize
h = 0.01

# stepss
steps = 2000

# iterate
for _ in range(steps):
    # get the next Euler step
    solver1.step(h)
    res = solver1.getCurrentSolution()

    # add the point
    all_y_1.append(res[0])
    all_t_1.append(all_t_1[-1] + h)
    
    # get the next RK4 step
    solver2.step(h)
    res = solver2.getCurrentSolution()

    # add the point
    all_y_2.append(res[0])
    all_t_2.append(all_t_1[-1] + h)

plt.figure(figsize=(8, 6))
plt.plot(all_t_1, all_y_1, label="Euler method")
plt.plot(all_t_2, all_y_2, label="RK4 method")
plt.title("Harmonic Oscillator")
plt.legend()
plt.grid()
plt.show()