// Annie Marazita
// HW3: Sudoku!

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int backtracks = 0;

// Prints puzzle grid to the screen
void showPuzzle(vector<vector<char>> puzzle)
{
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
			cout << puzzle[i][j] << " ";
		cout << endl; // end of one row
	}
}

// Checks row
bool isInRow(vector<vector<char>>& grid, int num, int r)
{
	char ch = num + '0'; // convert from int to char
	for(int c = 0; c < 9; c++) // move down columns of same row
	{
		if(grid[r][c] == ch)
    		return true;
    }
	return false;
}

// Checks column
bool isInCol(vector<vector<char>>& grid, int num, int c)
{
	char ch = num + '0'; // convert int to char
	for(int r = 0; r < 9; r++) // move down rows of same column
	{
		if(grid[r][c] == ch)
			return true;
    }
	return false;
}

// Checks subgrid
bool isInSubgrid(vector<vector<char>>& grid, char num, int r, int c)
{
	char ch = num + '0'; // convert int to char
	r = r - r%3; // start checking at the first row of the subgrid
	c = c - c%3; // and first column of the subgrid
	for(int i = r; i < r+3; i++)
	{
		for(int j = c; j < c+3; j++)
		{
			if(grid[i][j] == ch)
			{
				return true;
			}
		}
	}
	return false;
}

// Checks to see if a number is legally placed.
bool isLegalMove(vector<vector<char>>& grid, int entry, int r, int c)
{
	if(r < 0 || r > 8 || c < 0 || c > 8) // off the grid
		return false;
	if(isInSubgrid(grid, entry, r, c)) // check subgrid
		return false;
	if(isInRow(grid, entry, r)) // check row
		return false;
	if(isInCol(grid, entry, c)) // check column
		return false;
	return true; // haven't returned false, so legal
}

// Checks to see if the puzzle read in from the file is legal to begin with
bool isLegalPuzzle(vector<vector<char>>& grid)
{
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			if(grid[i][j] != '-') // only need to check filled spaces
			{
				int num = grid[i][j] - '0'; // convert char to int to pass to isLegalMove
				grid[i][j] = '-'; // make the cell empty so isLegalMove doesn't incorrectly return false
				if(!isLegalMove(grid, num, i, j))
				{
					grid[i][j] = num + '0'; // convert to char and put it back
					return false; // the puzzle read in from the file is illegal
				}
				grid[i][j] = num + '0'; // convert to char and put it back
			}
		}
	}
	return true; // we never returned false, so none of the entries were illegal
}


// Solves a given Sudoku puzzle using recursive backtracking.
// @pre A legal 9x9 puzzle grid from a file.
// @post Finds a legal solution or determines that the puzzle is unsolvable.
bool solvePuzzle(vector<vector<char>>& grid, int r, int c)
{
	if(r >= 9)
		return true; // base case: looped through the whole board, so all positions are filled legally
	if(grid[r][c] == '-') // cell is empty
	{
		for(int num = 1; num < 10; num++) // go through digits
		{
			if(isLegalMove(grid, num, r, c))
			{
				char ch = num + '0'; // convert int to char
				grid[r][c] = ch; // try it
				if(c == 8)
				{
					if(solvePuzzle(grid, r+1, 0)) // recursive call: solve from beginning of next row
						return true;
				}
				else
				{
					if(solvePuzzle(grid, r, c+1)) // recursive call: solve from next cell
						return true;
				}
				backtracks++; // backtrack: this digit was legal but made the puzzle unsolvable, so try the next one
			}
		}
		grid[r][c] = '-';
		return false; // no digit works
	}
	else // there is already a number in the cell
	{
		if(c == 8) 
			return solvePuzzle(grid, r+1, 0); // skip to next row
		else
			return solvePuzzle(grid, r, c+1); // skip to next cell
	}
	return false; // unsolvable from here, in case I haven't returned something yet
}

int main()
{
	// open test file
	ifstream fin;
	string filename;
	cout << "Enter the filename: ";
	cin >> filename;
	fin.open(filename.data());
	while(!fin.is_open())
	{
		cout << "Illegal filename, try again: ";
		cin >> filename;
		fin.clear();
		fin.open(filename.data());
	}
	
	// read file into 2D vector
	vector<vector<char>> puzzle(9);
	for(int r = 0; r < 9; r++)
		puzzle[r].resize(9);
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
			fin >> puzzle[i][j];
	}
  
	// solve puzzle
	if(isLegalPuzzle(puzzle))
	{
		if(solvePuzzle(puzzle, 0, 0))
		{
			cout << "Solution:\n";
			showPuzzle(puzzle);
			cout << "Backtracked " << backtracks << " times.\n";
		}
		else
		{
			cout << "Unsolvable.\n";
			showPuzzle(puzzle);
			cout << "Backtracked " << backtracks << " times.\n";
		}
	}
	else
	{
		cout << "Unsolvable.\n";
		showPuzzle(puzzle);
	}
	
	return 0;
}