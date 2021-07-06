#pragma once
#include<iostream>

class Player
{
public:
	Player();
	Player(std::string name, char symbol);

	char GetSymbol() const noexcept;
	std::string GetName() const noexcept;
private:
	std::string m_name;
	char m_symbol;
};

