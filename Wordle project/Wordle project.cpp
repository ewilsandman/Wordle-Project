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
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <vector>

#define FILEPOS "../words.txt"
#define BACKGROUND(color, text) "\033[3;42;" << static_cast<int>(color) << "m" << text << "\033[0m"

#define CHARINCORRECT 0 // PSA do not #define incorrect
#define	CHARWRONGPOSITION 1
#define CHARCORRECT 2

enum class BackgroundColor : int 
{
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
	std::ifstream file(fileName.c_str(), std::ifstream::in);
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
class HiddenWord 
{
	std::vector<char> hiddenWordVector;
	std::string hiddenWord;
	public:
	HiddenWord();
	std::string getWord() { return hiddenWord; }
	void checkAnswer(std::vector<char> inputVector, int * inputState);
};

HiddenWord::HiddenWord() 
{


	hiddenWordVector.clear();
	int randomLine = rand() % getFileLineCount(FILEPOS);
	hiddenWord = getLine(randomLine, FILEPOS);
	transform(hiddenWord.begin(), hiddenWord.end(), hiddenWord.begin(), ::toupper);
	std::cout << hiddenWord;

	// constructs the vector
	for (size_t i = 0; i < hiddenWord.length(); i++)
	{
		hiddenWordVector.push_back(hiddenWord.at(i));
	}
}



void HiddenWord::checkAnswer(std::vector<char> inputVector, int * inputState)
{
	int hiddenCharPosition = 0;
	int inputCharPosition = 0;


	//Iterates through the hidden word
	for (char hiddenChar : hiddenWordVector)
	{
		//Iterates through input for each char in the hidden word
		for (char inputChar : inputVector)
		{
			if (hiddenChar == inputChar)
			{
				if (hiddenCharPosition == inputCharPosition)
				{
					inputState[hiddenCharPosition] = CHARCORRECT;
				}
				else if (inputState[inputCharPosition] != CHARCORRECT)
				{
					inputState[inputCharPosition] = CHARWRONGPOSITION;
				}
			}
			inputCharPosition++;
		}
		inputCharPosition = 0;
		hiddenCharPosition++;
	}
	//return inputState;
}


bool playAgain()
{
	do
	{
		std::cout << "Play again?, Y or N" << std::endl;
		std::string queryAnswer;
		while (!(std::cin >> queryAnswer))
		{
			std::cin.clear();
			std::cin.ignore();
		}
		if ((queryAnswer.find("Y") != std::string::npos)|| (queryAnswer.find("y") != std::string::npos))
		{
			return(true);
		}
		else if ((queryAnswer.find("N") != std::string::npos) || (queryAnswer.find("n") != std::string::npos))
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
	HiddenWord hiddenWord;
	
	
	bool hasWon = false;

    // system("cls"); // Clears the console, works only on Windows 
	std::cout << "Welcome to cpp Wordle" << std::endl;

	// Main loop, iterates through the players attempts
	for (size_t attempt = 0; attempt < 6; attempt++)
	{
		int inputState[5] = { CHARINCORRECT,CHARINCORRECT,CHARINCORRECT,CHARINCORRECT,CHARINCORRECT };
		std::cout << "Try " << attempt + 1 << "/6" << std::endl;
		std::vector<char> inputVector = handleInput();
		hiddenWord.checkAnswer(inputVector, inputState);
		
		int stateCount = 0; // needed for the program to know what state number we are on
		// iterates through each state, typing out the input
		for (int s : inputState)
		{
			if (s == CHARCORRECT)
			{
				std::cout << BACKGROUND(BackgroundColor::BrightGreen, inputVector[stateCount]);
			}
			else if (s == CHARWRONGPOSITION)
			{
				std::cout << BACKGROUND(BackgroundColor::Yellow, inputVector[stateCount]);
			}
			else // CHARINCORRECT
			{
				std::cout << BACKGROUND(BackgroundColor::Grey, inputVector[stateCount]);
			}
			stateCount++;
		}
		std::cout << std::endl;
		for (size_t i = 0; i < 5; i++)
		{
			if (inputState[i] != 2)
			{
				break;
			}
			else if (i == 4)
			{
				std::cout << "you win, the word was " << hiddenWord.getWord() << std::endl;
				hasWon = true;
				attempt = 5;
				break;
			}
		}
	}
	if (!hasWon)
	{
		std::cout << "you loose, the word was " << hiddenWord.getWord() << std::endl;
	}
}
