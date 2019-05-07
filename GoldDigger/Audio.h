#pragma once
#include <string>

class Audio
{
public:
	virtual ~Audio() {}
	virtual void playSound(std::wstring&& file) = 0;
	virtual void stopSound(std::wstring&&file) = 0;
	virtual void stopAllSounds() = 0;
};

class ConsoleAudio : public Audio
{
public:

	virtual void playSound(std::wstring&&file) override;
	virtual void stopSound(std::wstring&&file) override;
	virtual void stopAllSounds() override;
};

class LoggedAudio : public Audio
{
public:
	virtual void playSound(std::wstring&&file) override;
	virtual void stopSound(std::wstring&&file) override;
	virtual void stopAllSounds() override;
};

class NullAudio : public Audio
{
public:
	virtual void playSound(std::wstring&&file) override { (file); /* Do nothing. */ }
	virtual void stopSound(std::wstring&&file) override { (file); /* Do nothing. */ }
	virtual void stopAllSounds() override{ /* Do nothing. */ }
};