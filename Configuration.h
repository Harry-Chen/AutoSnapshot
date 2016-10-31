#pragma once
#include "stdafx.h"

class Configuration {
public:
	Configuration();

	~Configuration();

	bool parseFromFile(const char* filePath);
	void writeIntoFile(const char* filePath) const;

	void setValues(bool _timer_enabled, UINT _timer_interval, bool _hotkey_enabled, UINT _hotkey_modifiers, UINT _hotkey_code, bool _encryption_enabled, std::string _random_directory);

	bool isTimerEnabled() const;
	UINT getTimerInterval() const;
	bool isHotKeyEnabled() const;
	UINT getHotKeyModifiers() const;
	UINT getHotKeyCode() const;
	bool isEncryptionEnabled() const;
	std::string getRandomDirectory() const;

private:
	Json::Value *root;
	Json::Value *temp;
	bool timer_enabled;
	UINT timer_interval;
	bool hotkey_enabled;
	UINT hotkey_modifiers;
	UINT hotkey_code;
	bool encryption_enabled;
	std::string random_directory;

};