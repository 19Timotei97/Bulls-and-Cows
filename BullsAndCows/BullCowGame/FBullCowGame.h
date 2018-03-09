/*
	The game's logic is a simple word guessing
*/
#pragma once

#include<string>

//Unreal standards for string and integer
using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Length_Is_Wrong,
	Not_LowerCase
};

//The game's class
class FBullCowGame
{
public:
	FBullCowGame(); 

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus IsGuessValid(FString) const;

	void Reset();
	FBullCowCount SubmitValidGuess(FString);
	void ChangeWordLength();
	

private:
	//see the constructor
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGame_Won;
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;

};