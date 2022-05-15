#include "VU1dumper.h"
#include <sstream>
#include <string>
#include <iostream>
#include <filesystem>

void VU1Dumper::Dump()
{
	if (GetKeyState(VU1_DUMPER_TOGGLE_KEY) & 0x8000)
	{
		if (!m_directory_clean_trigger)
		{
			for (const auto& entry : std::filesystem::directory_iterator(VU1_DUMPER_LOGS_DIRECTORY))
				std::filesystem::remove_all(entry.path());
			m_logs_counter = 1;
			m_directory_clean_trigger = true;
		}

		std::ostringstream os;
		FillStream(os);
		const auto jsonAsString = os.str();
		auto jsonAsChars = jsonAsString.c_str();
		std::stringstream filepath;
		filepath << VU1_DUMPER_LOGS_DIRECTORY;
		filepath << m_logs_counter++;
		filepath << ".json";
		const auto filepathAsString = filepath.str();
		auto filepathAsChars = filepathAsString.c_str();

		FILE* pFile = fopen(filepathAsChars, "w");
		fwrite(jsonAsChars, sizeof(char), strlen(jsonAsChars), pFile);
		fclose(pFile);
	}
	else
	{
		m_directory_clean_trigger = false;
	}
}

void VU1Dumper::FillStream(std::ostringstream& os)
{
	os << "{";
	{
		os << "\"vi\":{";
		{
			os << "\"F\":[";
			{
				for (size_t i = 0; i < 32; i++)
				{
					os << "{";
					os << "\"index\":" << i << ",";
					os << "\"value\":" << VU1.VI[i].F;
					os << "}";
					if (i != 31)
						os << ",";
				}
			}
			os << "]";
		}
		os << "},";

		os << "\"vf\":{";
		{
			os << "\"f\":[";
			{
				for (size_t i = 0; i < 32; i++)
				{
					os << "{";
					os << "\"index\":" << i << ",";
					os << "\"x\":" << VU1.VF[i].f.x << ",";
					os << "\"y\":" << VU1.VF[i].f.y << ",";
					os << "\"z\":" << VU1.VF[i].f.z << ",";
					os << "\"w\":" << VU1.VF[i].f.w << "";
					os << "}";
					if (i != 31)
						os << ",";
				}
			}
			os << "],";
			os << "\"i\":[";
			{
				for (size_t i = 0; i < 32; i++)
				{
					os << "{";
					os << "\"index\":" << i << ",";
					os << "\"x\":" << VU1.VF[i].i.x << ",";
					os << "\"y\":" << VU1.VF[i].i.y << ",";
					os << "\"z\":" << VU1.VF[i].i.z << ",";
					os << "\"w\":" << VU1.VF[i].i.w << "";
					os << "}";
					if (i != 31)
						os << ",";
				}
			}
			os << "]";
		}
		os << "},";

		os << "\"q\":{";
		{
			os << "\"F\": " << VU1.q.F;
		}
		os << "},";

		os << "\"p\":{";
		{
			os << "\"F\": " << VU1.p.F;
		}
		os << "},";

		os << "\"acc\":{";
		{
			os << "\"f\":{";
			{

				os << "\"x\":" << VU1.ACC.f.x << ",";
				os << "\"y\":" << VU1.ACC.f.y << ",";
				os << "\"z\":" << VU1.ACC.f.z << ",";
				os << "\"w\":" << VU1.ACC.f.w << "";
			}
			os << "},";

			os << "\"i\":{";
			{
				os << "\"x\":" << VU1.ACC.i.x << ",";
				os << "\"y\":" << VU1.ACC.i.y << ",";
				os << "\"z\":" << VU1.ACC.i.z << ",";
				os << "\"w\":" << VU1.ACC.i.w << "";
			}
			os << "}";
		}
		os << "}";
	}
	os << "}";
}