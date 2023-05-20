// File: CWords.cpp
// This is the implementation file for the CWords class

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>	// srand function
#include <ctime>	// time function
#include "CWords.h"
using namespace std;


// === CWords::CWords ================================
// 
// This is the CWords default constructor. It initializes the private data 
// members. It sets m_numWords to zero, allocates space for m_words, and 
// calls the ReadFile function.
// 
// Input:
//		none
// 
// ===================================================
CWords::CWords()
{
    m_numWords = 0;
    
    for (int i = 0; i < NUM_WORDS; i++)
    {
        m_words[i] = nullptr;
    }
    
    ReadFile();
}


// === CWords::~CWords ===============================
// 
// This is the CWords destructor. It releases the dynamic memory.
// 
// Input:
//		none
//
// ===================================================
CWords::~CWords()
{
    for (int i = 0; i < m_numWords; i++)
    {
        delete[] m_words[i];
    }
}


// === CWords::GetRandomWord =========================
//
// This function randomly selects a word from m_words and returns it as a 
// const char pointer. It must first seed the random function (srand) to the 
// current time to start the randomness. Then use the random function (rand) 
// to randomly select a word.
//
// Input:
//		none
//
// Output:
//		a const char pointer that contains the string of the random word/phrase
//
// ===================================================
const char* CWords::GetRandomWord()
{
    srand(static_cast<unsigned int>(time(nullptr))); 
    
    if(m_numWords > 0)
    {
        int randomIndex = rand() % m_numWords;
        
        return m_words[randomIndex];
    }
    
    return nullptr;
}


// === CWords::ReadFile ==============================
//
// This function reads the contents of the file that has a word separated by 
// a new line. As a note, the word can be a combination of two words (as a 
// name in this case). You will read the contents of the file until there are 
// no more words to read or NUM_WORDS has been exhausted. As you read each 
// word, be sure to update m_numWords (number of words read).
// 
// Input:
//		none
// 
// ===================================================
void CWords::ReadFile()
{
    ifstream file("ListOfMarvelCharacters.txt");
    
    if (!file)
    {
        cerr << "Error opening word list file." << endl;
        exit(1);
    }
    
    string word;
    int wordCount;
    
    while(getline(file, word) && wordCount < NUM_WORDS)
    {
        m_words[wordCount] = new char[CHAR_SIZE];
        strncpy(m_words[wordCount], word.c_str(), CHAR_SIZE - 1);
        m_words[wordCount][CHAR_SIZE - 1] = '\0';
        wordCount++;
    }
    
    m_numWords = wordCount;
    
    file.close();
}










