//
//  GameOfLife.cpp
//  Farhan Haziq
//


#include <iostream>  // std::cin, std::cout. std::istream
#include <fstream>   // std::ifstream
#include <string>    // std::getline
#include <vector>    // std::vector
#include <cstring>
// alias for our 2D vector
using _2D_Vect = std::vector<std::vector<char> >; 

//
//
//  Overload << operator to print the board
//
//
std::ostream &operator<<(std::ostream& out, _2D_Vect &board)
{
	 for (std::vector<char> &row : board) {
		for (char &c : row) { out << c; }
		out << '\n';
	}
	return out;
}


//
//  Check if the board is valid
//  Where:
//  the input is not at least 2×2
//  the input contains a bad character
//  the input has inconsistent line lengths.
//
bool is_valid(_2D_Vect &board)
{
	for (std::vector<char> &row : board){
		// check if board is at least 2x2 or inconsistent length
		if  (row.size() < 2 || board.size() < 2 || row.size() != board.at(0).size()){ return false; } 
		// check if the input is a valid char
		for (char &c : row) { 
			if (c != '.' && c != 'O') { return false; } 
		} 
	}
	return true;
}

//
//
//
//	getting neighbours alive count function
//
//
//
int get_count(const _2D_Vect &board, int &x, int &y, const int &row, const int &col, const char &alive)
{
	int count = 0;
	for (int i = x - 1; i <= x + 1; i++){
		for (int j = y - 1; j <= y + 1; j++){
			int n_row = (i + row) % row;
			int n_col = (j + col) % col;
			// if ourself continue
			// if neighbor alive, count++
			if ((board.at(n_row).at(n_col) == alive) && (i != x || j != y)) { count++; }
		}
	}
	return count;
}

//
//
// The universe of the Game of Life is an infinite, two-dimensional orthogonal grid of square cells, 
// each of which is in one of two possible states, live or dead, (or populated and unpopulated, respectively). 
// Every cell interacts with its eight neighbours, which are the cells that are horizontally, vertically, or diagonally adjacent. 
// At each step in time, the following transitions occur:
//
// Any live cell with fewer than two live neighbours dies, as if by underpopulation.
// Any live cell with two or three live neighbours lives on to the next generation.
// Any live cell with more than three live neighbours dies, as if by overpopulation.
// Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
// These rules, which compare the behavior of the automaton to real life, can be condensed into the following:
//
// Any live cell with two or three live neighbours survives.
// Any dead cell with three live neighbours becomes a live cell.
// All other live cells die in the next generation. Similarly, all other dead cells stay dead.
// stolen from: https://en.wikipedia.org/wiki/Conway's_Game_of_Life
//
//
void game(_2D_Vect &board)
{
	const char dead  = '.';
	const char alive = 'O';
	const int row = board.size();
	const int col = board.at(0).size();
	int life_count = 0;
	// initialize next board
	_2D_Vect next_board{board};
	for (int i = 0; i < row; i++){
		for (int j = 0; j < col; j++){
			life_count = 0;
			char curr_state = board.at(i).at(j);
			life_count = get_count(board, i, j, row, col, alive);
			next_board.at(i).at(j) = dead;
			if (curr_state == alive && (life_count == 2 || life_count == 3)) { next_board.at(i).at(j) = alive; }
			if (curr_state == dead && life_count == 3) { next_board.at(i).at(j) = alive; }
		}
	}
	board = next_board;
	std::cout << board;
}

//
//
//  Create a vector for the game
//  from the file
//  thus creating the initial state
//  of the board.
//
//
_2D_Vect create_board(std::istream &in)
{
	std::string line;
	_2D_Vect board;
	while (std::getline(in, line)){
		std::vector<char> rows;
		for (char &c : line){ rows.emplace_back(c); }
		board.emplace_back(rows);
	}
	// if the board generated isn't valid
	// exit
	// non-valid board is definind in is_valid() function
	if (!is_valid(board)){
		std::cerr << "The board generated is not a valid board.\n";
		exit(1);
	}
	
	return board;
}


int main(int argc, char *argv[])
{
	// try to read the game from file or from stdin
	// first we attempt to open the file
	// if that doesn't work it will
	// redirect to stdin
	std::ifstream file;
	if (!(argv[1] == nullptr)) { file.open(argv[1]); }
	if (!file) { 
		std::cerr << argv[1] << " cannot be open\n"; 
		exit(1);
	}
	std::istream &in = (argc < 2) ? std::cin : file;

	// make a 2D vector, see using for full type definition
	_2D_Vect board = create_board(in);
	game(board);
	file.close();
	return 0;
}