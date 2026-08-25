# PyODE

This repository holds a small project to create an extension for Python written in C++ to solve ODEs numerically.

## Why?

I wanted to get a rough outline of how to create C++ extensions for Python using *pybind11*. :D

## Usage

To get this thing running, simply run the *generate.py* Python-script, which will use *pybind11* to build a Python package from the C++ source code and install it using pip.  

The file *test.py* in the *test*-folder shows a simple working example.