#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include <vector>
#include <thread>
#include "cliinput.h"
#include "utils.h"
#include "config.h"
#include "conversion.h"



int main(int argc, char** argv)
{
	CLI CLIParse(argc, argv);

	const char* input_image = CLIParse.GetImage();
		Utils::Assert::exit_if(!Image::supported_format(input_image), "Input image is of unsupported format.");
		Utils::Assert::exit_if(!Image::supported_channels(input_image), "Input image is of unsupported channels.");
	const char* input_config = CLIParse.GetConfig();
		Config config(input_config);

	std::vector<std::thread> threads;
		std::cout << "[ ] Conversions pending: " << config.extensions.size() * config.sizes.size() << "." << std::endl;
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