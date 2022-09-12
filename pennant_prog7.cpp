/****SAMPLE PROGRAM HEADER*******************************************************
NAME: St Goerge Pennant

Description: Hangman Game
*************************************************************/
#include <iostream> //standard library for i/o
#include <string> // always include this when you use the string class
#include <fstream> //file input/ output
#include <cstdlib> //for exit()

using namespace std;

const int numGuesses = 6;//six guesses (head, body, arm1, arm2, leg1, leg2

/*********************************************************
//Following is the declaration of a round of the hangman game
**********************************************************/
class hangmanGame
{
public:
	string solution; //solution word
	string wordGuess; //if the user guesses a correct letter they can guess the word
	char starWord[20];//hint word made of *
	char letters[20];//letters guessed so far (right or wrong)
	int letterCount;//number of letters guessed so far (right or wrong)
	int incorrectCount;//number of incorrect letters guessed so far
	char letterGuess;//current letter guess
	int wordLength;//length of the solution word
	bool correctLetter;//OPTIONAL
	bool win;//flag to set if all the user won that round
};


//Declaration/ Prototypes for your functions will go here
//BE SURE TO ADD COMMENTS TO THE FUNCTION PROTOTYPES AND THE FUNCTION DEFINITIONS

void HangmanRules(const string&);
//Precondition: 
//Postcondition: 
//Description: Provides instructions to the user on how to play the game

void PlayOneRound(const string&, hangmanGame&, ifstream&);
//Precondition: 
//Postcondition: 
//Description: Play one round of the game

void SetUpOneRound(hangmanGame&, ifstream&);
//Precondition: 
//Postcondition: 
//Description: Resets and sets up the member variables for the current round

string GetWord(ifstream&);
//Precondition: 
//Postcondition: 
//Description: Gets the next word from the file

void SetWord(hangmanGame&, const string&);
//Precondition: 
//Postcondition: 
//Description: sets the solution word for the current round

void SetWordLength(hangmanGame&);
//Precondition: 
//Postcondition: 
//Description:  Sets the length of the solution word for the current round

void CreateStarArray(hangmanGame&);
//Precondition: 
//Postcondition: 
//Description:  creates the array of *

void GetLetterGuess(hangmanGame&);
//Precondition: 
//Postcondition: 
//Description:  Displays star array and letters guessed and asks and get a current 
//letter guess

void UpdateLetterArray(hangmanGame&);
//Precondition: 
//Postcondition: 
//Description:  Add the letter guessed to the letters array

bool InterpretLetterGuess(hangmanGame&);
//Precondition: 
//Postcondition: 
//Description:  Check if the letter guessed is in the solution and if it is, replace all * with that 
//letter in the starword and return true, otherwise return false

void CorrectGuess(hangmanGame&, string name);
//Precondition: 
//Postcondition: 
//Description:  checks if it is the final correct letter and if it is not asks if the 
//user wants to guess the word

void GuessTheWord(hangmanGame&);
//Precondition: 
//Postcondition: 
//Description:  allows the user to guess the word

bool GameOver(const hangmanGame&);
//Precondition: 
//Postcondition: 
//Description:  Returns true if the starword matches the solution, you can use ==  
//or if the wordGuess matches the solution, you can use ==

void WonOrLostDisplay(const hangmanGame&, string name);
//Precondition: 
//Postcondition:
//Description: Lets the user know if they won or lost the round

void DrawHangman(hangmanGame&);
//Precondition: 
//Postcondition:
//Description:  Draw or describe the hangman drawing


//HERE IS THE main function, a driver to test your program

