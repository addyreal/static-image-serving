#include "cliinput.h"



CLI::CLI(int argc, char** argv)
{
	if(argc == 2 && !Utils::CLI::input_is_help(argv[1]))
	{
		this->m_image= argv[1];
		this->m_config = (char*)"default_config.yaml";
		Utils::Assert::exit_if(!std::filesystem::exists((std::filesystem::path)argv[1]), "Provided image DNE.");
		Utils::Config::GenerateDefaultConfig();
	}
	else if(argc == 3)
	{
		this->m_image= argv[1];
		this->m_config = argv[2];
		Utils::Assert::exit_if(!std::filesystem::exists((std::filesystem::path)argv[1]), "Provided image DNE.");
		Utils::Assert::exit_if(!Utils::Files::file_exists(argv[2]), "Provided config DNE.");
	}
	else
	{
		std::cout << "Usage: static-image-convert <image> [config]\n\nArguments:\n  <image>    Path to the input image (required)\n  [config]   Config located in the project directory (optional)\n\nExamples:\n  static-img-convert ../image.jpg myconfig.yaml\n  static-img-convert hello.png" << std::endl;
		exit(0);
	}
}



const char* CLI::GetImage()
{
	return m_image;
}



const char* CLI::GetConfig()
{
	return m_config;
}