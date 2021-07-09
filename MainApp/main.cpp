#include <iostream>
#include "TicTacToe.h"
void ShowBoard(std::shared_ptr<TicTacToeAPI::ITicTacToe> game)
{
	int rows = game->GetRows(), cols = game->GetColumns();

	for (int indexRow = 0; indexRow < rows; indexRow++)
	{
		for (int indexCol = 0; indexCol < cols; indexCol++)
		{
			std::cout<<game->GetCellAt(indexRow, indexCol);
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

	auto game = TicTacToeAPI::ITicTacToe::Produce( "Player 1 ","Player 2 ", n, m);
	game->SetStrategy(TicTacToeAPI::StrategyType::MEDIUM_PVCOMP);
	ShowBoard(game);
	do
	{
		system("cls");
		
		ShowBoard(game);

		TicTacToeAPI::EMoveResult result;
		do
		{
			int row, col;
			std::cout << "It is " << game->GetActivePlayerName() << " turn" << std::endl << "Pick a row: ";
			std::cin >> row;
			std::cout << "Pick a column: ";
			std::cin >> col;

			result = game->TakeTurn(row, col); //this is where  Strategy applies

			switch (result)
			{
			case TicTacToeAPI::EMoveResult::PositionOccupied: { std::cout << "Position occupied! "; break; }
			case TicTacToeAPI::EMoveResult::InvalidPosition: { std::cout << "Invalid position! Please choose a place on the board! " << std::endl; break; }
			}
		} while (result != TicTacToeAPI::EMoveResult::Success);

	} while (!game->FullBoard() && !game->WinCheck());
	std::cout << std::endl << std::endl;
	ShowBoard(game);
	std::cout << std::endl << std::endl;
	if (game->WinCheck())
		std::cout << std::endl << game->GetActivePlayerName() << " won the game!" << std::endl;
	else
		std::cout << "TIE" << std::endl;

	std::cout << std::endl << "Game ended! :)";
	
	return 0;
}