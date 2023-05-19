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
    const char* title = "xyz";
    bool header = true;
    bool footer = true;
    bool headerspace = true;
    bool footerspace = true;
    
    while (m_numTries > 0 && !m_guessedWord)
    {
        system("clear");
        DispTitle(title, header, footer, headerspace, footerspace);
        DrawSnowman(m_numTries);
        DrawAvailLetters();
        cout << endl;
        DispWordDash();
        GetUserGuess();
    }

    system("clear");
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
    m_numTries = NUM_TRIES;
    m_wordToGuess[0] = '\0';
    memset(m_letterGuessed, false, sizeof(m_letterGuessed));
    memset(m_lettersInWord, false, sizeof(m_lettersInWord));
    m_wordLen = 0;
    m_guessedWord = false;
    m_numUniqueLetters = 0;

    const char* randomWord = m_words.GetRandomWord();
    strncpy(m_wordToGuess, randomWord, sizeof(m_wordToGuess));
    m_wordToGuess[sizeof(m_wordToGuess) - 1] = '\0';

    m_numUniqueLetters = GetNumUniqueLetters();
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
    cout << "Available Letters: ";
    for (int i = 0; i < NUM_ALPHA_CHARS; i++)
    {
        if (!m_letterGuessed[i])
            cout << static_cast<char>(i + 'A') << " ";
        else
            cout << "  ";
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
    cout << "Word to Guess: ";
    for (int i = 0; i < m_wordLen; i++)
    {
        if (isalpha(m_wordToGuess[i]) && m_lettersInWord[toupper(m_wordToGuess[i]) - 'A'])
            cout << m_wordToGuess[i] << " ";
        else
            cout << "_ ";
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
    cout << "Enter a letter as your guess: ";
    char guess;
    cin >> guess;
    cin.ignore(256, '\n');

    if (IsValidGuess(guess))
    {
        bool correctGuess = false;
        for (int i = 0; i < m_wordLen; i++)
        {
            if (toupper(m_wordToGuess[i]) == toupper(guess))
            {
                m_lettersInWord[toupper(guess) - 'A'] = true;
                correctGuess = true;
            }
        }

        if (!correctGuess)
            m_numTries--;

        m_letterGuessed[toupper(guess) - 'A'] = true;
        m_guessedWord = memcmp(m_letterGuessed, m_lettersInWord, sizeof(m_letterGuessed)) == 0;

        if (!correctGuess)
        {
            cout << "Wrong guess!" << endl;
            sleep(SLEEP_NUM_SNOWMAN);
        }
        else if (m_guessedWord)
        {
            cout << "Correct guess!" << endl;
            sleep(SLEEP_NUM_SNOWMAN);
        }
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
    if (!isalpha(guess))
    {
        cout << "Invalid guess! Please enter an alphabetical character." << endl;
        sleep(SLEEP_NUM_SNOWMAN);
        return false;
    }

    if (m_letterGuessed[toupper(guess) - 'A'])
    {
        cout << "You've already guessed the letter " << guess << ". Please enter a different letter." << endl;
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
    int count = 0;
    for (int i = 0; i < m_wordLen; i++)
    {
        if (isalpha(m_wordToGuess[i]) && !m_lettersInWord[toupper(m_wordToGuess[i]) - 'A'])
        {
            m_lettersInWord[toupper(m_wordToGuess[i]) - 'A'] = true;
            count++;
        }
    }
    return count;
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
void CSnowmanGame::DrawSnowman(int numTries) const
{
    switch (numTries)
    {
    case 0:
        DrawSnowmanPart0();
        break;
    case 1:
        DrawSnowmanPart1();
        break;
    case 2:
        DrawSnowmanPart2();
        break;
    case 3:
        DrawSnowmanPart3();
        break;
    case 4:
        DrawSnowmanPart4();
        break;
    case 5:
        DrawSnowmanPart5();
        break;
    case 6:
        DrawSnowmanPart6();
        break;
    case 7:
        DrawSnowmanPart7();
        break;
    case 8:
        DrawSnowmanPart8();
        break;
    }
}

// The rest of this file is code for the "graphics" of the game. They seem to be already done and way too difficult to copy. See screenshots in readme.
// Functions not written:
// DispTitle
// DispSnowmanTitle
// DrawSnowmanPart0-8
