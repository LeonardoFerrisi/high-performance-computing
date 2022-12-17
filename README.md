# High Performance Computing

## A collection of projects demonstrating concepts in high performance computing

# 

<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about">About</a>
    </li>
    <li>
        <a href="#projects">Projects</a>
        <ul>
            <li><a href="#c-bootcamp">C Bootcamp</a></li>
            <li><a href="#mpi">Message Passing Interface: MPI</a></li>
            <ul>
                <li><a href="#mpi-bootcamp">MPI Bootcamp</a></li>
                <li><a href="#mpi-collective">MPI Collective</a></li>
                <li><a href="#mpi-advanced">MPI Advanced</a></li>
            </ul>
            <li><a href="#tictactoe-parallel">Parallelized Tic Tac Toe<a></li>
            <li><a href="#openmp">OpenMP<a></li>
            <ul>
                <li><a href="#openmp-bootcamp">OpenMP Intro</a></li>
                <li><a href="#openmp-advanced">OpenMP Advanced</a></li>
            </ul>
            <li><a href="#final-project">Final Project; Prim's Algorithm and Fourier Transform - Parallelized</a></li>
        </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Setup</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>

#

## About
The following is a collection of projects demonstrating Parallel Computing and Concepts in High Performance Computing

## Projects

### C Bootcamp

### MPI

Demonstrations in distributed memory parallelization

#### MPI Bootcamp

The purpose of this project was gain a feel for reading and writing code that uses the MPI framework to send and receive data across distributed memory tasks.

Check out mpi-bootcamp [here](https://github.com/LeonardoFerrisi/high-performance-computing/tree/main/mpi-bootcamp)

#### MPI Collective

A demonstration in collective communication protocols and vector normalization to  implement parallelized vector normalization.

Check out mpi-collective [here](https://github.com/LeonardoFerrisi/high-performance-computing/tree/main/mpi-collective)

#### MPI Advanced

A demonstration of advanced MPI collective communication, most importantly `MPI_Reduce`, one of the most important concepts in parallel programming.

Check out mpi-advanced [here](https://github.com/LeonardoFerrisi/high-performance-computing/tree/main/mpi-advanced)

### TICTACTOE Parallel

A demonstration of parallelizing a game-playing AI for TIC TAC TOE

Check out parallel-tictactoe [here](https://github.com/LeonardoFerrisi/high-performance-computing/tree/main/parallel-tictactoe)

### OpenMP

Demonstrations in shared memory parallelization

#### OpenMP Bootcamp

The purpose of this project was gain a feel for reading and writing code that uses the OpenMP framework to send and receive data across shared memory tasks.

Check out openmp-bootcamp [here](https://github.com/LeonardoFerrisi/high-performance-computing/tree/main/openmp-bootcamp)

#### OpenMP Advanced

A demonstration with matrix addition (adding two 2D matrices of equal size) and matrix transposition of square matrixes (swap elements around the diagonal) using
* use double precision floating point and dynamically allocated arrays (done in starter code)
* write helper functions to initialize each matrix with appropriately randomized numbers (elaborate on starter code)
* time each *serial* function using the OpenMP timing functions across a range of matrix sizes (be sure not to time your randomization routines):
    * Matrix Sizes: 100x100, 500x,1000x,2000x,4000x,8000x (larger if time/space allow)
* Always use square matrices! Much easier!

Check out openmp-advanced [here](https://github.com/LeonardoFerrisi/high-performance-computing/tree/main/openmp-advanced)

### Final Project

A demonstration of parallelizing Prim's Algorithm and the Fourier Transform

Check out final-project [here](https://github.com/LeonardoFerrisi/high-performance-computing/tree/main/final-project)


