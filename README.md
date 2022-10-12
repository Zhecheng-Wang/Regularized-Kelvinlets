# Regularized Kelvinlets: Sculpting Brushes based on Fundamental Solutions of Elasticity
A naive C++ implementaion of the SIGGRAPH 2017 paper Regularized Kelvinlets (de Goes et al. 2017) with a viewer and time integration. This is a CMake project.

---
### Author
Zhecheng Wang

---
### Implemented Brushes
- [ ] Grab
- [X] Twist
- [X] Scale
- [X] Pinch

---
### Working Brushes
- [ ] Grab
- [X] Twist
- [ ] Scale
- [X] Pinch

---
### Prerequisites
[polyscope](https://polyscope.run/)

[libigl](https://libigl.github.io/)

---
### Installation
Clone from this repo

    git clone https://github.com/Zhecheng-Wang/Regularized-Kelvinlets.git

Initialize build folder and compile the code

    mkdir build
    cd build
    cmake ..
    make

To run the program, run ``kelvinlets`` in the ``build`` folder with a mesh in the ``data`` folder.

---
### References
**Papers:** [[de Goes *et al.*, 2017]](https://graphics.pixar.com/library/Kelvinlets/paper.pdf)
