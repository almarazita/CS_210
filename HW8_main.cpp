// Annie Marazita
// HW 8 Taking Turns
// 4/11/22

#include <iostream>
#include "List.h"
#include "player.h"

using namespace std;

int main()
{
	// Create a sorted linked list of player objects
	List<Player> board;
	
	// Create and add new players to the list
	cout << "Welcome to the game!" << endl;
	cout << "Enter the number of players: ";
	int players;
	cin >> players; // Get number of players
	Player curPerson; // Temporary player object 
	for(int i = 1; i <= players; i++) // For each person
	{
		cout << "Enter Player " << i << "'s name: ";
		string name;
		cin >> name;
		cout << "Starting position: ";
		int pos;
		cin >> pos;
		
		curPerson.Set_Name(name); // Set name
		curPerson.Set_Pos(pos); // and starting position
		board.Insert(curPerson); // and insert into the list
	}
	
	// Play the game
	cout << "Let's play!" << endl;	
	while(board.Size() != 0) // Stops when the list is empty (all players at 99 or above)
	{
		Player current; // Player object variable to hold item copied into it from Find_Item_At_Index function
		board.Find_Item_At_Index(1, current); // Get the player the furthest back on the board
		board.Delete(current); // Remove them from the list
		cout << "It's " << current.Get_Name() << "'s turn!" << endl; // Output the name of the player whose turn it is
		cout << "Currently on space " << current.Get_Pos() << endl; // and their current space
		cout << "Enter new space to move: "; // Ask them for a new space
		int move;
		cin >> move;
		while(move <= current.Get_Pos()) // If the new space is not more than the old space, keep asking
		{
			cout << "Cannot move backward. Try again: ";
			cin >> move;
		}
		
		// Check each of the other players' positions to see if the new move will conflict
		Player temp;
		for(int i = 1; i <= board.Size(); i++) // Go through each list entry
		{
			board.Find_Item_At_Index(i, temp); // Copies player object into temp
			// If the move is the same position as another player's, keep asking. We still have to make sure it's not backward.
			while(temp.Get_Pos() == move || move <= current.Get_Pos())
			{
				cout << "Space occupied. Enter a different space to move: "; // Pick a different space
				cin >> move;
			}
		}
		
		// If the space is less than 99, insert a new player object back into the list in the correct sorted position
		if(move < 99)
		{
			current.Set_Pos(move);
			board.Insert(current);
		}
		
		// If the space is 99 or more, the player remains removed from the board
	}
	
	cout << "Game over!" << endl; // The board is now empty
	
	return 0;
}