// File: CSnowmanGame.cpp
// This is the implementation file for the CSnowmanGame class

#include <iostream>
#include <cstring>
#include <unistd.h>			// sleep function
#include "CSnowmanGame.h"
using namespace std;

// === CSnowmanGame::CSnowmanGame ====================
//
// This is the CSnowmanGame default constructor. It sets up the environment 
// by initializing the private data members by calling the Reset function.
//
// Input:
//		none
//
// ===================================================
CSnowmanGame::CSnowmanGame()
{
    Reset();
}


// === CSnowmanGame::Start ===========================
//
// This function starts the game. It clears the terminal screen to show only 
// the game by calling the function system("clear"). It further calls member 
// functions to display the title of the game, draw the snowman figure, draw 
// available letters, draw the number of tries, and the word to guess in dashed 
// lines. The Start function will loop continuously until the user guesses 
// correctly or has no more tries. This function will display a message to the 
// user if they have guessed the word(s) correctly or ran out of tries.
//
// Input:
//		none
//
// Output:
//		none
//
// ===================================================
void CSnowmanGame::Start()
{
    system("clear");
    DisplayTitle();
    DrawSnowman();
    DrawAvailLetters();
    DrawNumTries();
    DispWordDash();

    while (true)
    {
        if (HasGuessedWord())
        {
            cout << "Congratulations! You guessed the word correctly!" << endl;
            break;
        }

        if (m_numTries == MAX_TRIES)
        {
            cout << "Game over! You ran out of tries. The word was: " << m_wordToGuess << endl;
            break;
        }

        GetUserGuess();
    }
}


// === CSnowmanGame::Reset ===========================
//
// This function initializes all the private data members. It will use 
// CWords's object to randomly obtain a word and update m_wordToGuess.
//
// Input:
//		none
//
// Output:
//		none
//
// ===================================================
void CSnowmanGame::Reset()
{
    m_wordToGuess = CWords::GetInstance().GetRandomWord();
    m_numTries = 0;
    memset(m_lettersInWord, false, sizeof(m_lettersInWord));
}


// === CSnowmanGame::DrawAvailLetters ================
//
// This function displays the letters over two rows that the user has not 
// guessed yet. At the start of the game, the function will display all the 
// letters in the alphabet. As the user takes their guesses, the letters 
// will be replaced with a space. This will keep the structure/spacing of 
// all the letters the same.
//
// Input:
//		none
//
// Output:
//		none
//
// ===================================================
void CSnowmanGame::DrawAvailLetters()
{
    cout << "Available letters: ";
    for (char letter = 'A'; letter <= 'Z'; letter++)
    {
        if (!m_lettersInWord[letter - 'A'])
        {
            cout << letter << " ";
        }
        else
        {
            cout << "  ";
        }
    }
    cout << endl;
}


// === CSnowmanGame::DispWordDash ====================
//
// This function displays the word to guess with underscores. As the user 
// guesses each correct letter, the function appropriately updates the dash 
// to the letter guessed. As a note, only alphabetical characters are expressed 
// with underscores. If the word contains anything else, like a space, 
// period, or a number, make sure that is not hidden and displayed.
//
// Input:
//		none
//
// Output:
//		none
//
// ===================================================
void CSnowmanGame::DispWordDash()
{
    cout << "Word to guess: ";
    for (size_t i = 0; i < m_wordToGuess.length(); i++)
    {
        if (isalpha(m_wordToGuess[i]))
        {
            if (m_lettersInWord[toupper(m_wordToGuess[i]) - 'A'])
            {
                cout << m_wordToGuess[i] << " ";
            }
            else
            {
                cout << "_ ";
            }
        }
        else
        {
            cout << m_wordToGuess[i] << " ";
        }
    }
    cout << endl;
}


// === CSnowmanGame::GetUserGuess ====================
//
// This function promprs the user to enter a guess. It then validates the 
// guess by calling the IsValidGuess. If the guess is not valid, it will 
// repeatedly ask the user to enter a valid guess.
//
// Input:
//		none
//
// Output:
//		none
//
// ===================================================
void CSnowmanGame::GetUserGuess()
{
    char guess;
    cout << "Enter your guess: ";
    cin >> guess;
    guess = toupper(guess);

    if (!IsValidGuess(guess))
    {
        cout << "Invalid guess! Please enter a valid alphabetical character." << endl;
        sleep(SLEEP_NUM_SNOWMAN);
        GetUserGuess();
        return;
    }

    if (m_lettersInWord[guess - 'A'])
    {
        cout << "You've already guessed the letter '" << guess << "' before." << endl;
        sleep(SLEEP_NUM_SNOWMAN);
        GetUserGuess();
        return;
    }

    m_lettersInWord[guess - 'A'] = true;
    if (!IsCorrectGuess(guess))
    {
        cout << "Wrong guess! The letter '" << guess << "' is not in the word." << endl;
        m_numTries++;
        DrawSnowman();
        DrawNumTries();
        sleep(SLEEP_NUM_SNOWMAN);
    }
    else
    {
        cout << "Correct guess! The letter '" << guess << "' is in the word." << endl;
        DispWordDash();
        sleep(SLEEP_NUM_SNOWMAN);
    }
}



// === CSnowmanGame::IsValidGuess ====================
//
// This function checks if the guess the user entered is valid. The function 
// will return false if the user enters a non-alphabetical character or if 
// the user entered the same letter before. None of these two cases should 
// count against the user's tries. The function returns true if the guess 
// has not been entered before, whether the guess is correct or not. For 
// each case, the function will display an appropriate message and sleep 
// for SLEEP_NUM_SNOWMAN seconds, to let the user read the message before 
// moving on with the program.
//
// Input:
//		guess	[IN]	-- a char to represent the guess of the user
//
// Output:
//		bool			-- true if the guess is valid, false otherwise
//
// ===================================================
bool CSnowmanGame::IsValidGuess(char guess)
{
    guess = toupper(guess);

    if (!isalpha(guess))
    {
        cout << "Invalid guess! Please enter an alphabetical character." << endl;
        sleep(SLEEP_NUM_SNOWMAN);
        return false;
    }

    if (m_lettersInWord[guess - 'A'])
    {
        cout << "You have already guessed that letter before." << endl;
        sleep(SLEEP_NUM_SNOWMAN);
        return false;
    }

    return true;
}


// === CSnowmanGame::GetNumUniqueLetters =============
//
// This function calculates the number of unique letters for the word to guess. 
// It also changes the location of each letter position in m_lettersInWord as true.
//
// Input:
//		none
//
// Output:
//		int		-- number of unique letters in m_wordToGuess
//
// ===================================================
int CSnowmanGame::GetNumUniqueLetters()
{
    memset(m_lettersInWord, 0, sizeof(m_lettersInWord));
    int uniqueLetters = 0;
    for (char c : m_wordToGuess)
    {
        if (isalpha(c) && !m_lettersInWord[toupper(c) - 'A'])
        {
            m_lettersInWord[toupper(c) - 'A'] = true;
            uniqueLetters++;
        }
    }
    return uniqueLetters;
}



// === CSnowmanGame::DrawSnowman =====================
//
// This function draws the appropriate stage/part of the snowman based of the 
// number of tries the user has.
//
// Input:
//		numTries	[In]	-- the number of tries the user has so far
//
// Output:
//		none
//
// ===================================================

// The rest of this file is code for the "graphics" of the game. They seem to be already done and way too difficult to copy. See screenshots in readme for an idea of what I mean lol.
// Functions not written:
// DispTitle
// DispSnowmanTitle
// DrawSnowmanPart0-8
