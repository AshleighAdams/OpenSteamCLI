#ifndef OPENSTEAMCLI_CHATFORM_H
#define OPENSTEAMCLI_CHATFORM_H

// Consor
#include <Consor/Containers/AlignContainer.hpp>
#include <Consor/Containers/FlowContainer.hpp>
#include <Consor/Containers/ScrollContainer.hpp>
#include <Consor/Controls/Label.hpp>
#include <Consor/Controls/TextBox.hpp>
#include <Consor/Util/Hooks.hpp>

//OpenSteamClient
#include <OpenSteamClient/SteamClient.hpp>
#include <OpenSteamClient/SteamUser.hpp>
#include <OpenSteamClient/SteamFriends.hpp>

// STL
#include <list>
#include <string>
#include <unordered_map>

#include "Form.hpp"

// Small helper control
class TextMessage : public Consor::TextBox
{
public:
	TextMessage(){}
	virtual bool HandleInput(Consor::Input::Key Key, Consor::Input::IInputSystem& System)
	{
		if(Key == Consor::Input::Key::Enter)
		{
			this->Enter(this->GetText());
			this->SetText("");
			return true;
		}
		
		return Consor::TextBox::HandleInput(Key, System);
	}
	Consor::Hook<const std::string&> Enter;
};

class ChatForm : public Form
{
	std::list<Consor::Label*>  _Messages;
	
	Consor::FlowContainer      _MainFlow, _MessageFlow;
	Consor::ScrollContainer    _MessageScroll;
	TextMessage                _Message;
	
	Sc::SteamId                _ID;
	Sc::SteamFriends*          _pFriends;
	const Sc::Persona*         _pPersona;
	
	ChatForm(Sc::SteamId steamid, Sc::SteamFriends& friends);
	~ChatForm();
	
	void _InsertMessage(const std::string& message);
	void _Message_Enter(const std::string& message);
public:
	void Toggle();
	
// static
public:
	static ChatForm& FromSteamId(Sc::SteamId steamid, Sc::SteamFriends& friends);
	static void FreeAllChats();
};

#endif //OPENSTEAMCLI_CHATFORM_H
