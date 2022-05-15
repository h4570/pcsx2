#pragma once

#include <pcsx2/VU.h>

static const char VU1_DUMPER_TOGGLE_KEY = 'L';
static const char* VU1_DUMPER_LOGS_DIRECTORY = "C:/Users/hasto/Documents/repositories/misc/vu_logs/";

class VU1Dumper
{
public:
	static void Dump();

private:
	static void FillStream(std::ostringstream& os);

	inline static bool m_directory_clean_trigger = false;
	inline static int m_logs_counter = 1;
};