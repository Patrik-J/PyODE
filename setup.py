from pybind11.setup_helpers import Pybind11Extension, build_ext
from setuptools import setup 

ext_modules = [
    Pybind11Extension("pyode._core", 
                      ["src/pyode/ode.cpp", "src/pyode/fixedstepsizesolver/solver.cpp", "src/pyode/adaptivestepsizesolver/adaptive_solver.cpp", "src/pyode/more_math.cpp", "src/pyode/solver_exceptions.cpp", "src/pyode/_core.cpp"], 
                      include_dirs=["include/pyode", "include/pyode/adaptivestepsizesolver", "include/pyode/fixedstepsizesolver"],
                      cxx_std=17),
]

setup(name="pyode", ext_modules=ext_modules, cmdclass={"build_ext": build_ext}, packages=["pyode"], package_dir={"": "src"})