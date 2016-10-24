#include "stdafx.h"
#include "Configuration.h"

const char* TIMER_ENABLED = "timer_enabled";
const char* TIMER_INTERVAL = "timer_interval";
const char* HOTKEY_ENABLED = "hotkey_enabled";
const char* HOTKEY_MODIFIERS = "hotkey_modifiers";
const char* HOTKEY_CODE = "hotkey_code";

const char *KEYS[] = { TIMER_ENABLED, TIMER_INTERVAL, HOTKEY_ENABLED, HOTKEY_MODIFIERS, HOTKEY_CODE };

Configuration::Configuration() {
	root = new Json::Value();
}

Configuration::~Configuration() {
	delete root;
}

bool Configuration::parseFromFile(const char * filePath) {
	Json::Reader reader;
	std::ifstream is(filePath, std::ios::binary);
	if (reader.parse(is, *root)) {
		for (const char* key : KEYS) {
			if ((*root)[key].isNull()) return false;
		}
		timer_enabled = root->get(TIMER_ENABLED, false).asBool();
		timer_interval = root->get(TIMER_INTERVAL, 5000L).asUInt();
		hotkey_enabled = root->get(HOTKEY_ENABLED, false).asBool();
		hotkey_modifiers = root->get(HOTKEY_MODIFIERS, MOD_ALT | MOD_SHIFT).asInt();
		hotkey_code = root->get(HOTKEY_CODE, 'X').asInt();
		return true;
	}
	else return false;
}

void Configuration::writeIntoFile(const char * filePath) {
	std::ofstream out(filePath, std::ios::binary);
	Json::StyledStreamWriter writer;
	writer.write(out, *root);
	out.close();
}

void Configuration::setValues(bool _timer_enabled, UINT _timer_interval, bool _hotkey_enabled, UINT _hotkey_hotkey_modifiers, UINT _hotkey_code){
	timer_enabled = _timer_enabled;
	timer_interval = _timer_interval;
	hotkey_enabled = _hotkey_enabled;
	hotkey_modifiers = _hotkey_hotkey_modifiers;
	hotkey_code = _hotkey_code;
}

bool Configuration::isTimerEnabled()
{
	return timer_enabled;
}

UINT Configuration::getTimerInterval()
{
	return timer_interval;
}

bool Configuration::isHotKeyEnabled()
{
	return hotkey_enabled;
}

UINT Configuration::getHotKeyModifiers()
{
	return hotkey_modifiers;
}

UINT Configuration::getHotKeyCode()
{
	return hotkey_code;
}
