// File: CPlayer.h
// This header file contains the declaration for the CPlayer class. The class is used in CSnowmanGame to create the player.

#include "CSnowmanGame.h"

#ifndef CPlayer_h
#define CPlayer_h

// a const for the number of seconds to pause (sleep) the game
const int SLEEP_NUM_PLAYER = 3;

class CPlayer
{
public:
	// constructor(s)
	CPlayer();
	CPlayer(char const* name);

	// destructor
	~CPlayer();

	// public member functions
	void SetName(char const* name);
	const char* GetName() const;
	void Start();
	void Reset();

private:
	char* m_name;			// store player's name
	bool m_gameResetted;	// bool to check if game has been resetted
	CSnowmanGame m_game;	// object used to create the Snowman game
};

#endif /* CPlayer_h */
