#pragma once
/*
	This is the console executable and uses BullCow Class.
	Responsable for all user interaction.
*/

#include<iostream>
#include<string>
#include "FBullCowGame.h"

//FText is used mainly for user input,standard Unreal coding rules
using FText = std::string;
//int32 is the standard for int in Unreal
using int32 = int;

void PrintIntro();
void PlayGame();
bool PlayAgain();
FText GetValidGuess();
void PrintGameSummary();
FBullCowGame BCGame;

int main()
{
	do
	{
		PrintIntro();
		
		PlayGame();
	}
	while (PlayAgain());
	
	return 0;
}

void PrintIntro()
{
	std::cout << "       ***Welcome to Bulls and Cows, a fun word game!***   \n";
	std::cout << std::endl;
	std::cout << "    ((   _______   ))		  _______      " << std::endl;
	std::cout << "    \\\(/	          \\)/	       /	   \\     " << std::endl;
	std::cout << "     {  =0=   =0=  }	      (  =0=   =0=  )	   	  " << std::endl;
	std::cout << "      \\		  /	       \\           /		   " << std::endl;
	std::cout << "       \\|       |/		\\|	 |/     " << std::endl;
	std::cout << "       \\__0___0__/		\\__0___0__/    " << std::endl;
	std::cout << std::endl;
	std::cout << "This game's task is guessing the hidden isogram word in a number of tries." << std::endl;
	std::cout << "An isogram is a word with no repeating letters." << std::endl;
	std::cout << "So,can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking off in " << BCGame.GetMaxTries() << " tries?" << "\n";

	return;
}

void PlayGame()
{ 
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	//loop until game is won and there are still tries left
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();
		
		//Submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls << " ";
		std::cout << "Cows = " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();
	return;
}

FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	//Keep looping until the guess is valid
	do
	{
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << std::endl;

		FText Guess = "";
		std::cout << "Enter your guess : ";
		std::getline(std::cin, Guess);

		Status = BCGame.IsGuessValid(Guess);
		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a valid isogram(do not repeat any letter)!" << "\n\n";
			break;
		case EGuessStatus::Length_Is_Wrong:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter guess!" << "\n\n";
			break;
		case EGuessStatus::Not_LowerCase:
			std::cout << "Please write the guess using only lowercase letters!" << "\n\n";
			break;
		default:
			return Guess;
		}
	}
	while (Status != EGuessStatus::OK);
}

//Giving the option to play again
bool PlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word?(Y/N)" << std::endl;
	FText Response = "";
	std::getline(std::cin, Response);

	return (Response[0] == 'Y') || (Response[0] == 'y');
}

void PrintGameSummary() 
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Good job! You've won!" << std::endl;
	}
	else
	{
		std::cout << "You ran out of tries! Try out next time!" << std::endl;
	}
}

