#pragma once
#include <iostream>
#include "Player.h"
#include "API\TicTacToeAPI.h"

class TicTacToe : public ITicTacToe
{
public:
	TicTacToe();
	TicTacToe(const std::string& player1Name, const std::string& player2Name, int n, int m);
	TicTacToe(const TicTacToe&) = delete;
	TicTacToe& operator =(const TicTacToe&) = delete;
//inherited
	int GetRows()const noexcept override;
	int GetColumns()const noexcept  override;
	char GetCellAt(int rowNumber,int colNumber) const noexcept  override;
	std::string GetActivePlayerName()  override;
	bool WinCheck()  override;
	bool FullBoard() const  override;
	EMoveResult TakeTurn(int lineNumber,int colNumber) override;
	~TicTacToe();
private:
//procedures
	std::string GetPlayer1Name() noexcept;
	std::string GetPlayer2Name() noexcept;
	bool VerifyCellExists() const;
	bool VerifiyCellOccupied() const;
	void CellFill( char x) const;
	void SwitchTurn();


	bool CheckColumn() const;
	bool CheckRow() const;
	bool CheckMainDiagonal() const;
	bool CheckSecDiagonal() const;
	
//members	
private:
	int m_rows, m_cols;
	int m_lPosRow, m_lPosCol;
	char** m_board;
	int m_turnNumber;
	Player m_player1;
	Player m_player2;
	std::shared_ptr<IStrategy> m_strategy;
};