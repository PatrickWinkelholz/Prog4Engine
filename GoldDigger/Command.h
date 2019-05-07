#pragma once
#include "Locator.h"
#include <iostream>
#include <deque>

class Command
{
public:
	virtual void execute() = 0; //pure virtual function = abstract class
	virtual ~Command() = default;
};

class Fire : public Command
{
public:
	void execute() override { Locator::getAudio().playSound(L"fire.wav"); };
	~Fire() {};
};

class Duck : public Command
{
public:
	void execute() override { Locator::getAudio().playSound(L"duck.wav"); };
	~Duck() {};
};

class Jump : public Command
{
public:
	void execute() override { Locator::getAudio().playSound(L"jump.wav"); };
	~Jump() {};
};

class Fart : public Command
{
public:
	void execute() override { Locator::getAudio().playSound(L"fart.wav"); };
	~Fart() {};
};

class SwitchAudio : public Command //used to cycle between audio services. can store any number of services and cycles between them
{
public:
	SwitchAudio(std::deque<Audio*>* services) { 
		m_Services = services; 
		execute();
	}

	void execute() override 
	{
		Locator::provide(m_Services->front());
		m_Services->push_back(m_Services->front());
		m_Services->pop_front();
		std::cout << "Audio switched!\n";
	};

	~SwitchAudio() {};

private:
	std::deque<Audio*>* m_Services;
};

class Quit : public Command
{
public:
	Quit(bool& quit) { m_Quit = &quit; };
	void execute() override { *m_Quit = true; };
	~Quit() {};

private:
	bool* m_Quit;
};

class TestCommand : public Command
{
public: 
	int testNumber{};
	void execute() override { testNumber++; };
	~TestCommand() {};
};

