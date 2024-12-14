#pragma once

#include <algorithm>
#include <cstdint>
#include <ostream>
#include <string>
#include <vector>
#include <memory>

struct HintInfo
{
	std::int32_t x_index, y_index;
};

bool operator==(const HintInfo& i1, const HintInfo& i2);

class Hint
{
public:
	Hint(const HintInfo &info) :
		info (info),
		is_visible(false)
	{
		;
	}
public:
	HintInfo info;
	bool is_visible;
	std::string text;
};

class CVectorHint : public std::vector<Hint>
{
public:
	bool AddHint(const HintInfo &info);

	bool HideHint(const HintInfo& info);

	bool SetHint(const HintInfo &info, std::string &&text);

	//void PrintHint(int client, std::basic_ostream<char> &output_stream)
	void PrintHint(int client, std::string &text);
};