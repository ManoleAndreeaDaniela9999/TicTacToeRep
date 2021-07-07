#include <iostream>
#include "TicTacToe.h"
void ShowBoard(const TicTacToe& game)
{
	int rows = game.GetRows(), cols = game.GetColumns();

	for (int indexRow = 0; indexRow < rows; indexRow++)
	{
		for (int indexCol = 0; indexCol < cols; indexCol++)
		{
			std::cout<<game.GetCellAt(indexRow, indexCol);
		}
		std::cout << std::endl;
	}
}
int main()
{
	int n = 0, m = 0;
	std::cout << "Game start! " << std::endl << "Chose board size (rows,cols) " << std::endl << "number of rows: ";
	std::cin >> n;
	std::cout << "number of columns: ";
	std::cin >> m;
	if (m < 3 && n < 3) m = 3, n = 3;

	auto game = new TicTacToe("Player 1 ", 'x', "Player 2 ", '0', n, m);
	bool posIsCorrect  = false;
	
	ShowBoard(*game);
	while (!game->FullBoard())
	{
		int row = 0;
		int col = 0;
		system("cls");
		ShowBoard(*game);
		posIsCorrect = false;
		while (!posIsCorrect)
		{
			if (game->GetTurn() == 1) {
				std::cout << "It is " << game->GetPlayer1Name() << " turn" << std::endl << "Pick a row: ";
				std::cin >> row;
				std::cout << "Pick a column: ";
				std::cin >> col;
			}
			else
			{
				std::cout << "It is " << game->GetPlayer2Name() << " turn" << std::endl << "Pick a row: ";
				std::cin >> row;
				std::cout << "Pick a column: ";
				std::cin >> col;
			}
			posIsCorrect = game->VerifiyPosition(row, col);
			if (!posIsCorrect) std::cout << "Bad position!";
		}
		game->TakeTurn(row, col);
		if(game->WinCheck(row, col))
		{
			std::cout << std::endl << game->GetActivePlayerName() << " won the game!" << std::endl;
			break;
		}
		game->SwitchTurn();
	}
	std::cout << std::endl << "Game ended! :)";
	return 0;
}