#ifndef MENUITEM_H
#define MENUITEM_H
#include "animentity.h"
#include <string>
using namespace std;

class MenuItem : public AnimEntity
{
public:
	MenuItem();
	~MenuItem();
	void setName(string name);
	void setActiveStatus(bool active);
	
	string getName();
	bool getActiveStatus();

	// class members
public:
	string m_name;
	bool m_active;
};
#endif //__MENUITEM_H__