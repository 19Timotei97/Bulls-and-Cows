#pragma once

#include "FBullCowGame.h"
#include<map>
#include<iostream>

#define TMap std::map

//Unreal's standards for int & string
using int32 = int;
using FString = std::string;

FBullCowGame::FBullCowGame() 
{ 
	Reset(); 
} 

int32 FBullCowGame::GetCurrentTry() const 
{ 
	return MyCurrentTry; 
}

int32 FBullCowGame::GetHiddenWordLength() const 
{ 
	return MyHiddenWord.length(); 
}

bool FBullCowGame::IsGameWon() const 
{ 
	return bGame_Won; 
}

//Using map to change the max tries based on the word's length
int32 FBullCowGame::GetMaxTries() const 
{ 
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,16}, {7,20}};
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
	MyHiddenWord = "planet";
	MyCurrentTry = 1;
	bGame_Won = false;

	return;
}

EGuessStatus FBullCowGame::IsGuessValid(FString Guess) const
{
	int32 GuessLength = Guess.length();
	if (!IsIsogram(Guess)) 
	{
		return EGuessStatus::Not_Isogram;
	}
	else if(!IsLowercase(Guess)) 
	{
		return EGuessStatus::Not_LowerCase;
	}
	else if(GuessLength != GetHiddenWordLength())
	{
		return EGuessStatus::Length_Is_Wrong;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

//Gets a valid guess,increments turn,returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); //guess length = hidden word length!
	
	//loop through all letters in the hidden word
	for (int32 HWChar = 0; HWChar < WordLength; HWChar++)
	{
	//compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			//if they match
			if (Guess[GChar] == MyHiddenWord[HWChar])
			{
				//and if they are in the same place!!
				if (HWChar == GChar)
				{
					BullCowCount.Bulls++;
				}	
				else
				{
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength)
	{
		bGame_Won = true;
	}
	else 
	{
		bGame_Won = false;
	}
	return BullCowCount;
}

void FBullCowGame::ChangeWordLength()
{
	FString Word_Array[5] = { "ant", "band", "cable", "detail", "elastic" };
	FString HIDDEN_WORD = "";
	std::cout << "How long the word you're trying to guess should be?(enter digits only please!) " << std::endl;
	int32 Answer;
	std::cin >> Answer;
	switch (Answer)
	{
	case 3:
		std::cout << "You've selected a 3 letter word" << std::endl;
		HIDDEN_WORD = Word_Array[0]; //Must be an isogram!
		MyHiddenWord = HIDDEN_WORD;
		break;
	case 4:
		std::cout << "You've selected a 4 letter word" << std::endl;
		HIDDEN_WORD = Word_Array[1]; //Must be an isogram!
		MyHiddenWord = HIDDEN_WORD;
		break;
	case 5:
		std::cout << "You've selected a 5 letter word" << std::endl;
		HIDDEN_WORD = Word_Array[2]; //Must be an isogram!
		MyHiddenWord = HIDDEN_WORD;
		break;
	case 6:
		std::cout << "You've selected a 6 letter word" << std::endl;
		HIDDEN_WORD = Word_Array[4]; //Must be an isogram!
		MyHiddenWord = HIDDEN_WORD;
		break;
	case 7:
		std::cout << "You've selected a 7 letter word" << std::endl;
		HIDDEN_WORD = Word_Array[5]; //Must be an isogram!
		MyHiddenWord = HIDDEN_WORD;
		break;
	default:
		std::cout << "Please enter a number between 3 and 7!" << std::endl;
		break;
	}
	return;
}


bool FBullCowGame::IsIsogram(FString Word) const
{	
	//treats 0 and 1 letter guesses
	if (Word.length() <= 1) { return true; }
	
	TMap<char, bool> LetterSeen;
	for (auto Letter : Word) //for-each loop used
	{
		Letter = tolower(Letter);
		
		if (LetterSeen[Letter]) 
		{ 
			return false;
		}
		else
		{
			//add the letter to the map
			LetterSeen[Letter] = true;
		}
			
	}
	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}
	return true;
}


