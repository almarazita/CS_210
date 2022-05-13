// Program to play a 2-player game of tic-tac-toe.
// Keeps track of the moves of each player, and only takes legal moves
// Checks and reports who won (or a draw)

#include <iostream>
#include <vector>

using namespace std;

const int BOARD_SIZE = 4; // we're using a 4x4 board.

// Pre: "Board" is any two-dimensional vector (but hopefully is the
//      state of a tic-tac-toe game
// Post: Outputs the elements of "Board" to the screen row by row
//      with spacing and borders.
void Print_Board(const vector<vector<char> >& Board){
  cout << endl;
  for(int i = 0; i < Board.size(); i++){
    cout << "|";
    for(int j = 0; j < Board.size(); j++){
      cout << " " << Board[i][j] << " |";
    }
    cout << endl;
  }
  cout << endl;
}

// Pre: Board is a valid Tic-Tac-Toe board (2D, square, contains only
//      'X', 'O', or '-' characters.  "r" and "c" can be any ints
// Post: Returns true if Board[r][c] exists and is a '-' character/
//       Returns false otherwise
bool Check_Move(const vector<vector<char> >& Board, int r, int c){
  // if a value is too small, it's illegal
  if(r < 0 || c < 0)
    return false;

  // if a value is too large, it's illegal
  if(r >= Board.size() || c >= Board.size())
    return false;

  // if we get here, the position is at least on the board.  Now it's legal
  // if what's at that position is a '-'
  if(Board[r][c] == '-')
    return true;
  else
    return false;
}

// Pre: Board is a valid Tic-Tac-Toe board (2D, square, contains only
//      'X', 'O', or '-' characters.  "r" is a legal row in Board
//      (0 <= r < Board.size())
// Post: returns true if all elements of row r are either 'X' or 'O'
//       returns false otherwise
bool Check_Row(const vector<vector<char> >& Board, int r){
  char cur_player = Board[r][0];
  if(cur_player == '-')
    return false; // If the first column is empty, there can't be all
                  // in a row

  for(int j = 1; j < Board[r].size(); j++){
    if(Board[r][j] != cur_player) // found something different
      return false;
  }

  // if we get here, all columns had the same value
  return true;
}

// Pre: Board is a valid Tic-Tac-Toe board (2D, square, contains only
//      'X', 'O', or '-' characters.  "c" is a legal column in Board
//      (0 <= r < Board[0].size())
// Post: returns true if all elements of column c are either 'X' or 'O'
//      returns false otherwise
bool Check_Col(const vector<vector<char> >& Board, int c){
	char cur_player = Board[0][c];
	if(cur_player == '-')
    return false; // If the first row is empty, there can't be all
                  // in a row
  for(int i = 1; i < Board.size(); i++){
    if(Board[i][c] != cur_player) // found something different
      return false;
  }

  // if we get here, all columns had the same value
  return true;
}
// Pre: Board is a valid Tic-Tac-Toe board (2D, square, contains only
//      'X', 'O', or '-' characters.  
// Post: returns true if all elements of the diagonal from
//       the upper-left corner to the lower-right corner are either 'X' or 'O'
//      returns false otherwise
bool Check_NW_SE_Diagonal(const vector<vector<char> >& Board){
  char cur_player = Board[0][0]; // upper left corner
  if(cur_player == '-')
    return false; // empty square on diagonal
  for(int i = 1; i < Board.size(); i++){
    if(Board[i][i] != cur_player) // found something different
      return false;
  }
  // if we get here, all positions are the same
  return true;
}

  // Pre: Board is a valid Tic-Tac-Toe board (2D, square, contains only
//      'X', 'O', or '-' characters.  
// Post: returns true if all elements of the diagonal from
//       the upper-right corner to the lower-left corner are either 'X' or 'O'
//      returns false otherwise
bool Check_NE_SW_Diagonal(const vector<vector<char> >& Board){
  int size = Board.size();
  char cur_player = Board[0][size-1]; // upper right corner
  if(cur_player == '-')
    return false; // empty square on diagonal

  for(int i = 1; i < Board.size(); i++){
    if(Board[i][3-i] != cur_player) // found something different
      return false;
  }
  // if we get here, all positions are the same
  return true;
}

