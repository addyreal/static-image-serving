#pragma once
#include "utils.h"
#include <vector>
#include <fstream>
#include <yaml-cpp/yaml.h>
#include <yaml-cpp/node/node.h>
#include <yaml-cpp/node/type.h>



void GenerateDefaultConfig();
class Config
{
	public:
		Config() = delete;
		Config(const std::string& rel_path);
		~Config() = default;
	public:
		std::vector<std::string> extensions;
		std::vector<unsigned int> sizes;
		unsigned int quality;
};