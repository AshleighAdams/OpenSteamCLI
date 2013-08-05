#ifndef OPENSTEAMCLI_FRIENDSFORM_H
#define OPENSTEAMCLI_FRIENDSFORM_H

#include "Form.hpp"
#include "FriendControl.hpp"

// Consor
#include <Consor/Containers/FlowContainer.hpp>
#include <Consor/Containers/ScrollContainer.hpp>
#include <Consor/Controls/Button.hpp>
#include <Consor/Controls/Label.hpp>

// STL
#include <string>
#include <list>

class FriendsForm : public Form
{
	Consor::FlowContainer        _MainFlow;
	Consor::ScrollContainer      _MainScroll;
	Consor::Button               _LogoutButton;
	Consor::Label                _StatusLabel;
	
	std::list<FriendControl*>    _Controls;
	std::string                  _Username, _Password;
	
	void _LogoutButton_Click();
	void _UpdateStatus(const std::string& status);
public:
	FriendsForm(const std::string& username, const std::string& password);
	~FriendsForm();
	virtual void Run();
};

#endif //OPENSTEAMCLI_FRIENDSFORM_H
