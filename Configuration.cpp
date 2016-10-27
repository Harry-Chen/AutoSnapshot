#include "stdafx.h"
#include "Configuration.h"

const char* TIMER_ENABLED = "timer_enabled";
const char* TIMER_INTERVAL = "timer_interval";
const char* HOTKEY_ENABLED = "hotkey_enabled";
const char* HOTKEY_MODIFIERS = "hotkey_modifiers";
const char* HOTKEY_CODE = "hotkey_code";
const char* ENCRYPTION_ENABLED = "encryption_enabled";
const char* RANDOM_DIRECTORY = "random_directory";

const char *KEYS[] = { TIMER_ENABLED, TIMER_INTERVAL, HOTKEY_ENABLED, HOTKEY_MODIFIERS, HOTKEY_CODE, ENCRYPTION_ENABLED, RANDOM_DIRECTORY };

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
		encryption_enabled = root->get(ENCRYPTION_ENABLED, false).asBool();
		random_directory = root->get(RANDOM_DIRECTORY, std::string("")).asString();
		return true;
	}
	else return false;
}

void Configuration::writeIntoFile(const char * filePath) {
	std::ofstream out(filePath, std::ios::binary);
	Json::StyledStreamWriter writer;
	writer.write(out, *temp);
	out.close();
	delete temp;
}

void Configuration::setValues(bool _timer_enabled, UINT _timer_interval, bool _hotkey_enabled, UINT _hotkey_hotkey_modifiers, UINT _hotkey_code, bool _encryption_enabled, std::string _random_directory){
	temp = new Json::Value();
	(*temp)[TIMER_ENABLED] = _timer_enabled;
	(*temp)[TIMER_INTERVAL] = _timer_interval;
	(*temp)[HOTKEY_ENABLED] = _hotkey_enabled;
	(*temp)[HOTKEY_MODIFIERS] = _hotkey_hotkey_modifiers;
	(*temp)[HOTKEY_CODE] = _hotkey_code;
	(*temp)[ENCRYPTION_ENABLED] = _encryption_enabled;
	(*temp)[RANDOM_DIRECTORY] = _random_directory;
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

bool Configuration::isEncryptionEnabled() {
	return encryption_enabled;
}

std::string Configuration::getRandomDirectory() {
	return random_directory;
}