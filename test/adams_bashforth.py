from pyode.fixedstepsizesolver import AdamsBashforthSolver
from pyode import ODE

def harmonic_oscillator(t, y):
    # y'' = -y
    return -y[0]

# create the ODE
ode = ODE(harmonic_oscillator)

# initial conditions
t0 = 0.0
y0 = [1.0, 0.0]

# init the 
AdBa2 = AdamsBashforthSolver(ode, 2)
AdBa2.setInitialConditions(y0, t0)
AdBa3 = AdamsBashforthSolver(ode, 3)
AdBa3.setInitialConditions(y0, t0)
AdBa4 = AdamsBashforthSolver(ode, 4)
AdBa4.setInitialConditions(y0, t0)
AdBa5 = AdamsBashforthSolver(ode, 5)
AdBa5.setInitialConditions(y0, t0)

# show solver info
print(AdBa2)
print(AdBa3)
print(AdBa4)
print(AdBa5)

# storage 
t = [t0]
adba2_y = [y0[0]]
adba3_y = [y0[0]]
adba4_y = [y0[0]]
adba5_y = [y0[0]]

# stepsize
h = 0.01

# steps
steps = 5_000

# iterate
for _ in range(steps):
    AdBa2.step(h)
    AdBa3.step(h)
    AdBa4.step(h)
    AdBa5.step(h)
    
    t.append(t[-1] + h)
    adba2_y.append(AdBa2.getCurrentSolution()[0])
    adba3_y.append(AdBa3.getCurrentSolution()[0])
    adba4_y.append(AdBa4.getCurrentSolution()[0])
    adba5_y.append(AdBa5.getCurrentSolution()[0])

from matplotlib import pyplot as plt

plt.figure(figsize=(8,6))
plt.plot(t, adba2_y, label="Adams-Bashforth (s = 2)")
plt.plot(t, adba3_y, label="Adams-Bashforth (s = 3)")
plt.plot(t, adba4_y, label="Adams-Bashforth (s = 4)")
plt.plot(t, adba5_y, label="Adams-Bashforth (s = 5)")
plt.legend()
plt.grid()
plt.show()