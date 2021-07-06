#include "Player.h"

Player::Player()
{
	m_name = "-NoName";
	m_symbol = '#';
};

Player::Player(std::string name, char symbol)
	: m_name(name), m_symbol(symbol)
{
};

char Player::GetSymbol() const noexcept
{
	return m_symbol;
}

std::string Player::GetName() const noexcept
{
	return m_name;
}
