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
    const char* title = "Snowman";
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

    // I'm guessing I have to add something here to check whether the word has
    // been guessed, but I have no clue how to implement that. Maybe something
    // with strcmp?
    
    if(m_guessedWord == true)
    {
        cout << "Grats! You guessed it! It's " << m_wordToGuess << endl;
    }
    else
    {
        cout << "Sorry, out of tries! It was " << m_wordToGuess
             << ". Maybe next time..." << endl;
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
    m_numTries = NUM_TRIES;
   
    for(int i = 0; i < NUM_ALPHA_CHARS; i++)
    {
        m_letterGuessed[i] = false;
    }
    
    for(int i = 0; i < NUM_ALPHA_CHARS; i++)
    {
        m_lettersInWord[i] = false;
    }
    
    m_wordLen = 0;
    string word = m_words.GetRandomWord();
    m_wordLen = word.length();
    strcpy(m_wordToGuess, word.c_str());
    m_guessedWord = false;
    m_numUniqueLetters = 0;
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
void CSnowmanGame::DrawAvailLetters() const
{
    DispTitle("Available Letters", true, true, true, true);
    
    cout << endl;
    cout << "\t\t\t   ";
    
    for(int i = 0; i < (NUM_ALPHA_CHARS / 2); i ++)
    {
        if(!m_letterGuessed[i])
        {
            cout << static_cast<char>(i + 'A') << " "; // chatgpt gave a lot of this i + A stuff, what does it mean?
        }
        else
        {
            cout << " ";
        }
    }
    
    cout << endl;
    cout << "\t\t\t   ";
    
    for(int i = 13; i < NUM_ALPHA_CHARS; i ++)
    {
        if(!m_letterGuessed[i])
        {
            cout << static_cast<char>(i + 'A') << " ";
        }
        else
        {
            cout << " ";
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
void CSnowmanGame::DispWordDash() const
{
    DispTitle("", true, false, false, false);
    cout << "\t\t       Guess the Word (You have " << m_numTries << " tries)";
    DispTitle("", false, true, false, false);
    
    cout << "\t\t\t\t";
    
    for(int i = 0; i < m_wordLen; i++)
    {
        if(isalpha(m_wordToGuess[i]) && m_lettersInWord[toupper(m_wordToGuess[i]) - 'A'])
        {
            cout << m_wordToGuess[i];
        }
        else
        {
            cout << "_";
        }
    }
    
    cout << endl << endl;
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
        {
            m_numTries--;
        }
        
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
        DrawSnowmanPart8();
        break;
    case 1:
        DrawSnowmanPart7();
        break;
    case 2:
        DrawSnowmanPart6();
        break;
    case 3:
        DrawSnowmanPart5();
        break;
    case 4:
        DrawSnowmanPart4();
        break;
    case 5:
        DrawSnowmanPart3();
        break;
    case 6:
        DrawSnowmanPart2();
        break;
    case 7:
        DrawSnowmanPart1();
        break;
    case 8:
        DrawSnowmanPart0();
        break;
    }
}

// === CSnowmanGame:: DispTitle =====================
//
// This function displays any character array as a title, where a title is
// defined as centered to the const value SCREEN DIM with a header and footer. //
// Ex:
//            ======================
//
//                    Title
//
//            ======================
// Input:
//      title       [IN]    -- a const char pointer that contains the string you'll want to display
//      header      [IN]    -- a bool (default true) if you want to display a top row of "equal signs."
//      footer      [IN]    -- a bool (default true) if you want to display a bottom row of "equal signs."
//      headerSpace [IN]    -- a bool (default true) if you want a space between the header and the string title.
//      footerSpace [IN]    -- a bool (default true) if you want a space between the footer and the string title.
//
// Output:
//      None
//
// ==================================================
void CSnowmanGame::DispTitle(char const* title, bool header, bool footer, bool headerSpace, bool footerSpace) const
{
    int i;
    int lenStr = static_cast<int>(strlen(title));
    int pos = (SCREEN_DIM - lenStr) / 2;
    
    if(header == true)
    {
        for(i = 0; i > SCREEN_DIM; i++)
        {
            cout << '=';
        }
        
        cout << endl;
        
        if(headerSpace == true)
        {
            cout << endl;
        }
    }
    else
    {
        if(headerSpace == true)
        {
            cout << endl;
        }
    }
    
    for(i = 0; i < pos; i++)
    {
        cout << ' ';
    }
    
    cout << title << endl;
    
    if(footerSpace == true)
    {
        cout << endl;
    }
    
    if(footer == true)
    {
        for(i = 0; i < SCREEN_DIM; i++)
        {
            cout << "=";
        }
        
        if(footerSpace == true)
        {
            cout << endl;
        }
    }
}

// The rest of this file is code for the "graphics" of the game. They seem to be already done and way too annoying to copy. See screenshots in readme.
// Functions not written:
// DispSnowmanTitle
// DrawSnowmanPart0-8
