# CSnowman
## I'm gonna copy relevant info from the assignment prompt. Sorry in advance for the terrible formatting lol. Screenshots of the prompt will be below if you prefer that.
Unfortunately I simply can't view some files so we'll have to ignore **SampleExecutable.out** and the IntToCStringLib files. Also, this assignment has no dumb restrictions like previous assignments. Thankfully.

## Sample Output
It should look like this: https://youtu.be/1C9ZrDrdiow

# Objective
Your objective for this project is to work on several classes to construct a game called CSnowman.  It is the politically correct version for “Hangman” with the same rules.  You’ll have eight (8) tries to guess the correct word/phrase.  For every incorrect guess, a body part of the snowman will be drawn. Now how will the game be constructed and what classes are we going to make in order for the game to work?

# Starter Kit

Fortunately, you won’t need to construct the entire project yourself as I created a starter kit. The starter kit includes 11 files: **main.cpp**, **CPlayer.h**, **CPlayer.cpp**, **CSnowmanGame.h**, **CSnowmanGame.cpp**, **CWords.h**, **CWords.cpp**, **IntToCString.h**, **IntToCString.o**, **ListOfMarvelCharacters.txt**, and **SampleExecutable.out**. Your objective is to implement all the .cpp files only.  The headers file and main.cpp have been completed for you.
(I don't have access to **SampleExecutable.out** code, we can only run it to see how it plays.)

# Project Description

The description of the files below is the recommended order you should work on them.

## CWords Class

I recommend that you get this class to run on its own before you proceed to the next phase (next class).  You can create a temporary main.cpp to test the features of your class.

    CWords.h -- This header file contains the declaration for the CWords class. This class is used to read and store locally the words/lines in a file and randomly select a word.

    CWords.cpp -- This is the implementation file of CWords.h. The file is filled with function headers with comments/descriptions to guide you in the implementation.  As a note, you’ll need to use the libraries cstdlib and ctime for the functions srand, time, and rand.  You’ll need to seed the random function with the current time to make sure each run is unique.  To set it you’ll use the code srand(time(NULL)). To obtain a random number after you seeded the random function is call the function rand.  Be sure to do your research on what the random function returns. (Hint: You'll be using the modulus operator to get the range you like).

## CSnowmanGame Class

This class contains the entire structure of the game and will take the majority of your time.  Perhaps, it may be best to learn and program the CPlayer class before implementing this class.

    CSnowmanGame.h -- This header file contains the declaration for the CSnowmanGame class.  This class includes the header file CWords.h.  It contains four global constants with the explanations below:
        NUM_TRIES: The number of tries to give the user
        NUM_ALPHA_CHARS: The number of alphabetical characters
        SCREEN_DIM: The dimension of the screen to center the titles
        SLEEP_NUM_SNOWMAN: The number of seconds for the program to sleep when displaying a message to the user.  This will give them some time to read the message before proceeding to the next statement.

The class contains three (3) public functions: the default constructor, Start, and Reset.  The constructor initializes the game.  The Start function begins the game and the Reset functions reset the game environment should the player decide to play again after winning or losing.

The class has eight (8) private data members.

    m_numTries: The number of tries to give the user
    m_wordToGuess: A char array to store the word to guess
    m_letterGuessed: A bool array that stores true/false whether each letter was guessed correctly based on the position of the array.  Element zero (0) represents the letter 'A' and element 25 represents the letter 'Z'
    m_lettersInWord: A bool array that stores true/false whether each letter exists in the word to guess.
    m_wordLen: The length of the random word selected
    m_guessedWord: A bool to represent whether the random word was guessed correctly or not
    m_numUniqueLetters: An int that represents the number of unique letters in the random word selected
    m_words: A CWords object used to read items in a file and randomly select a word/phrase.

The class contains 17 private member functions.  These functions cannot be called outside of the class.  Only public member functions have access to call the private member functions.  The explanation of each function is given in the implementation file.

    CSnowmanGame.cpp -- This is the implementation file of CSnowmanGame.h. The file is filled with function headers with comments/descriptions to guide you in the implementation. As a note, you’ll use the sleep function described in the CWords Class to sleep the program for SLEEP_NUM_SNOWMAN seconds to display the appropriate message when needed.  I've left some functions fully implemented for you to use to save you time and research in this project.  Furthermore, I've included my own header file called "IntToCStringLib.h" should you want to convert an integer to a CString.  I'll note how you'll compile it in a later section below.

## main.cpp

Contains a fully implemented function to use with all the classes.

 
## ListOfMarvelCharacters.txt

Contains a listing of 1253 words/phrases separated by newlines.  This file will be used to be read by the CWords class. (For the purposes of keeping my sanity, I'm just gonna copy like 10 words.)

## IntroToCStringLib

This contains the header and implementation for two functions to convert an int to a CString.  You don’t need to use this, but I included it in case you want to convert an int to a CString. (IntToCStringLib.o is unreadable to me so idk if we can even use this if we wanted to.)

    IntToCStringLib.h -- A header file that contains the function prototypes of the two functions and a description of how to use them.

    IntToCStringLib.o -- An object file of the two functions.  This file has already been compiled (to keep hidden the implementation of the two functions).  If you are going to use the functions, you don’t need to compile it, but simply use the linker to link it to your executable file.

Screenshots of the prompt:
![Screenshot 2023-05-11 194719](https://github.com/Nyriki/CSnowman/assets/76397078/ec356d48-b068-44f5-95d4-df46ab307394)
![Screenshot 2023-05-11 194955](https://github.com/Nyriki/CSnowman/assets/76397078/9919386b-6d4b-4ef9-9249-bf6c8ce3337a)
![Screenshot 2023-05-11 195023](https://github.com/Nyriki/CSnowman/assets/76397078/4a2cda22-4773-4c9d-88a3-db9cd97c43f0)

Snippet of CSnowmanGame.cpp code I didn't transcribe:
![Screenshot 2023-05-13 124843](https://github.com/Nyriki/CSnowman/assets/76397078/56d87d71-2d50-4bbe-bdc6-d3e44f145d47)

