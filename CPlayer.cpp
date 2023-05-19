// File: CPlayer.cpp
// Implementation file for the CPlayer class

#include <iostream>
#include <cstring>
#include <unistd.h> // sleep function
#include "CPlayer.h"
using namespace std;

const int SLEEP_NUM_PLAYER = 1;

// === CPlayer::CPlayer ===============================
//
// This is the CPlayer default constructor. It allocated space from the 
// HEAP and initializes the private data member m_name to "Guest Player." 
// Furthermore, it sets m_gameResetted to false.
//
// Input:
//		none
//
// ====================================================
CPlayer::CPlayer()
{
    m_name = new char[strlen("Guest Player") + 1];
    strcpy(m_name, "Guest Player");
    m_gameResetted = false;
}

// === CPlayer::CPlayer ===============================
// This is the CPlayer type constructor. It uses the parameter to allocate 
// space from the HEAP and initializes the private data member m_name. 
// Furthermore, it sets m_gameResetted to false.
//
// Input:
//		name	[IN]	-- a char pointer to a given name
//
// ====================================================
CPlayer::CPlayer(const char* name)
{
    m_name = new char[strlen(name) + 1];
    strcpy(m_name, name);
    m_gameResetted = false;
}

// === CPlayer::~CPlayer ==============================
//
// This is the CPlayer destructor. It appropriately releases memory from the HEAP.
//
// Input:
//		none
//
// ====================================================
CPlayer::~CPlayer()
{
    delete[] m_name;
}

// === CPlayer::SetName ===============================
//
// The SetName function uses the parameter to update the private data member 
// m_name. Be sure you have exactly the space needed to store the new name.
//
// Input:
//		name	[IN]	-- a char pointer to a given name
//
// Output:
//		none
//
// ====================================================
void CPlayer::SetName(const char* name)
{
    delete[] m_name;
    m_name = new char[strlen(name) + 1];
    strcpy(m_name, name);
}

// === CPlayer::GetName ===============================
//
// The GetName function returns m_name as a const char pointer.
//
// Input:
//		none
//
// Output:
//		a const char*
//
// ====================================================
const char* CPlayer::GetName() const
{
    return m_name;
}

// === CPlayer::Start =================================
//
// The Start function uses the CSnowmanGame object to begin the game by calling 
// its public member function Start. Before calling the Start function and if 
// the game has not been resetted, the program will display a welcoming message 
// and a game loading message. Afterwards the program will sleep for 
// SLEEP_NUM_PLAYER seconds.
//
// Input:
//		none
//
// Output:
//		none
//
// ====================================================
void CPlayer::Start()
{
    CSnowmanGame game;
    
    if (!m_gameResetted)
    {
        cout << "Welcome, " << m_name << "!" << endl;
        cout << "Loading game..." << endl;
    }
    
    game.Start();
    sleep(SLEEP_NUM_PLAYER);
}

// === CPlayer::Reset =================================
//
// The Reset function uses the CSnowmanGame object to restart the game by calling 
// its public member function Reset. Before calling the Reset function the program 
// wil display a restarting and reloading message. Afterwards the program will 
// sleep for SLEEP_NUM_PLAYER seconds.
//
// Input:
//		none
//
// Output:
//		none
//
// ====================================================
void CPlayer::Reset()
{
    CSnowmanGame game;
    
    cout << "Restarting game..." << endl;
    cout << "Reloading game..." << endl;
    
    game.Reset();
    sleep(SLEEP_NUM_PLAYER);
}
