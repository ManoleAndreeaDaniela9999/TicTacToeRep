#pragma once
#include <iostream>

class TicTacToe
{
public:
	TicTacToe(const int n,const int m);

	void CellFill(const int& line, const int& column, const char& x) const;
	bool CheckColumn(const int& colNumber) const;
	bool CheckRow(const int& rowNumber) const;
	bool CheckDiagonals(const int& rownumber , const int& colNumber) const;

private:
	int m_rows, m_cols;
	char** m_board;
};