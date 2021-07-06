#include "TicTacToe.h"

TicTacToe::TicTacToe()
{
	m_rows = 0;
	m_cols = 0;
	m_board = nullptr;
	m_turnNumber = 1;
}

TicTacToe::TicTacToe(const std::string& player1Name, char player1Symbol, const std::string& player2Name, char player2Symbol, int n, int m)
	: m_rows(n), m_cols(m), m_player1(Player{ player1Name,player1Symbol }), m_player2(Player{ player2Name,player2Symbol }), m_turnNumber(1)
{
	if (m_rows > m_cols)
	{
		auto aux = m_rows;
		m_rows = m_cols;
		m_cols = aux;
	}

	m_board = new char* [m_rows];

	for (int index = 0; index < m_rows; index++)
	{
		m_board[index] = new char[m_cols];
	}

	for (int rowIndex = 0; rowIndex < m_rows; rowIndex++)
	{
		for (int colIndex = 0; colIndex < m_cols; colIndex++)
			m_board[rowIndex][colIndex] = '.';

	}
}

int TicTacToe::GetRows() const noexcept
{
	return m_rows;
}

int TicTacToe::GetColumns() const noexcept
{
	return m_cols;
}

bool TicTacToe::CheckMainDiagonal(int rowNumber,int colNumber) const
{
	//main diagonal
	int rowIndex = rowNumber;
	int columnIndex = colNumber;
	int count = 0;
	
	bool up = true, down = true;
	char symbol = m_board[rowNumber][colNumber];
	while (rowIndex < m_rows && columnIndex < m_cols)
	{
		if (m_board[rowIndex][columnIndex] != symbol)
		{
			down = false;
			break;
		}
		++rowIndex, ++columnIndex, ++count;
	}
	rowIndex = rowNumber;
	columnIndex = colNumber;
	while (rowIndex >= 0 && columnIndex >= 0 )
	{
		if (m_board[rowIndex][columnIndex] != symbol)
		{
			up = false;
			break;
		}
		--rowIndex, --columnIndex, ++count;
	}

	if (count != m_rows + 1) up = false, down = false;
	if (up && down) return true;
	
	return false;
}

bool TicTacToe::CheckSecDiagonal(int rowNumber,int colNumber) const
{
	//secondary diagonal
	int rowIndex = rowNumber;
	int columnIndex = colNumber;
	char symbol = m_board[rowNumber][colNumber];
	bool up = true;
	bool down = true;
	int count = 0;
	while (rowIndex < m_rows && columnIndex >= 0)
	{
		if (m_board[rowIndex][columnIndex] != symbol)
		{
			up = false;
			break;
		}
		++rowIndex, --columnIndex, ++count;
	}
	rowIndex = rowNumber;
	columnIndex = colNumber;
	while (rowIndex >= 0 && columnIndex < m_cols)
	{
		if (m_board[rowIndex][columnIndex] != symbol)
		{
			down = false;
			break;
		}
		--rowIndex, ++columnIndex, ++count;
	}
	if (count != m_rows + 1) up = false, down = false;
	if (up && down) return true;
	return false;
}

bool TicTacToe::VerifiyPosition(int lineNumber, int colNumber) const
{
	if (lineNumber < 0 || colNumber < 0 || lineNumber >= m_rows || colNumber >= m_cols) return false;
	if (m_board[lineNumber][colNumber] != '.') return false;
	return true;
}

bool TicTacToe::FullBoard() const
{
	for (int indexRow = 0; indexRow < m_rows; indexRow++)
	{
		for (int indexCol = 0; indexCol < m_cols; indexCol++)
		{
			if (m_board[indexRow][indexCol] == '.') return false;
		}

	}
	return true;
}

bool TicTacToe::WinCheck(int lineNumber, int colNumber) 
{
	if (CheckColumn(colNumber) ||CheckRow(lineNumber) ||CheckMainDiagonal(lineNumber, colNumber) ||CheckSecDiagonal(lineNumber, colNumber))
	{
		return true;
	};
	return false;
}

void TicTacToe::SwitchTurn()
{
	m_turnNumber = 3 - m_turnNumber;
}

void TicTacToe::TakeTurn(int lineNumber, int colNumber)
{
	char symbol;
	if (m_turnNumber == 1)
		symbol = m_player1.GetSymbol();
	else
		symbol = m_player2.GetSymbol();
	CellFill(lineNumber, colNumber, symbol);
}

char** TicTacToe::GetBoard() const noexcept
{
	return m_board;
}

int TicTacToe::GetTurn() const noexcept
{
	return m_turnNumber;
}
std::string TicTacToe::GetActivePlayerName()
{
	if (m_turnNumber == 1) return GetPlayer1Name();
	else return GetPlayer2Name();
}


std::string TicTacToe::GetPlayer1Name() noexcept
{
	return m_player1.GetName();
}

std::string TicTacToe::GetPlayer2Name() noexcept
{
	return m_player2.GetName();
}

TicTacToe::~TicTacToe()
{
	for (int index = 0; index < m_cols; index++)
		delete m_board[index];
	delete m_board;
}

void TicTacToe::CellFill(int line,int column, char x = 'x') const
{
	m_board[line][column] = x;
}

bool TicTacToe::CheckRow(int rowNumber) const
{
	char firstSymbol = m_board[rowNumber][0];
	for (int columnIndex = 1; columnIndex < m_cols; columnIndex++)
		if (m_board[rowNumber][columnIndex] != firstSymbol)
			return false;
	return true;
}

bool TicTacToe::CheckColumn(int colNumber) const
{
	char firstSymbol = m_board[0][colNumber];
	for (int lineIndex = 1; lineIndex < m_rows; lineIndex++)
		if (m_board[lineIndex][colNumber] != firstSymbol)
			return false;
	return true;
}
