#pragma once
#include <string>
#include <cstring>
#include <fstream>
#include <iostream>
#include <filesystem>



namespace Utils
{
	namespace CLI
	{
		bool input_is_help(const char*);
	}
	namespace Config
	{
		void GenerateDefaultConfig();
	}
	namespace Files
	{
		const std::string get_root_dir();
		const std::string get_proper_path(const std::string& rel_path);
		bool file_exists(const char* rel_path);
		bool file_has_extension(const char*, const char*);
		std::string strip_extension(const std::string&);
	}
	namespace Assert
	{
		void exit_if(bool);
		void exit_if(bool, const char*);
	}
}