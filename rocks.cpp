#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include "utilities.h"
#include <cstring>
using namespace std;

const int MAXWORDS = 9000;

//checks if probeWord is 4-6 characters long
bool isValidLength(const char probeWord[])
{
	if ((strlen(probeWord) < 4) || (strlen(probeWord) > 6))
		return false;
	else
		return true;
}

//checks if probeWord has lowercase letters
bool isLower(const char probeWord[])
{
	for (int i = 0; i < strlen(probeWord); i++)
	{
		if (!islower(probeWord[i]))
			return false;
	}
	return true;
}

//checks if probeWord is all alpha characters (letters)
bool isLetter(const char probeWord[])
{
	for (int i = 0; i < strlen(probeWord); i++)
	{
		if (!isalpha(probeWord[i]))
			return false;
	}

	return true;
}

//checks if the array words[] knows the probeWord the user entered
bool knowsWord(const char probeWord[], const char words[][MAXWORDLEN + 1], int nWords)
{
	for (int i = 0; i < nWords; i++)
	{
		if (strcmp(probeWord, words[i]) == 0)
			return true;
	}

	return false;
}

int manageOneRound(const char words[][MAXWORDLEN + 1], int nWords, int wordnum)
{
	int score = 1;

	//checks validity of values inputted
	if (nWords < 0 || wordnum < 0 || wordnum >= nWords)
		return -1;
	
	cerr << "The mystery word is " << words[wordnum] << endl;

	//reads in probeWord
	char probeWord[200];
	cout << "Probe word: ";
	cin.getline(probeWord, 200);

	//keeps asking for probe word until it matches the secret word
	while (strcmp(probeWord, words[wordnum]) != 0)
	{
		//checks if valid probeWord
		if (!isValidLength(probeWord) || !isLower(probeWord) || !isLetter(probeWord))
			cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
		else if (!knowsWord(probeWord, words, nWords))
			cout << "I don't know that word." << endl;
		else
		{
			int rocks = 0;
			int pebbles = 0;
			//creates copy of secret word
			char secretWord[9999] = "";
			strcpy(secretWord, words[wordnum]);

			int secretWordLength = strlen(words[wordnum]);
			int probeWordLength = strlen(probeWord);

			//ROCKS
			//checks if character matches at same location in both strings & adds 1 to rocks
			//changes characters to avoid recounting in pebbles
			for (int i = 0; i < secretWordLength && i < probeWordLength; i++)
				if (words[wordnum][i] == probeWord[i])
				{
					rocks++;
					secretWord[i] = '*';
					probeWord[i] = '#';
				}

			//PEBBLES
			//checks if any character in probeWord = secretWord at a specific position & adds 1 to pebbles
			//changes characters to avoid recounting
			for (int i = 0; i < secretWordLength; i++)
			{
				for (int j = 0; j < probeWordLength; j++)
					if ((secretWord[i] == probeWord[j]))
					{
						pebbles++;
						secretWord[i] = '*';
						probeWord[j] = '#';
					}
			}
			
			//outputs rocks and pebbles and adds 1 to how many tries it took
			cout << "Rocks: " << rocks << ", Pebbles: " << pebbles << endl;
			score++;
		}

		cout << "Probe word: ";
		cin.getline(probeWord, 100);
	}

	//returns # of tries
	return score;
}

// You must not put implementations of loadWords or randInt in rocks.cpp; they belong in utilities.cpp

int main()
{
	char wordList[MAXWORDS][MAXWORDLEN + 1];
	int maxWords = 9000; //number of words actually want to fill in array
	int nWords = 0;

	//# of words loaded into array
	nWords = loadWords(wordList, maxWords);

	//checks if no words loaded
	if (nWords < 1)
	{
		cout << "No words were loaded, so I can't play the game." << endl;
		return 0;
	}
	//continues to game
	else
	{
		int numberOfRounds;
		cout << "How many rounds do you want to play? "; 
		cin >> numberOfRounds;
		cin.ignore(10000, '\n');

		if (numberOfRounds < 0)
		{
			cout << "The number of rounds must be positive." << endl;
			return 0;
		}
		else
		{
			unsigned int minTries = 1000;
			unsigned int maxTries = 1;
			double sumOfTries = 0.0;
			double averageOfTries = 0.0;
			
			//executes # of rounds
			for (int i = 0; i < numberOfRounds; i++)
			{
				cout << endl;

				cout << "Round " << (i + 1) << endl;
				
				//generates random number to get random word from array
				int randomInteger = randInt(0, nWords - 1);

				cout << "The secret word is " << strlen(wordList[randomInteger]) << " letters long." << endl;

				//does one round and records # of tries it took
				int tries = manageOneRound(wordList, nWords, randomInteger);

				//outputs # of tries it took
				if (tries == 1)
					cout << "You got it in 1 try." << endl;
				else
					cout << "You got it in " << tries << " tries." << endl;

				//establishes min and max tries after the respective round
				if (tries < minTries)
					minTries = tries;
				if (tries > maxTries)
					maxTries = tries;

				//adds # of tries of that round to total sum of tries
				sumOfTries += tries;
				//computes average # of tries for rounds thus far
				averageOfTries = sumOfTries / (i + 1);

				cout.setf(ios::fixed);
				cout.precision(2);

				//outputs information gathered
				cout << "Average: " << averageOfTries << ", minimum: " << minTries << ", maximum: " << maxTries << endl;
			}

		}
	}
}