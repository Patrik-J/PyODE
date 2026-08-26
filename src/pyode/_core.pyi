"""
Bindings for the ODE class
"""
from __future__ import annotations
import collections.abc
import typing
__all__: list[str] = ['AdamsBashforthSolver', 'AdaptiveStepsizeSolver', 'BackwardEulerSolver', 'EulerSolver', 'FixedStepsizeSolver', 'ODE', 'RK45Solver', 'RK4Solver']
class AdamsBashforthSolver(FixedStepsizeSolver):
    def __init__(self, ode: ODE, s: typing.SupportsInt | typing.SupportsIndex = 2) -> None:
        """
        Create an instace of the AdamsBashforthSolver class
        """
    def step(self, stepsize: typing.SupportsFloat | typing.SupportsIndex) -> None:
        """
        Perform a Adams-Bashforth step.
        """
class AdaptiveStepsizeSolver:
    def __repr__(self) -> str:
        ...
    def getCurrentSolution(self) -> list[float]:
        """
        Get the result of the previous step.
        """
    def getCurrentTime(self) -> float:
        """
        Get the current time after the previous step.
        """
    def setInitialConditions(self, initial: collections.abc.Sequence[typing.SupportsFloat | typing.SupportsIndex], t0: typing.SupportsFloat | typing.SupportsIndex = 0.0) -> None:
        """
        Set the initial conditions.
        """
    def setInitialStepsize(self, initial_stepsize: typing.SupportsFloat | typing.SupportsIndex = 0.001) -> None:
        """
        Set the initial stepsize.
        """
class BackwardEulerSolver(FixedStepsizeSolver):
    def __init__(self, ode: ODE) -> None:
        """
        Create an instace of the BackwardEulerSolver class
        """
    def step(self, stepsize: typing.SupportsFloat | typing.SupportsIndex) -> None:
        """
        Perform an backwards Euler step.
        """
class EulerSolver(FixedStepsizeSolver):
    def __init__(self, ode: ODE) -> None:
        """
        Create an instace of the EulerSolver class
        """
    def step(self, stepsize: typing.SupportsFloat | typing.SupportsIndex) -> None:
        """
        Perform an Euler step.
        """
class FixedStepsizeSolver:
    def __repr__(self) -> str:
        ...
    def getCurrentSolution(self) -> list[float]:
        """
        Get the result of the previous step.
        """
    def setInitialConditions(self, initial: collections.abc.Sequence[typing.SupportsFloat | typing.SupportsIndex], t0: typing.SupportsFloat | typing.SupportsIndex = 0.0) -> None:
        """
        Set the initial conditions.
        """
class ODE:
    def __call__(self, t: typing.SupportsFloat | typing.SupportsIndex, y: collections.abc.Sequence[typing.SupportsFloat | typing.SupportsIndex]) -> list[float]:
        """
        Call the function defining the ODE
        """
    def __init__(self, func: collections.abc.Callable[[float, list[float]], typing.SupportsFloat | typing.SupportsIndex]) -> None:
        """
        Create an instance of the ODE class
        """
class RK45Solver(AdaptiveStepsizeSolver):
    def __init__(self, arg0: ODE, arg1: typing.SupportsFloat | typing.SupportsIndex) -> None:
        """
        Create an instace of the RK45Solver class
        """
    def step(self) -> None:
        """
        Perform a RK4(5) step.
        """
class RK4Solver(FixedStepsizeSolver):
    def __init__(self, ode: ODE) -> None:
        """
        Create an instace of the RK4Solver class
        """
    def step(self, stepsize: typing.SupportsFloat | typing.SupportsIndex) -> None:
        """
        Perform a RK4 step.
        """
