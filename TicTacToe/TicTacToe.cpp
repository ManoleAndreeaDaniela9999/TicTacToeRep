#include "TicTacToe.h"
#include "ClassicPVP.h"
#include "EasyPlayerVsComp.h"
#include "MediumPlayerVsComp.h"
#include "HardPlayerVsComp.h"

TicTacToeAPI::ITicTacToe::Ptr TicTacToeAPI::ITicTacToe::Produce(const std::string& player1Name, const std::string& player2Name, int n, int m)
{
	return std::make_shared<TicTacToe>(player1Name,player2Name, n, m);
}


TicTacToe::TicTacToe()
{
	m_rows = 0;
	m_cols = 0;
	m_board = nullptr;
	m_turnNumber = 1;
	m_lPosRow = 0;
	m_lPosCol = 0;
	m_strategyType = TicTacToeAPI::StrategyType::CLASSIC_PVP;
}

TicTacToe::TicTacToe(const std::string& player1Name, const std::string& player2Name, int n, int m)
	: m_rows(n), m_cols(m), m_player1(Player{ player1Name,'x' }), m_player2(Player{ player2Name,'0' }),
	m_turnNumber(1), m_strategy{new TicTacToeAPI::ClassicPVP} , m_strategyType{ TicTacToeAPI::StrategyType::CLASSIC_PVP }
{
	if (m_rows > m_cols)
	{
		auto aux = m_rows;
		m_rows = m_cols;
		m_cols = aux;
	}
	if (n < 3) m_rows = 3;
	if (m < 3) m_cols = 3; //default 3 if any value is too small

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
	m_lPosRow = 0;
	m_lPosCol = 0;
}

int TicTacToe::GetRows() const noexcept
{
	return m_rows;
}

int TicTacToe::GetColumns() const noexcept
{
	return m_cols;
}
char TicTacToe::GetCellAt(int rowNumber, int colNumber) const noexcept
{
	return m_board[rowNumber][colNumber];
}
bool TicTacToe::CheckMainDiagonal() const
{
	//main diagonal
	int rowIndex = m_lPosRow;
	int columnIndex = m_lPosCol;
	int count = 0;

	bool up = true, down = true;
	char symbol = m_board[m_lPosRow][m_lPosCol];
	while (rowIndex < m_rows && columnIndex < m_cols)
	{
		if (m_board[rowIndex][columnIndex] != symbol)
		{
			down = false;
			break;
		}
		++rowIndex, ++columnIndex, ++count;
	}
	rowIndex = m_lPosRow;
	columnIndex = m_lPosCol;
	while (rowIndex >= 0 && columnIndex >= 0)
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

bool TicTacToe::CheckSecDiagonal() const
{
	//secondary diagonal
	int rowIndex = m_lPosRow;
	int columnIndex = m_lPosCol;
	char symbol = m_board[m_lPosRow][m_lPosCol];
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
	rowIndex = m_lPosRow;
	columnIndex = m_lPosCol;
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

bool TicTacToe::VerifyCellExists() const
{
	if (m_lPosRow < 0 || m_lPosCol < 0 || m_lPosRow >= m_rows || m_lPosCol >= m_cols) return false;
	return true;
}

bool TicTacToe::VerifiyCellOccupied() const
{
	if (m_board[m_lPosRow][m_lPosCol] != '.') return false;
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

bool TicTacToe::WinCheck()
{
	if (CheckColumn() || CheckRow() || CheckMainDiagonal() || CheckSecDiagonal())
	{
		return true;
	};
	return false;
}

void TicTacToe::SwitchTurn()
{
	m_turnNumber = 3 - m_turnNumber;
}

void TicTacToe::SetStrategy(TicTacToeAPI::StrategyType strategyType)
{
	switch (strategyType)
	{
	case TicTacToeAPI::StrategyType::CLASSIC_PVP: { m_strategy = std::make_shared<TicTacToeAPI::ClassicPVP>(); break; }
	case TicTacToeAPI::StrategyType::EASY_PVCOMP: {m_strategy = std::make_shared<TicTacToeAPI::EasyPlayerComp>(); break; };
	case TicTacToeAPI::StrategyType::MEDIUM_PVCOMP: {m_strategy = std::make_shared<TicTacToeAPI::MediumPlayerVsComp>(); break; };
	case TicTacToeAPI::StrategyType::HARD_PVCOMP: {m_strategy = std::make_shared<TicTacToeAPI::HardPlayerVsComp>(); break; };
	}
	m_strategyType = strategyType;
}

//TicTacToeAPI::StrategyType TicTacToe::GetStrategyType()
//{
//}

TicTacToeAPI::EMoveResult TicTacToe::TakeTurn(int lineNumber, int colNumber)
{
	bool PCPlays;
	m_lPosRow = lineNumber;
	m_lPosCol = colNumber;
	if (!VerifyCellExists())
		return TicTacToeAPI::EMoveResult::InvalidPosition;
	if (!VerifiyCellOccupied())
		return TicTacToeAPI::EMoveResult::PositionOccupied;
	char symbol;
	if (m_turnNumber == 1)
	{
		symbol = m_player1.GetSymbol();
	}
	else
	{
		symbol = m_player2.GetSymbol();
	}
	CellFill(symbol);
	PCPlays = m_strategy->ApplyStrategy(m_board,m_turnNumber, m_lPosRow, m_lPosCol, m_rows, m_cols);
	
	if (!PCPlays)
	{
		if (!WinCheck())
			SwitchTurn();
	}
	else
	{	
		if(WinCheck()) return TicTacToeAPI::EMoveResult::Success;
		else {
			SwitchTurn();
			m_lPosRow = lineNumber;
			m_lPosCol = colNumber;
		}
	}
	return TicTacToeAPI::EMoveResult::Success;
}

bool TicTacToe::Reset()
{
	for (int rowIndex = 0; rowIndex < m_rows; rowIndex++)
	{
		for (int colIndex = 0; colIndex < m_cols; colIndex++)
			m_board[rowIndex][colIndex] = '.';
	}
	m_turnNumber = 1;
	return true;
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
	for (int index = 0; index < m_rows; index++)
		delete m_board[index];
	delete m_board;
}

void TicTacToe::CellFill(char x) const
{
	 m_board[m_lPosRow][m_lPosCol] = x;
}

bool TicTacToe::CheckRow() const
{
	char firstSymbol = m_board[m_lPosRow][0];
	for (int columnIndex = 1; columnIndex < m_cols; columnIndex++)
		if (m_board[m_lPosRow][columnIndex] != firstSymbol)
			return false;
	return true;
}

bool TicTacToe::CheckColumn() const
{
	char firstSymbol = m_board[0][m_lPosCol];
	for (int lineIndex = 1; lineIndex < m_rows; lineIndex++)
		if (m_board[lineIndex][m_lPosCol] != firstSymbol)
			return false;
	return true;
}
