#include "TicTacToe.h"

TicTacToe::TicTacToe(const int n, const int m)
	: m_rows(n), m_cols(m)
{
	if (m_rows > m_cols)
	{
		auto aux = m_rows;
		m_rows = m_cols;
		m_cols = aux;

	}
	const int c = m;
	m_board = new char* [n];

	for (int index = 0; index < m; index++)
	{
		m_board[index] = new char[m];
	}

}

bool TicTacToe::CheckDiagonals(const int& rowNumber, const int& colNumber) const
{
	//main diagonal
	int rowIndex = rowNumber;
	int columnIndex = colNumber;
	bool up = true, down = false;
	char symbol = m_board[rowNumber][colNumber];
	while (rowIndex < m_cols && columnIndex < m_cols)
	{
		if (m_board[rowIndex][columnIndex] != symbol)
		{
			down = false;
			break;
		}
		++rowIndex, ++columnIndex;
	}
	while (rowIndex >= 0 && columnIndex >= 0 )
	{
		if (m_board[rowIndex][columnIndex] != symbol)
		{
			down = false;
			break;
		}
		--rowIndex, --columnIndex;
	}
	if (up && down) return true;

	return false;
}

void TicTacToe::CellFill(const int& line, const int& column, const char& x = 'x') const
{
	m_board[line][column] = x;
}

bool TicTacToe::CheckRow(const int& rowNumber) const
{
	char firstSymbol = m_board[rowNumber][0];
	for (int columnIndex = 1; columnIndex < m_cols; columnIndex++)
		if (m_board[rowNumber][columnIndex] != firstSymbol)
			return false;
	return true;
}

bool TicTacToe::CheckColumn(const int& colNumber) const
{
	char firstSymbol = m_board[0][colNumber];
	for (int lineIndex = 1; lineIndex < m_rows; lineIndex++)
		if (m_board[lineIndex][colNumber] != firstSymbol)
			return false;
	return true;
}
