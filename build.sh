#!/bin/bash

g++ --std=c++11 -Wfatal-errors ./Source/*.cpp -o ./Binaries/OpenSteamCLI -lOpenSteamClient -lprotobuf -lcrypto++ -lconsor -pthread

