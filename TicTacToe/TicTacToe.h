#pragma once
#include <iostream>
#include "Player.h"

class TicTacToe
{

public:
	TicTacToe();
	TicTacToe(const std::string& player1Name,char player1Symbol, const std::string& player2Name, char player2Symbol, int n, int m);
//procedures
	int GetRows()const noexcept;
	int GetColumns()const noexcept;
	int GetTurn() const noexcept;
	char GetCellAt(int rowNumber,int colNumber) const noexcept;
	std::string GetActivePlayerName();
	std::string GetPlayer1Name() noexcept;
	std::string GetPlayer2Name() noexcept;


	
	bool VerifiyPosition(int lineNumber, int colNumber) const;
	bool FullBoard() const;
	bool WinCheck(int lineNumber,int colNumber) ;
	
	void CellFill( int line, int column,  char x) const;

	void SwitchTurn();
	
	void TakeTurn(int lineNumber,int colNumber);

	~TicTacToe();

private:
	bool CheckColumn( int colNumber) const;
	bool CheckRow( int rowNumber) const;
	bool CheckMainDiagonal(int rowNumber , int colNumber) const;
	bool CheckSecDiagonal(int rowNumber ,int colNumber) const;
//members	
private:
	int m_rows, m_cols;
	char** m_board;
	int m_turnNumber;
	Player m_player1;
	Player m_player2;
};