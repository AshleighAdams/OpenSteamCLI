
#include "FriendsForm.hpp"
#include <Consor/Util/Debug.hpp>
#include <Consor/Util/Prompts.hpp>

using namespace std;
using namespace Consor;

FriendsForm::FriendsForm(const string& username, const string& password)
	: Form(_MainScroll, "Friends"),
	_MainFlow(FlowContainer::FlowAxis::Vertical, 0),
	_MainScroll(_MainFlow, Size(-1, 20))
{
	// layout
	_MainFlow.AddControl(_LogoutButton);
	_MainFlow.AddControl(_StatusLabel);
	
	// properties
	_LogoutButton.SetText("Logout");
	_StatusLabel.SetText("Idle");
	
	//events
	_LogoutButton.Click += std::bind(&FriendsForm::_LogoutButton_Click, this);
	
	_Username = username;
	_Password = password;
}

void FriendsForm::_UpdateStatus(const string& status)
{
	_StatusLabel.SetText(status);
	Util::Log("setting status to `%'", status);
}

bool FriendsForm::_Login()
{
	this->_UpdateStatus("connecting...");
	
	Util::Log("attempting to login as `%'", this->_Username);
	
	Util::MessageBox("This hasn't been implimented yet!", "Not Implimented", {"OK"});
	
	return false;
}

void FriendsForm::Run()
{
	if(!this->_Login())
		return;
	
	while(true)
	{
		if(_Closed)
			break;
		
	}
}

FriendsForm::~FriendsForm()
{
	for(Control* pControl : this->_Controls)
		delete pControl;
}

void FriendsForm::_LogoutButton_Click()
{
	struct NotImplimented {} _;
	throw _;
}
