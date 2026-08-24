import subprocess

subprocess.run(["pip", "install", "-e", ".", "--no-build-isolation"]) 
subprocess.run(["pybind11-stubgen", "pyode._core", "--output-dir", "src"]) 