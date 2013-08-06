
#include "ChatForm.hpp"

#include <Consor/Util/StringUtils.hpp>

using namespace Consor;
using namespace std;

ChatForm::ChatForm(Sc::SteamId steamid, Sc::SteamFriends& friends) :
	Form(_MainFlow, friends.GetPersonaInfo(steamid).name),
	_MainFlow(FlowContainer::FlowAxis::Vertical, 0),
	_MessageFlow(FlowContainer::FlowAxis::Vertical, 0),
	_MessageScroll(_MessageFlow, Size(40, 20))
{
	// vars
	_ID         = steamid;
	_pFriends   = &friends;
	_pPersona   = &friends.GetPersonaInfo(steamid);
	
	// layout
	//_Message.ForceResize(Size(_MessageFlow.GetSize().Width, 1));
	
	_MainFlow.AddControl(_Message); // TODO: Put other way; ScrollContainer takes input wrong for some reason, the focus messes up...
	_MainFlow.AddControl(_MessageScroll);
	
	
	// events
	//_Message.Enter += std::bind(&ChatForm::_Message_Enter, this);
	_Message.Enter += [&](const string& str){this->_Message_Enter(str);};
	
	this->_InsertMessage("Do not give your password away!");
}

ChatForm::~ChatForm()
{
	for(Consor::Label* pLbl : _Messages)
		delete pLbl;
}

void ChatForm::_InsertMessage(const std::string& message)
{
	Label* ptr = new Label();
	ptr->SetText(message);
	
	this->_MessageFlow.AddControl(*ptr);
}

void ChatForm::Toggle()
{
	if(this->_Closed)
		this->Show();
	else
		this->Close();
}

void ChatForm::_Message_Enter(const string& message)
{
	string toinsert = Util::FormatString("%: %", _pFriends->GetPersonaName(), message);
	
	this->_InsertMessage(toinsert);
	_pFriends->SendFriendMessage(_ID, message);
}


// static
std::unordered_map<Sc::SteamId, ChatForm*> _Chats;

ChatForm& ChatForm::FromSteamId(Sc::SteamId steamid, Sc::SteamFriends& friends)
{
	ChatForm* ret = nullptr;
	auto it = _Chats.find(steamid);
	
	if(it == _Chats.end())
	{
		ret = new ChatForm(steamid, friends);
		_Chats[steamid] = ret;
	}
		
	return *ret;
}

void ChatForm::FreeAllChats()
{
	for(auto it : _Chats)
		delete it.second;
	
	_Chats.clear();
}
