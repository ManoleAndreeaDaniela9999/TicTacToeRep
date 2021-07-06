#include "TicTacToeLogic.h"

void TicTacToeLogic::SwitchTurn()
{
	if (m_turnNumber == 1)
		m_turnNumber = 2;
	else m_turnNumber = 1;
}

void TicTacToeLogic::TakeTurn(const int& lineNumber, const int& colNumber)
{
	char symbol;
	if (m_turnNumber == 1)
		symbol = m_player1.GetSymbol();
	else
		symbol = m_player2.GetSymbol();
	m_ticTacToe.CellFill(lineNumber, colNumber, symbol);
}

std::string TicTacToeLogic::WinCheck(const int& lineNumber, const int& colNumber)
{
	if (m_ticTacToe.CheckColumn(colNumber) || m_ticTacToe.CheckRow(lineNumber) || m_ticTacToe.CheckDiagonals(lineNumber, colNumber))
	{
		if (m_turnNumber == 1) return m_player1.GetName();
		else m_player2.GetName();
	};
}

void TicTacToeLogic::ShowBoard()
{
	int rows = m_ticTacToe.GetRows();
	int cols = m_ticTacToe.GetColumns();


}

