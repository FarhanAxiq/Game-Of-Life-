## __Game of Life__

Just a very simple Conway Game of Life

# _How to Compile_
To compiled, just used this command:
`g++ -std=c++17 -Wall GameOfLife.cpp -o GameOfLife.o`

# _How to use_
The game board is defined in test textfile
where . is dead and O is alive and the board size must
be nxn or greater than 2x2 (so no 1x1 board)

To run it, passed the file after the application name:
`$: ./GameOfLife.o test`

it can also be passed on stdin from file by
using `<` command
i.e: `$./GameOfLife.o<test`

To run iteration on it, use the pipe command:
`$: ./GameOfLife.o test | ./GameOfLife.o`


# _Legal notices_
Made it for a school project but
since the solution is deemed generic enough 
it should not break the school rule of sharing code
and it should be fine to be uploaded here.
