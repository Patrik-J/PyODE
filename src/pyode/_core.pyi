"""
Bindings for the ODE class
"""
from __future__ import annotations
import collections.abc
import typing
__all__: list[str] = ['EulerSolver', 'FixedStepsizeSolver', 'ODE', 'RK4Solver']
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
class RK4Solver(FixedStepsizeSolver):
    def __init__(self, ode: ODE) -> None:
        """
        Create an instace of the RK4Solver class
        """
    def step(self, stepsize: typing.SupportsFloat | typing.SupportsIndex) -> None:
        """
        Perform a RK4 step.
        """
