// Wordle project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <random>

#define FILEPOS "../words.txt"

#define FOREGROUND(color, text) "\x1B[" << static_cast<int>(color) << "m" << text << "\033[0m"
#define BACKGROUND(color, text) "\033[3;42;" << static_cast<int>(color) << "m" << text << "\033[0m"

enum class ForegroundColor : int {
    Red = 31,
    Green = 32,
    Yellow = 33,
    BrightRed = 91,
    BrightGreen = 92,
    BrightYellow = 93
};

enum class BackgroundColor : int {
    Red = 41,
    Green = 42,
    Yellow = 43,
    BrightRed = 101,
    BrightGreen = 102,
    BrightYellow = 103
};

int getFileLineCount(const std::string& fileName)
{
    std::ifstream file(fileName.c_str(), std::ifstream::in | std::ifstream::binary);
    std::string line;
    int count = 0;

    if (file.is_open())
    {
        while (!file.eof())
        {
            getline(file, line); // counts the ammount of characters in file
            count++;
        }
    }
    return count; // divides by 5, the lenght of the words
}

std::string getLine(int lineNumber, std::string filename)
{
    std::ifstream file(filename, std::ifstream::in);
    std::string line;
    if (file.is_open())
    {
        for (size_t i = 0; i < lineNumber; i++)
        {
            getline(file, line);
        }
         return line;
    }
}

int main()
{
    srand(time(nullptr));
    int randomLine = rand() % getFileLineCount(FILEPOS);
    std::string lineToGuess = getLine(randomLine, FILEPOS);

    std::cout << FOREGROUND(ForegroundColor::BrightRed, randomLine) << std::endl;
    std::cout << FOREGROUND(ForegroundColor::BrightRed, getFileLineCount(FILEPOS)) << std::endl;
    std::cout << BACKGROUND(BackgroundColor::BrightRed, lineToGuess) << std::endl;
}
/*

Analyze and implement the game Wordle as a console application written in object oriented C++.

Implement the games overall structure and features in an object oriented way.
Consider the player experience.

Wordle is a game were you need to guess a five letter word. You have six tries.

Game loop

    Player guess the word.
    Letters not in the word are marked with a grey background.
    Letters in the word but on the wrong place is marked with a yellow background.
    Letters in the word and in the correct place is marked with a green background.

When the player has successfully guessed the word or failed at doing so, the game should ask the player to play again.


    The code should compile without any issues.
    No runtime crashes (handle wrongful input from user).
    Read words from file.
    Custom container for the words (motivate what structure you implemented and why it's good for this case).  (What is this?????)
    Read words from file.
    Good code quality (readable, well structures and good and consistent naming).

*/