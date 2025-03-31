#include "utils.h"



#ifdef PROJECT_SOURCE_DIR
const std::string Utils::Files::get_project_dir()
{
	return std::string(PROJECT_SOURCE_DIR);
}
#else
const std::string Utils::Files::get_project_dir()
{
	std::cout << "Error, missing macro from CMake." << std::endl;
	exit(1);
}
#endif



const std::string Utils::Files::locate_file(const std::string& rel_path)
{
	return get_project_dir() + "/" + rel_path;
}



bool Utils::Files::file_exists(const char * rel_path)
{
	return std::filesystem::exists(locate_file(rel_path));
}



bool Utils::Files::file_has_extension(const char* filename, const char* ext)
{
	const char* dot = std::strrchr(filename, '.');
	return dot && std::strcmp(dot, ext) == 0;
}



std::string Utils::Files::strip_extension(const std::string& filename)
{
	size_t dot_pos = filename.find_last_of('.');
	if(dot_pos == std::string::npos) return filename;
	else return filename.substr(0, dot_pos);
}



void Utils::Assert::exit_if(bool c)
{
	if(c)
	{
		std::cout << "Error" << std::endl;
		exit(1);
	}
}



void Utils::Assert::exit_if(bool c, const char* msg)
{
	if(c)
	{
		std::cout << "Error: " << msg << std::endl;
		exit(1);
	}
}