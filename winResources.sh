#!/bin/bash
cp -r Resources Platforms/Windows/Chameleon

cp -r Resources Platforms/Windows/Debug
cp -r External\ Libraries/Windows/SFML-2.5.1/bin/openal32.dll Platforms/Windows/Debug
cp -r External\ Libraries/Windows/SFML-2.5.1/bin/sfml-audio-d-2.dll Platforms/Windows/Debug
cp -r External\ Libraries/Windows/SFML-2.5.1/bin/sfml-graphics-d-2.dll Platforms/Windows/Debug
cp -r External\ Libraries/Windows/SFML-2.5.1/bin/sfml-network-d-2.dll Platforms/Windows/Debug
cp -r External\ Libraries/Windows/SFML-2.5.1/bin/sfml-system-d-2.dll Platforms/Windows/Debug
cp -r External\ Libraries/Windows/SFML-2.5.1/bin/sfml-window-d-2.dll Platforms/Windows/Debug

cp -r Resources Platforms/Windows/Release
cp -r External\ Libraries/Windows/SFML-2.5.1/bin/openal32.dll Platforms/Windows/Release
cp -r External\ Libraries/Windows/SFML-2.5.1/bin/sfml-audio-2.dll Platforms/Windows/Release
cp -r External\ Libraries/Windows/SFML-2.5.1/bin/sfml-graphics-2.dll Platforms/Windows/Release
cp -r External\ Libraries/Windows/SFML-2.5.1/bin/sfml-network-2.dll Platforms/Windows/Release
cp -r External\ Libraries/Windows/SFML-2.5.1/bin/sfml-system-2.dll Platforms/Windows/Release
cp -r External\ Libraries/Windows/SFML-2.5.1/bin/sfml-window-2.dll Platforms/Windows/Release
