#pragma once
#include <iostream>

class TicTacToe
{
public:
	TicTacToe();
	TicTacToe(const int n,const int m);

	int GetRows()const noexcept;
	int GetColumns()const noexcept;

	void CellFill(const int& line, const int& column, const char& x) const;
	bool CheckColumn(const int& colNumber) const;
	bool CheckRow(const int& rowNumber) const;
	bool CheckMainDiagonal(const int& rowNumber , const int& colNumber) const;
	bool CheckSecDiagonal(const int& rowNumber , const int& colNumber) const;
	char** GetBoard() const noexcept;
	~TicTacToe();

private:
	int m_rows, m_cols;
	char** m_board;
};