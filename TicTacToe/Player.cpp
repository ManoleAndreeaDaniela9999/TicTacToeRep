#include "Player.h"

char Player::GetSymbol() const noexcept
{
	return m_symbol;
}

std::string Player::GetName() const noexcept
{
	return m_name;
}
