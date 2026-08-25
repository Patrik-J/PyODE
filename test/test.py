from pyode import ODE, EulerSolver, RK4Solver, AdamsBashforthSolver

from matplotlib import pyplot as plt

def harmonic_oscillator(t, y):
    # y'' = -y
    return -y[0]

# create the ODE
ode = ODE(harmonic_oscillator)

# initial conditions
t0 = 0.0
y0 = [1.0, 0.0]

# set the solvers
solver1 = EulerSolver(ode)
solver1.setInitialConditions(y0, t0)

solver2 = RK4Solver(ode)
solver2.setInitialConditions(y0, t0)

solver3 = AdamsBashforthSolver(ode, 2)
solver3.setInitialConditions(y0, t0)

solver4 = AdamsBashforthSolver(ode, 3)
solver4.setInitialConditions(y0, t0)

solver5 = AdamsBashforthSolver(ode, 5)
solver5.setInitialConditions(y0, t0)

# show info
# print(solver1)
# print(solver2)
# print(solver3)
# print(solver4)

# storage
all_t_1 = [t0]
all_y_1 = [y0[0]]

all_t_2 = [t0]
all_y_2 = [y0[0]]

all_t_3 = [t0]
all_y_3 = [y0[0]]

all_t_4 = [t0]
all_y_4 = [y0[0]]

all_t_5 = [t0]
all_y_5 = [y0[0]]

# stepsize
h = 0.01

# stepss
steps = 4000

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
    all_t_2.append(all_t_2[-1] + h)

    # get the next AdamsBashforth (s=2) step
    solver3.step(h)
    res = solver3.getCurrentSolution()

    # add the point
    all_y_3.append(res[0])
    all_t_3.append(all_t_3[-1] + h)

    # get the next AdamsBashforth (s=3) step
    solver4.step(h)
    res = solver4.getCurrentSolution()

    # add the point
    all_y_4.append(res[0])
    all_t_4.append(all_t_4[-1] + h)

    # get the next AdamsBashforth (s=5) step
    solver5.step(h)
    res = solver5.getCurrentSolution()

    # add the point
    all_y_5.append(res[0])
    all_t_5.append(all_t_5[-1] + h)

plt.figure(figsize=(8, 6))
plt.plot(all_t_1, all_y_1, label="Euler method")
plt.plot(all_t_2, all_y_2, label="RK4 method")
plt.plot(all_t_3, all_y_3, label="Adams-Bashforth method (s=2)")
plt.plot(all_t_4, all_y_4, label="Adams-Bashforth method (s=3)")
plt.plot(all_t_5, all_y_5, label="Adams-Bashforth method (s=5)")
plt.title("Harmonic Oscillator")
plt.legend()
plt.grid()
plt.show()