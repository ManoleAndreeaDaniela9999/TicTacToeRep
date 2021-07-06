#pragma once
#include <iostream>
#include <TicTacToe.h>
#include <Player.h>

class TicTacToeLogic
{
public:
	TicTacToeLogic(const std::string& player1Name, const char& player1Symbol, const std::string& player2Name, const char& player2Symbol, int n, int m)
		: m_player1 ( Player {player1Name,player1Symbol}), m_player2(Player{ player1Name,player2Symbol }), m_ticTacToe(TicTacToe{n,m}) , m_turnNumber(1)
	{
	};
	void SwitchTurn();
	void TakeTurn(const int& lineNumber, const int& colNumber);//turns must be 1 or 0
	std::string WinCheck(const int& lineNumber, const int& colNumber);
	void ShowBoard();
private:
	Player m_player1;
	Player m_player2;
	TicTacToe m_ticTacToe;
	int m_turnNumber;
};

