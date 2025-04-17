#include "config.h"



Config::Config(const std::string& conf_path)
{
	Utils::Assert::exit_if(!Utils::Files::file_exists(conf_path.c_str()), "Config missing.");
	YAML::Node config;
	try
	{
		config = YAML::LoadFile(Utils::Files::get_proper_path(conf_path));
	}
	catch(...) {Utils::Assert::exit_if(true, "Config failed to open.");}

	// Config
	Utils::Assert::exit_if(!config.IsDefined(), "Config invalid.");
	Utils::Assert::exit_if(!config.IsMap(), "Config invalid.");

	// Extensions
	Utils::Assert::exit_if(!config["extensions"].IsDefined(), "Config extensions missing.");
	Utils::Assert::exit_if(!config["extensions"].IsMap(), "Config extensions invalid.");
	Utils::Assert::exit_if(!config["extensions"]["png"].IsDefined(), "Config png extension unspecified.");
	Utils::Assert::exit_if(!config["extensions"]["png"].IsScalar(), "Config png extension invalid.");
	Utils::Assert::exit_if(!config["extensions"]["jpg"].IsDefined(), "Config jpg extension unspecified.");
	Utils::Assert::exit_if(!config["extensions"]["jpg"].IsScalar(), "Config jpg extension invalid.");
	Utils::Assert::exit_if(!config["extensions"]["webp"].IsDefined(), "Config webp extension unspecified.");
	Utils::Assert::exit_if(!config["extensions"]["webp"].IsScalar(), "Config webp extension invalid.");
	try
	{
		if(config["extensions"]["png"].as<bool>())
		{
			this->extensions.push_back("png");
		}
	}
	catch(...) {Utils::Assert::exit_if(true, "Config png extension invalid.");}
	try
	{
		if(config["extensions"]["jpg"].as<bool>())
		{
			this->extensions.push_back("jpg");
		}
	}
	catch(...) {Utils::Assert::exit_if(true, "Config jpg extension invalid.");}
	try
	{
		if(config["extensions"]["webp"].as<bool>())
		{
			this->extensions.push_back("webp");
		}
	}
	catch(...) {Utils::Assert::exit_if(true, "Config webp extension invalid.");}

	// Sizes
	Utils::Assert::exit_if(!config["sizes"].IsDefined(), "Config sizes missing.");
	Utils::Assert::exit_if(!config["sizes"].IsSequence(), "Config sizes invalid.");
	for(YAML::iterator it = config["sizes"].begin(); it != config["sizes"].end(); it++)
	{
		Utils::Assert::exit_if(!it->IsScalar(), "Config size invalid.");
		try
		{
			Utils::Assert::exit_if(it->as<unsigned int>() == 0, "Config size invalid.");
			this->sizes.push_back(it->as<unsigned int>());
		}
		catch(...) {Utils::Assert::exit_if(true, "Config size invalid.");}
	}

	// Quality
	Utils::Assert::exit_if(!config["quality"].IsDefined(), "Config conversion quality missing.");
	Utils::Assert::exit_if(!config["quality"].IsScalar(), "Config conversion quality invalid.");
	try
	{
		Utils::Assert::exit_if(config["quality"].as<unsigned int>() <= 0, "Config conversion quality invalid.");
		Utils::Assert::exit_if(config["quality"].as<unsigned int>() > 100, "Config conversion quality invalid.");
		this->quality = config["quality"].as<unsigned int>();
	}
	catch(...) {Utils::Assert::exit_if(true, "Config conversion quality invalid.");}
}