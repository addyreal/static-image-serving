#pragma once
#include <string>
#include <cstring>
#include <iostream>
#include <filesystem>



namespace Utils
{
	namespace Files
	{
		const std::string get_project_dir();
		const std::string locate_file(const std::string& rel_path);
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