int main()
{
	//declare variables
	//name, y or n, file, hangman game object 
	string name;
	ifstream in;
	string yesOrNo = "y";
	hangmanGame activeGame;

	//connect to the input file 
	in.open("words.txt");

	//if //file did not open correctly
	if(in.fail())
	{
		cout << "Input file did not open correctly" << endl;
		exit(1);
	}

	//ask and get the users name
	cout << "Enter your first name: ";
	cin >> name;

	//Hangman rules
	HangmanRules(name);

	//ask and get yes or no if the user wants to play
	cout << endl << "Do you want to play the hangman game? (y or n): ";
	cin >> yesOrNo;

	//loop to contiue to play another round
	while (yesOrNo == "y" || yesOrNo == "Y")
	{
		//play one round of hangman
		PlayOneRound(name, activeGame, in);
		
		//again?
		cout << endl << "Do you want to play the hangman game? (y or n): ";
		cin >> yesOrNo;
	}
	
	in.close();

	return  0;
}

void HangmanRules(const string& name)
//Description: Provides instructions to the user on how to play the game
{
	cout << endl << "\t\t" << name << ", WELCOME TO HANGMAN!" << endl;
	cout << endl << endl << "\tPlease read the following instructions before you play." << endl;
	cout << "\t" << "- You will be presented with a word to be guessed" << endl;
	cout << "\t" << "- Guess letters one at a time" << endl;
	cout << "\t" << "- You can have up to six incorrect letter guesses" << endl;
	cout << "\t" << "- You can only guess the word when you have made a correct letter guess" << endl;
	cout << "\t" << "- The game will be OVER when you have guessed the word correctly" << endl;
	cout << "\t" << "\tOr when you have guessed letters incorrectly SIX times." << endl;
	cout << endl << "\tHAVE FUN!" << endl;
}

void PlayOneRound(const string& name, hangmanGame& activeGame, ifstream& in)
//Description:  Play one round of the game
{
	//reset everything for the new round of the game
	//SetUpOneRound function
	SetUpOneRound(activeGame, in);

	//LOOP FOR THE ROUND OF THE GAME
	//the number of incorrect guesses is less than numGuesses
	//and win is false
	while(activeGame.win == false && activeGame.incorrectCount < numGuesses)
	{
		//GetLetterGuess 
		GetLetterGuess(activeGame);
		
		//UpdateLetterArray - add the letter to the array of guessed letters
		UpdateLetterArray(activeGame);

		if (InterpretLetterGuess(activeGame))
		{
			//the user guessed a correct letter
			cout << endl << "The letter was in the word!" << endl;
			//the user can now guess the word (if they want)
			CorrectGuess(activeGame, name);
		}
		else
		{
			//the user did not guess a correct letter
			cout << endl << name << ", your letter is not in the word" << endl;
			cout << "You have added a body part!" << endl;
			activeGame.incorrectCount++;
		}
		//DrawHangman (tell the user how many incorrect guesses so far)
		DrawHangman(activeGame);
	}

	//WonOrLostDisplay - lets the user know if they won or lost
	WonOrLostDisplay(activeGame, name);
	cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
}

void SetUpOneRound(hangmanGame& activeGame, ifstream& in)
//Description:  resets and sets up the member variables for the current round
{
	activeGame.solution = "";//clear the solution word
	//clear the guessed word
	activeGame.starWord[0] = '\0'; //clear the star array  
	//clear the letters guessed array
	activeGame.letterCount = 0; //letter count starts back at 0
	//reset the number of incorrect guesses
	activeGame.correctLetter = false; //reset correctLetter to false
	//reset win to false
	activeGame.win = false;
	activeGame.incorrectCount = 0;
	activeGame.letters[0] = '\0';

	string word;
	//get a word form the file, GetWord function will return a string
	word = GetWord(in);

	//add the word to the active game, SetWord 
	SetWord(activeGame, word);

	//get the length of the word, SetWordLength 
	SetWordLength(activeGame);

	//CreateStarArray 
	CreateStarArray(activeGame);
	//cout << endl << "Here is the star word so far \n\t" << activeGame.starWord << endl;
}

//SET UP FUNCTION
string GetWord(ifstream& inFile)
//Description: Gets the next word from the file
{
	string word = "";
	//get, and return a word(string) from the file
	inFile >> word;
	//cout << endl << "The solution is " << word;
	return word;
}

