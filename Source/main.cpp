// STL
#include <iostream>

// OpenSteamClient
#include <OpenSteamClient/SteamClient.hpp>
#include <OpenSteamClient/SteamUser.hpp>
#include <OpenSteamClient/SteamFriends.hpp>

// Consor
#include <Consor/PlatformConsoleRenderer.hpp>
#include <Consor/PlatformInputSystem.hpp>

#include <Consor/Util/Prompts.hpp>
#include <Consor/Util/Time.hpp>
#include <Consor/WindowSystem.hpp>
#include <Consor/Controls/ProgressBar.hpp>
#include <Consor/Containers/ScrollContainer.hpp>

// OpenSteamCLI
#include "LoginForm.hpp"

using namespace std;
using namespace Consor;
using namespace Consor::Input;
using namespace Consor::Console;

namespace LogRelated
{
	void LoadLogger();
	void UnloadLogger();
};


int main(int argc, char** argv)
{
	Input::PlatformInputSystem input;
	PlatformConsoleRenderer renderer;

	renderer.SetTitle("Open Steam CLI");
	
	WindowSystem::Setup(&renderer, &input); // so it doesn't crash upon Ctrl-C
	atexit([]()
	{
		WindowSystem::Close();
	});
	
	LogRelated::LoadLogger();
	
	while(true)
	{
		LoginForm loginform;
		
		if(loginform.Show() == FormResult::Cancel)
			break;
	}
	
	LogRelated::UnloadLogger();
	return 0;
}



namespace LogRelated
{
	FlowContainer _Flow(FlowContainer::FlowAxis::Vertical, 0);

	ScrollContainer _Scroll(_Flow, Size(-1, 16));
	WindowContainer _Window(_Scroll, "Debug Log");

	std::list<Control*> _ToDelete;
	mutex _Lock;

	void OnLog(const string& msg)
	{
		lock_guard<mutex> lock(_Lock); // safe for multithreading

		Label& msglbl = *new Label;
		_ToDelete.push_back(&msglbl);

		msglbl.SetText(msg);
		msglbl.ForceResize(Size(60, 1));

		_Flow.AddControl(msglbl);

		static bool HasScrolled = false;
		if(!HasScrolled && _Scroll.ScrollDown(9999))
			HasScrolled = true;

		if(_ToDelete.size() > 100)
		{
			delete _ToDelete.front();
			_ToDelete.pop_front();
		}
	}

	void Toggle()
	{
		static bool visible = false;

		if(!visible)
			WindowSystem::RegisterWindow(_Window, Vector(0, -1));
		else
			WindowSystem::UnregisterWindow(_Window);;

		visible = !visible;
	}

	void LoadLogger()
	{
		WindowSystem::RegisterHotKey(nullptr, Input::F2, false, false, Toggle);
		Util::HookLog(OnLog);
	}

	void UnloadLogger()
	{
		WindowSystem::UnregisterWindow(_Window);
		for(Control* pControl : _ToDelete)
			delete pControl;
	}
}


int main_test()
{
	Sc::SteamClient client;
	Sc::SteamUser user(client);
	Sc::SteamFriends friends(client);

	client.OnConnect->Add([&](Sc::ConnectEvent ev)
	{
		if(ev.result == Sc::EResult_OK)
		{
			cout << "connected\n";
			
			Sc::LoginDetails details;
			
			cout << "u/n: ";
			cin >> details.username;
			cout << "p/w: ";
			cin >> details.password;
			
			cout << "logging in...\n";
			user.LogIn(details);
		}
		else
		{
			
		}
	});

	client.OnDisconnect->Add([&](Sc::DisconnectEvent ev)
	{
		cout << "disconnected\n";
		// Disconnected.
	});

	user.OnLoggedIn->Add([&](Sc::LoggedInEvent ev)
	{
		if(ev.result == Sc::EResult_OK)
		{
			cout << "logged in\n";
			friends.SetPersonaState(Sc::EPersonaState_Online);
		}
		else
		{
			cout << "couldn't log in\n";
		}
	});

	// Start connecting.
	cout << "connecting...\n";
	client.Connect();

	while(client.IsConnected())
	{
		// -1 is the timeout in ms for waiting for packets.
		// -1 means infinite.
		client.Run(-1);
	}

	return 0;
}
