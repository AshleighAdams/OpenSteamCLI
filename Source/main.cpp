// STL
#include <iostream>

// OpenSteamClient
#include <OpenSteamClient/SteamClient.hpp>
#include <OpenSteamClient/SteamUser.hpp>
#include <OpenSteamClient/SteamFriends.hpp>

using namespace std;

int main()
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