//SET UP FUNCTION
void SetWord(hangmanGame& activeGame, const string& word)
//Description: sets the solution word for the current round
{
	//assign the word to the active game
	activeGame.solution = word;
	//cout << "\nWord is " << activeGame.solution;
}

//SET UP FUNCTION
void SetWordLength(hangmanGame& activeGame)
//Description:  Sets the length of the solution word for the current round
{
	//get the length of the word and assign it to activeGame.wordLength
	activeGame.wordLength = activeGame.solution.length();

	//let the user know how many letters are the word
	cout << endl << "The word has " << activeGame.wordLength << " letters." << endl;
}

//SET UP FUNCTION
void CreateStarArray(hangmanGame& activeGame)
//Description:  creates the array of * 
{
	//use  loop to assign '*' to each character in the activeGame.starWord
	//remember to add '\0' to the end of the starword
	//activeGame.wordLength should have the number of letters in the word
	for (int i = 0; i < activeGame.wordLength; i++)
	{
		activeGame.starWord[i] = '*';
	}
	activeGame.starWord[activeGame.wordLength] = '\0';
}

void GetLetterGuess(hangmanGame& activeGame)
//Description:  Display the star array and the letters guessed so far
//and ask and get a current letter guess
{
	//display the star array
	cout << "\n-----------------------------------------";
	cout << endl << "Here is the word so far " << endl << "\n\t" << activeGame.starWord;

	//display the letters that have been guessed so far
	cout << "\n-----------------------------------------";
	cout << endl << "Here are the letters guessed so far " << endl << "\n\t" << activeGame.letters;

	//ask and get a letter guess from the user
	cout << endl<< "\nPlease enter a letter: ";
	cin >> activeGame.letterGuess;
}

void UpdateLetterArray(hangmanGame& activeGame)
//Description:  Add the letter guessed to the letters array
{
	activeGame.letters[activeGame.letterCount] = activeGame.letterGuess;
	
	//update the letterCount
	activeGame.letterCount++;

	//add the '\0' character
	activeGame.letters[activeGame.letterCount] = '\0';
}

bool InterpretLetterGuess(hangmanGame& activeGame)
//Description:  Check if the letter guessed is in the
//word and if it is, replace all * with that letter in the starword
//and return true otherwise return false
{
	bool rv = false;
	//use a loop to search the solution word
	for (int i = 0; i < activeGame.wordLength; i++)
	{
		//if the letter is found
		if (activeGame.letterGuess == activeGame.solution[i])
		{
			//replace the letters in the starword and 
			activeGame.starWord[i] = activeGame.letterGuess;
			
			//set the rv to true
			rv = true;
		}
			//set the rv to true
	}
	return rv;
}

void CorrectGuess(hangmanGame& activeGame, string name)
//Description:  checks if it is the final correct letter and if it is not
//ask if the user wants to guess the word
{
	char guess;
	cout << "\n-----------------------------------------";
	//display the starword
	cout << endl << activeGame.starWord << endl;
	if (GameOver(activeGame)) //the correct letter completed the starword	
	{
		activeGame.win = true;//they won the round by entering all the letters
	}
	else //the user entered a correct letter but it was not the final correct letter
	{
		cout << endl << "IT WILL NOT COUNT AGAINST YOU IF YOU DO NOT GET THE CORRECT WORD!" << endl;
		
		//ask and get a response (y or n) if they want to guess the word
		cout << endl << name << ", would you like to guess the FULL word? (y or n): ";
		cin >> guess;

		if (guess == 'y')
		{
			//GuessTheWord function
			GuessTheWord(activeGame);
		}
	}
}

void GuessTheWord(hangmanGame& activeGame)
//Description:  allows the user to guess the word
{
	cout << "\nWhat is the word: ";
	cin >> activeGame.wordGuess;
	if (GameOver(activeGame))
	{
		activeGame.win = true;
	}
	else
	{
		cout << "\nTHAT WAS NOT THE CORRECT WORD!\n";
	}
}

