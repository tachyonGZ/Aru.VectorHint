#include "extension.h"

CVectorHintExtension g_vector_hint_ext;

SMEXT_LINK(&g_vector_hint_ext);

inline HintInfo MakeHintInfo(const cell_t *params)
{
	return HintInfo{.x_index = static_cast<std::int32_t>(params[1]), .y_index = static_cast<std::int32_t>(params[2])};
}

cell_t AddHint(IPluginContext* p_context, const cell_t* params)
{
	return g_vector_hint_ext.AddHint(MakeHintInfo(params));
}

cell_t HideHint(IPluginContext* p_context, const cell_t* params)
{
	return g_vector_hint_ext.HideHint(MakeHintInfo(params), params[3]);
}

cell_t SetHint(IPluginContext* p_context, const cell_t* params)
{
	char *text;
	p_context->LocalToString(params[4], &text);
	return g_vector_hint_ext.SetHint(MakeHintInfo(params), params[3], std::string(text));
}

cell_t PrintHint(IPluginContext* p_context, const cell_t* params)
{
	return g_vector_hint_ext.PrintHint(params[1]);
}

const sp_nativeinfo_t my_natives[] = {
	{"VectorHint_AddHint", AddHint},
	{"VectorHint_HideHint", HideHint},
	{"VectorHint_SetHint", SetHint},
	{"VectorHint_PrintHint", PrintHint},
	{nullptr, nullptr}
};

CVectorHintExtension::CVectorHintExtension() :
	p_map_vector_hint_(std::make_unique<std::map<int, CVectorHint>>())
{
	for (int client = 0; client < SM_MAXPLAYERS + 1; client++)
	{
		p_map_vector_hint_->emplace(client, CVectorHint());
	}
}

bool CVectorHintExtension::AddHint(const HintInfo &info) const
{
	for (std::pair<const int, CVectorHint> &p : (*p_map_vector_hint_))
	{
		if (!p.second.AddHint(info))
		{
			return false;
		}
	}

	return true;
}

bool CVectorHintExtension::HideHint(const HintInfo& info, int client) const
{
	return (*p_map_vector_hint_)[client].HideHint(info);
}


bool CVectorHintExtension::SetHint(const HintInfo &info, int client, std::string &&text)
{
	return (*p_map_vector_hint_)[client].SetHint(info, std::forward<std::string &&>(text));
}

bool CVectorHintExtension::PrintHint(int client)
{
	//hint_context_stream.clear();

	(*p_map_vector_hint_)[client].PrintHint(client, hint_context);

	return gamehelpers->HintTextMsg(client, hint_context.c_str());
}

void CVectorHintExtension::SDK_OnAllLoaded()
{
	sharesys->AddNatives(myself, my_natives);
}