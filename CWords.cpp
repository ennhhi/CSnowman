// File: CWords.cpp
// This is the implementation file for the CWords class

#include <iostream>
#include <fstream>
#include <cstdlib>	// srand function
#include <ctime>	// time function
#include "CWords.h"
using namespace std;


// === CWords::CWords ================================
// 
// This is the CWords default constructor. It initializes the private data members. It sets m_numWords to zero, allocates space for m_words, and calls the ReadFile function.
// 
// Input:
//		none
// 
// ===================================================




// === CWords::~CWords ===============================
// 
// This is the CWords destructor. It releases the dynamic memory.
// 
// Input:
//		none
//
// ===================================================




// === CWords::GetRandomWord =========================
//
// This function randomly selects a word from m_words and returns it as a const char pointer. It must first seed the random function (srand) to the current time to start the randomness. Then use the random function (rand) to randomly select a word.
//
// Input:
//		none
//
// Output:
//		a const char pointer that contains the string of the random word/phrase
//
// ===================================================




// === CWords::ReadFile ==============================
//
// This function reads the contents of the file that has a word separated by a new line. As a note, the word can be a combination of two words (as a name in this case). You will read the contents of the file until there are no more words to read or NUM_WORDS has been exhausted. As you read each word, be sure to update m_numWords (number of words read).
// 
// Input:
//		none
// 
// ===================================================