bool GameOver(const hangmanGame& activeGame)
//Description:  This function will return true if the 
//starword matches the solution, you can use ==  or if the 
//wordGuess matches the solution, you can use ==
{
	if (activeGame.solution == activeGame.wordGuess)
	{
		return true;
	}
	else if (activeGame.solution == activeGame.starWord)
	{
		return true;
	}
	else
	return false;
}

void WonOrLostDisplay(const hangmanGame& activeGame, string name)
//Description: Lets the user know if they won or lost the round
{
	cout << endl <<"\n-----------------------------------------";
	if (activeGame.win)
	{
		//tell the user they won that round
		cout << endl << name << ", you have solved the word without being hung!";
		cout << endl << "YOU WIN!" << endl << endl;
	}
	else
	{
		//tell the user they did not win that round
		cout << endl << "Sorry " << name << " you did not win that round!" << endl << endl;

		//display the solution word
		cout << endl <<"The word was " << activeGame.solution << endl << endl;
	}
}

void DrawHangman(hangmanGame& activeGame)
//Description:  Draw or describe the hangman drawing
{
	cout << "\n------------------------------------------------------";
	cout << "\nO-|--<  O-|--<  O-|--<  O-|--<  O-|--<  O-|--<  O-|--<";
	cout << "\n------------------------------------------------------";
	if (activeGame.incorrectCount == 0)
	{
		cout << "\nYou have no incorrect guesses yet! O-|--<";
	}
	else if (activeGame.incorrectCount == 1)
	{
		cout << "\nHEAD\n - 1 of 6 incorrect guesses!";
		cout << "\n------------------------------------------------------";
		cout << "\nO-|--<  O-|--<  O-|--<  O-|--<  O-|--<  O-|--<  O-|--<";
		cout << "\n------------------------------------------------------";
	}
	else if (activeGame.incorrectCount == 2)
	{
		cout << "\nHEAD\nBODY\n - 2 of 6 incorrect guesses!";
		cout << "\n------------------------------------------------------";
		cout << "\nO-|--<  O-|--<  O-|--<  O-|--<  O-|--<  O-|--<  O-|--<";
		cout << "\n------------------------------------------------------";
	}
	else if (activeGame.incorrectCount == 3)
	{
		cout << "\nHEAD\nBODY\nARM 1\n - 3 of 6 incorrect guesses!";
		cout << "\n------------------------------------------------------";
		cout << "\nO-|--<  O-|--<  O-|--<  O-|--<  O-|--<  O-|--<  O-|--<";
		cout << "\n------------------------------------------------------";
	}
	else if (activeGame.incorrectCount == 4)
	{
		cout << "\nHEAD\nBODY\nARM 1\nARM 2\n - 4 of 6 incorrect guesses!";
		cout << "\n------------------------------------------------------";
		cout << "\nO-|--<  O-|--<  O-|--<  O-|--<  O-|--<  O-|--<  O-|--<";
		cout << "\n------------------------------------------------------";
	}
	else if (activeGame.incorrectCount == 5)
	{
		cout << "\nHEAD\nBODY\nARM 1\nARM 2\nLEG 1\n - 5 of 6 incorrect guesses!";
		cout << "\n------------------------------------------------------";
		cout << "\nO-|--<  O-|--<  O-|--<  O-|--<  O-|--<  O-|--<  O-|--<";
		cout << "\n------------------------------------------------------";
	}
	else if (activeGame.incorrectCount == 6)
	{
		cout << "\nHEAD\nBODY\nARM 1\nARM 2\nLEG 1\nLEG 2\n - 6 of 6 incorrect guesses!";
		cout << endl << "GAME OVER";
		cout << "\n------------------------------------------------------";
		cout << "\nO-|--<  O-|--<  O-|--<  O-|--<  O-|--<  O-|--<  O-|--<";
		cout << "\n------------------------------------------------------";
	}
}









