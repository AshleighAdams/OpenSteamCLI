#ifndef OPENSTEAMCLI_FRIENDCONTROL_H
#define OPENSTEAMCLI_FRIENDCONTROL_H

// OpenSteamClient
#include <OpenSteamClient/SteamClient.hpp>
#include <OpenSteamClient/SteamUser.hpp>
#include <OpenSteamClient/SteamFriends.hpp>

// Consor
#include <Consor/Control.hpp>
#include <Consor/Controls/Label.hpp>
#include <Consor/Util/Hooks.hpp>

class FriendControl : public Consor::Label
{
	Sc::SteamFriends*    _pFriends;
	Sc::SteamId          _Whom;
	const Sc::Persona*   _pPersona;
public:
	FriendControl(Sc::SteamFriends& friends, Sc::SteamId& steamid);
	void Update();
	Consor::Hook<Sc::SteamId> Click;
	
	virtual bool HandleInput(Consor::Input::Key Key, Consor::Input::IInputSystem& System);
	virtual bool CanFocus();
};

#endif //OPENSTEAMCLI_FRIENDCONTROL_H
