#include "utils.h"



bool Utils::CLI::input_is_help(const char* input)
{
	return input == std::string("-help") || input == std::string("--help") || input == std::string("-h") || input == std::string("--h");
}


void Utils::Config::GenerateDefaultConfig()
{
	std::cout << "Config not provided, using default." << std::endl;
	std::ofstream default_config(Utils::Files::locate_file("default_config.yaml").c_str());
	Utils::Assert::exit_if(!default_config.is_open(), "Failed to generate default config.");
	const char* body =
	"# Default config (auto-generated)\n"
	"\n"
	"#output formats\n"
	"extensions:\n"
	"  png: true\n"
	"  jpg: true\n"
	"  webp: true\n"
	"\n"
	"#output image widths\n"
	"sizes:\n"
	"  - 768\n"
	"  - 384\n"
	"\n"
	"#conversion quality (ignored for conversion to png)\n"
	"quality: 90";
	default_config << body;
	default_config.close();
	Utils::Assert::exit_if(!Utils::Files::file_exists("default_config.yaml"), "Failed to generate default config.");
}



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