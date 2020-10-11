Just a very simple Conway Game of Life

Written in C++, mostly C++11 onwards
I've compiled this on Ubuntu 16.04 using:
g++ -std=c++17 -Wall GameOfLife.cpp -o GameOfLife.o

since it is simple enough, I feel like I don't have
to write makefile on it

Made it for a school project but
since the solution is generic enough I thought 
it's a good idea to put it on here.

The game board is defined in test textfile
where . is dead and O is alive and the board size must
be nxn or greater than 2x2 (so no 1x1 board)

To run it, passed the file after the application name:
$: ./GameOfLife.o test

it can also be passed on stdin from file by
using < command
i.e: $./GameOfLife.o<test

To run iteration on it, use the pipe command:
$: ./GameOfLife.o test | ./GameOfLife.o
