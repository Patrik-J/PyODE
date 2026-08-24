from pybind11.setup_helpers import Pybind11Extension, build_ext
from setuptools import setup 

ext_modules = [
    Pybind11Extension("pyode._core", 
                      ["src/pyode/ode.cpp", "src/pyode/solver.cpp", "src/pyode/more_math.cpp", "src/pyode/_core.cpp"], 
                      include_dirs=["include/pyode"],
                      cxx_std=17),
]

setup(name="pyode", ext_modules=ext_modules, cmdclass={"build_ext": build_ext},
      packages=["pyode"], package_dir={"": "src"})