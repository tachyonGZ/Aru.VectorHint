#include "VectorHint.h"

bool operator==(const HintInfo& i1, const HintInfo& i2)
{
	return i1.x_index == i2.x_index && i1.y_index == i2.y_index;
}

bool CVectorHint::AddHint(const HintInfo& info)
{
	auto citer = std::find_if(
		cbegin(),
		cend(),
		[info](const Hint& hint) {
			return hint.info == info;
		}
	);

	if (cend() != citer)
	{
		return false;
	}

	auto iter = std::lower_bound(
		begin(),
		end(),
		info,
		[](const Hint& hint, const HintInfo& info) {
			if (info.x_index != hint.info.x_index)
			{
				return hint.info.x_index < info.x_index;
			}

			return hint.info.y_index < info.y_index;
		}
	);

	std::insert_iterator insert_it(*this, iter);

	insert_it = info;
	return true;
}

bool CVectorHint::HideHint(const HintInfo& info)
{
	auto iter = std::find_if(
		begin(),
		end(),
		[info](const Hint& hint) {
			return hint.info == info;
		}
	);

	if (cend() == iter)
	{
		return false;
	}

	iter->is_visible = false;
	return true;
}

bool CVectorHint::SetHint(const HintInfo& info, std::string&& text)
{
	auto iter = std::find_if(
		begin(),
		end(),
		[info](const Hint& hint) {
			return hint.info == info;
		}
	);

	if (cend() == iter)
	{
		return false;
	}

	iter->is_visible = true;
	iter->text = text;
	return true;
}

void CVectorHint::PrintHint(int client, std::string& text)
{
	text.clear();

	std::int32_t last_x_index = 0;
	size_t cnt = size();

	for (const Hint& hint : *this)
	{
		if (!hint.is_visible)
		{
			continue;
		}

		if (cnt-- != size())
		{
			// not first hint
			if (hint.info.x_index != last_x_index)
			{
				text += '\n';
			}
			else
			{
				text += " | ";
			}
		}

		// first hint
		last_x_index = hint.info.x_index;

		text += hint.text;
	}
}