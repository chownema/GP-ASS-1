#include "MenuItem.h"

MenuItem::MenuItem()
{
	m_active = false;
}

MenuItem::~MenuItem()
{

}

void
MenuItem::setName(string name) 
{
	m_name = name;
}

void
MenuItem::setActiveStatus(bool active)
{
	m_active = active;
}

string
MenuItem::getName()
{
	return (m_name);
}

bool
MenuItem::getActiveStatus()
{
	return (m_active);
}