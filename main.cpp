// File: main.cpp

#include <iostream>
#include "CPlayer.h"
using namespace std;

int main()
{
	// create a CPlayer object
	CPlayer player1("Darth Vader");

	// or create a basic (guest) player
	// CPlayer player1;

	char userResp;

	// create a do-while loop to have the user play as much as they like
	do {
		// start the game
		player1.Start();

		// game ended, ask if the user wants to play again
		cout << "Do you want to play again? (Y/N): ";
		cin >> userResp;

		cout << endl << endl << endl;

		userResp = toupper(userResp);

		if (userResp == 'Y')
		{
			player1.Reset();
		}

	} while (userResp == 'Y')

	cout << "\n\nThanks for playing " << player1.GetName() << "!\n";
	cout << "Goodbye!\n\n";

	return 0;
}
