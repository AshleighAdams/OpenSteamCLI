
#include "FriendsForm.hpp"

// Consor
#include <Consor/Util/Debug.hpp>
#include <Consor/Util/Prompts.hpp>

// OpenSteamClient
#include <OpenSteamClient/SteamClient.hpp>
#include <OpenSteamClient/SteamUser.hpp>
#include <OpenSteamClient/SteamFriends.hpp>

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
}

void FriendsForm::Run()
{
	Sc::SteamClient client;
	Sc::SteamUser user(client);
	Sc::SteamFriends friends(client);
		
	client.OnConnect->Add([&](Sc::ConnectEvent ev)
	{
		if(ev.result == Sc::EResult_OK)
		{
			Util::Log("connected; logging in...");
			this->_UpdateStatus("logging in");
			
			Sc::LoginDetails details;
			
			details.username = this->_Username;
			details.password = this->_Password;
			
			user.LogIn(details);
			return;
		}
		
		if(Util::MessageBox("Failed to connect to Steam's servers!", "Error", {"Cancel", "Retry"}) == "Cancel")
			this->Close();
		else
			client.Connect();
	});
	
	client.OnDisconnect->Add([&](Sc::DisconnectEvent ev)
	{
		Util::Log("disconnected");
		this->Close();
	});
	
	user.OnLoggedIn->Add([&](Sc::LoggedInEvent ev)
	{
		if(ev.result == Sc::EResult_OK)
		{
			Util::Log("successfully logged in");
			this->_UpdateStatus("Online");
			friends.SetPersonaState(Sc::EPersonaState_Online);
			
			int fnds = friends.GetFriendCount();
			Util::Log("has % friends", fnds);
			
			for(int i = 0; i < fnds; i++)
			{
				Sc::SteamId sid = friends.GetFriendSteamId(i);
				const Sc::Persona& frnd = friends.GetPersonaInfo(sid);
				
				FriendControl* pControl = new FriendControl(friends, sid);
				
				_Controls.push_back(pControl);
				_MainFlow.AddControl(*pControl);
			}
		}
		else
		{
			Util::Log("couldn't log in: password incorrect");
			Util::MessageBox("Password incorrect, or Steam Guard!", "Can't login", {"OK"});
			this->Close();
		}
	});
	
	friends.OnPersonaUpdate->Add([&](Sc::PersonaUpdateEvent ev)
	{
		for(FriendControl* pControl : _Controls)
			pControl->Update();
	});
	
	Util::Log("attempting to login as `%'", this->_Username);
	this->_UpdateStatus("connecting");
	
	client.Connect();
	
	while(client.IsConnected())
	{
		if(this->_Closed)
			break;
		
		client.Run(5000);
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
