#pragma once
#include<iostream>

class Player
{
public:
	Player()
	{
		m_name = "-NoName";
		m_symbol = '#';
	};
	Player(std::string name, char symbol) : m_name(name), m_symbol(symbol)
	{};
	char GetSymbol() const noexcept;
	std::string GetName() const noexcept;
private:
	std::string m_name;
	char m_symbol;
};

