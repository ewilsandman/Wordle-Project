// Wordle project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <vector>

#define FILEPOS "../words.txt"
#define BACKGROUND(color, text) "\033[3;42;" << static_cast<int>(color) << "m" << text << "\033[0m"

enum class BackgroundColor : int {
	Red = 41,
	Green = 42,
	Yellow = 43,
	BrightRed = 101,
	BrightGreen = 102,
	BrightYellow = 103,
	Grey = 100
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
			getline(file, line); // counts file length
			count++;
		}
	}
	else
	{
		std::cout << "No file with adress " << FILEPOS << " found!" << std::endl;
		std::cout << "Press any key to exit";
		std::cin.get();
		exit(-1);
	}
	return count;
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
	std::cout << "No file with adress " << FILEPOS << " found!" << std::endl;
	std::cout << "Press any key to exit";
	std::cin.get();
	exit(-1);
}
std::vector<char> handleInput()
{
	std::vector<char> inputVector;
	std::string input;
	do
	{
		std::cout << "Enter a valid five letter word\n";
		while (!(std::cin >> input))
		{

			std::cin.clear();
			std::cin.ignore();
			std::cout << "Invalid value, try again.\n";

		}
	} while (input.length() != 5);
	for (size_t i = 0; i < input.length(); i++)
	{
		inputVector.push_back(toupper(input.at(i)));
	}
	return inputVector;
}
bool playAgain()
{
	do
	{
		std::cout << "Play again?, Y or N, case sensitive" << std::endl;
		std::string queryAnswer;
		while (!(std::cin >> queryAnswer))
		{
			std::cin.clear();
			std::cin.ignore();
		}
		if (queryAnswer.find("Y") != std::string::npos)
		{
			return(true);
		}
		else if (queryAnswer.find("N") != std::string::npos)
		{
			return(false);
		}
	} while (true);
}

int main()
{
	srand(time(nullptr));
	void game();
	do
	{
		game();
	} 
	while (playAgain());
}
void game()
{
	std::vector<char> lineToGuessVector;
	std::vector<char> inputVector;
	std::string lineToGuess;
	bool running = true;
	lineToGuessVector.clear();
	bool match[5]{ false,false,false,false,false };
	int randomLine = rand() % getFileLineCount(FILEPOS);
	lineToGuess = getLine(randomLine, FILEPOS);
	transform(lineToGuess.begin(), lineToGuess.end(), lineToGuess.begin(), ::toupper);
	for (size_t i = 0; i < lineToGuess.length(); i++)
	{
		lineToGuessVector.push_back(lineToGuess.at(i));
	}
    system("cls");
	std::cout << "Welcome to scuffed Wordle" << std::endl;
	for (size_t x = 0; x < 6; x++)
	{
		std::cout << "Try " << x + 1 << "/6" << std::endl;
		inputVector = handleInput();
		int countA = 0;
		int countB = 0;
		int stateCount = 0;
		int state[5] = { 0,0,0,0,0 };
		for (char a : lineToGuessVector)
		{
			for (char b : inputVector)
			{
				if (a == b)
				{
					if (countA == countB)
					{
						state[countA] = 1;
					}
					else
					{
						if (state[countB] != 1)
						{
							state[countB] = 2;
						}
					}
				}
				countB++;
			}
			countB = 0;
			countA++;
		}
		for (int s : state)
		{
			if (s == 1)
			{
				std::cout << BACKGROUND(BackgroundColor::BrightGreen, inputVector[stateCount]);
				match[stateCount] = true;
			}
			else if (s == 2)
			{
				std::cout << BACKGROUND(BackgroundColor::Yellow, inputVector[stateCount]);
			}
			else
			{
				std::cout << BACKGROUND(BackgroundColor::Grey, inputVector[stateCount]);
			}
			stateCount++;
		}
		std::cout << std::endl;
		for (size_t i = 0; i < 5; i++)
		{
			if (match[i] != true)
			{
				break;
			}
			else if (i == 4)
			{
				std::cout << "you win, the word was " << lineToGuess << std::endl;
				x = 5;
				break;
			}
		}
	}
	for (size_t i = 0; i < 5; i++)
	{
		if (match[i] != true)
		{
			std::cout << "you loose, the word was " << lineToGuess << std::endl;
			break;
		}
	}
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
	Custom container for the words (motivate what structure you implemented and why it's good for this case). Vector good, array better if not expanding
	Read words from file.
	Good code quality (readable, well structures and good and consistent naming).

*/