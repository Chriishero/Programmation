#pragma once
#include "main.hpp"

class Shape
{
	public:
		Shape();

		enum class Type
		{
			Circle, Lines
		};

		void setType(Type type);
		Type getType() const;

	private:
		Type m_type;
};

