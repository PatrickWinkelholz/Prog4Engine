#include "GoldDiggerPCH.h"
#include "Audio.h"
#include <windows.h>
#include <mmsystem.h>
#include <iostream>

void ConsoleAudio::playSound(std::wstring&& file)
{
	PlaySound(file.c_str(), 0, SND_FILENAME | SND_ASYNC);
}

void ConsoleAudio::stopSound(std::wstring&&file)
{
	(file); //unreference parameter
	PlaySound(0, 0, 0);
}

void ConsoleAudio::stopAllSounds()
{
	PlaySound(0, 0, 0);
}

void LoggedAudio::playSound(std::wstring&&file)
{
	std::wcout << L"playing sound: " << file << '\n' ;
}

void LoggedAudio::stopSound(std::wstring&&file)
{
	std::wcout << L"stopping sound: " << file << '\n';
}

void LoggedAudio::stopAllSounds()
{
	std::wcout << L"stopping all sounds\n";
}
