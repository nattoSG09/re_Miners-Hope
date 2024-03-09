#pragma once
#include "json.hpp"
#include <string>
using std::string;
using json = nlohmann::json;

namespace JsonManager
{
	bool Load(string fileName, json& _data);

	bool Save(string fileName, json& _data);

};

