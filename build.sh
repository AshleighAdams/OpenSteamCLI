#!/bin/bash

g++ --std=c++11 ./Source/*.cpp -o OpenSteamCLI -lOpenSteamClient -lprotobuf -lcrypto++ -lconsor -pthread

