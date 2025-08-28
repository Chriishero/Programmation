#include "Shape.h"

// Shape class implementation
Shape::Shape()
{
}

void Shape::setType(Type type)
{
	m_type = type;
}

Shape::Type Shape::getType() const
{
	return m_type;
}
