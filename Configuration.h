#pragma once
#include "stdafx.h"

class Configuration {
public:
	Configuration();

	~Configuration();

	bool parseFromFile(const char* filePath);
	void writeIntoFile(const char* filePath);

	void setValues(bool _timer_enabled, UINT _timer_interval, bool _hotkey_enabled, UINT _hotkey_modifiers, UINT _hotkey_code);

	bool isTimerEnabled();
	UINT getTimerInterval();
	bool isHotKeyEnabled();
	UINT getHotKeyModifiers();
	UINT getHotKeyCode();

private:
	Json::Value *root;
	bool timer_enabled;
	UINT timer_interval;
	bool hotkey_enabled;
	UINT hotkey_modifiers;
	UINT hotkey_code;


};