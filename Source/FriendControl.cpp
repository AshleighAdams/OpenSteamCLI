#include "FriendControl.hpp"

using namespace std;

FriendControl::FriendControl(Sc::SteamFriends& friends, Sc::SteamId& steamid)
{
	_pFriends = &friends;
	_Whom = steamid;
	_pPersona = &friends.GetPersonaInfo(steamid);
}

void FriendControl::Update()
{
	const string& name = _pPersona->name;
	bool offline = _pPersona->state == Sc::EPersonaState::EPersonaState_Offline;
	
	string show = offline ? "~" + name : name;
	this->SetText(show);
}

bool FriendControl::HandleInput(Consor::Input::Key Key, Consor::Input::IInputSystem& System)
{
	if(Key == Consor::Input::Key::Enter)
	{
		return true;
	}
	
	return false;
}

bool FriendControl::CanFocus()
{
	return true;
}