// Pre: Board is a valid Tic-Tac-Toe board (2D, square, contains only
//      'X', 'O', or '-' characters.
// Post: Returns true if the game is over: 4 in a row for X or O,
//       or all spaces filled.
//       Returns false otherwise.
//      If the function returns true, the "winner" reference parameter
//      will be set with the player who won ('X', 'O', or '-' if a draw
bool Is_Game_Over(const vector<vector<char> >& Board, char& winner){
  // First, check for a draw.
  bool empty_found = false;
  for(int i = 0; i < Board.size(); i++){
    for(int j = 0; j < Board.size(); j++){
      if(Board[i][j] == '-')
	empty_found = true;
    }
  }
  
  // Now check all rows for a winner
  for(int i = 0; i < Board.size(); i++){
    if(Check_Row(Board, i)){
      winner = Board[i][0];
      return true;
    }
  }

  // Now check all columns for a winner
  for(int j = 0; j < Board.size(); j++){
    if(Check_Col(Board, j)){
      winner = Board[0][j];
      return true;
    }
  }

  // Now check both diagonals.  I need a better name for these functions
  if(Check_NW_SE_Diagonal(Board)){
    winner = Board[0][0];
    return true;
  }

  if(Check_NE_SW_Diagonal(Board)){
    winner = Board[0][3];
    return true;
  }

	if(!empty_found){ // then all spaces were filled, so it's a draw
	winner = '-';
	return true;
  }
  
  // if none of the possible ways we could have the game over have happened,
  // the game is not over
  return false;
}

int main(){
  vector<vector<char> > Board; // the board
  // We'll use the capital letter 'X' for X,
  // the capital letter 'O' for O,
  // and the '-' character for an empty board.

  // resize the board to the correct size
  Board.resize(BOARD_SIZE);
  for(int i = 0; i<BOARD_SIZE; i++)
  {
	  Board[i].resize(BOARD_SIZE);
  }
 

  

  char play_again = 'y';
  while(play_again == 'y'){  // this loop lets us play the game
                             // several times
    // fill the vector with '-' characters, since the board is empty at the
	// start
	  for(int i = 0; i < BOARD_SIZE; i++){
		for(int j = 0; j < BOARD_SIZE; j++){
		  Board[i][j] = '-';
		}
	  }
    char cur_player = 'X'; // alternate between 'X' and 'O'
 
    char winner; // used in the Is_Game_Over function
    
	cout << endl << "Let's play Tic-Tac-Toe!";
	
    while(!Is_Game_Over(Board, winner)){
      Print_Board(Board);
      cout << "It is player " << cur_player << "s turn" << endl;
      bool is_valid_move = false;
      // we need a loop to check whether the move is valid
   	int r_move;
	int c_move;
      while(!is_valid_move){
	cout << "Enter row (0-3): ";
	cin >> r_move;
	cout << "Enter col (0-3): ";
	cin >> c_move;
	is_valid_move = Check_Move(Board, r_move, c_move);
	if(!is_valid_move)
	  cout << "Illegal move" << endl << endl;
      }
      // now that we know the move is valid, we can update the board
      Board[r_move][c_move] = cur_player;
	  if(cur_player == 'X')
		  cur_player = 'O';
	  else
		  cur_player = 'X';
      
    } // end main game loop
    
    Print_Board(Board);
    // once the game is over, output the winner
    if(winner == 'X'){
      cout << "The game is over, player X won!" << endl;
    }
    if(winner == 'O'){
      cout << "The game is over, player O won!" << endl;
    }
    if(winner == '-'){
      cout << "The game is a draw!" << endl;
    }

    cout << "Play again? (y/n): ";
    cin >> play_again;
	while(play_again != 'y' && play_again != 'n')
	{
		cout << endl << "Enter a valid character (y/n): ";
		cin >> play_again;
	}
	
  }// end loop for one game
  
  return 0;
}
