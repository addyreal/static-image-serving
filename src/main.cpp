#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include <vector>
#include <thread>
#include <filesystem>
#include "utils.h"
#include "config.h"
#include "conversion.h"



int main(int argc, char** argv)
{
	const char* input_config;
	const char* input_image;
	switch(argc)
	{
		case 2:
		{
			std::cout << "Config not provided, using default." << std::endl;
			Utils::Assert::exit_if(!std::filesystem::exists((std::filesystem::path)argv[1]), "Provided image DNE.");
			GenerateDefaultConfig();
			Utils::Assert::exit_if(!Utils::Files::file_exists("default_config.yaml"), "Failed to generate default config.");
			input_config = "default_config.yaml";
			input_image = argv[1];
			break;
		}
		case 3:
		{
			Utils::Assert::exit_if(!std::filesystem::exists((std::filesystem::path)argv[1]), "Provided image DNE.");
			Utils::Assert::exit_if(!Utils::Files::file_exists(argv[2]), "Provided config DNE.");
			input_image = argv[1];
			input_config = argv[2];
			break;
		}
		default:
		{
			Utils::Assert::exit_if(true, "Usage: static-image-convert {image} ({config}optional). \nLooks for config in project dir.");
			break;
		}
	}

	Utils::Assert::exit_if(!Image::can_be_converted(input_image), "Input image is of unsupported format.");
	Config config(input_config);

	std::vector<std::thread> threads;
	threads.reserve(config.extensions.size() * config.sizes.size());

	for(std::string extension: config.extensions)
	{
		for(unsigned int size: config.sizes)
		{
			threads.emplace_back([&, extension, size]()
			{
				Image::Convert(input_image, extension, config.quality, size);
			});
		}
	}

	for(std::thread& thread: threads)
	{
		thread.join();
	}

	return 0;
}