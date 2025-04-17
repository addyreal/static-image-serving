#include "conversion.h"
#include "utils.h"



bool Image::supported_format(const char* filename)
{
	return Utils::Files::file_has_extension(filename, ".jpg") || Utils::Files::file_has_extension(filename, ".png");
}



bool Image::supported_channels(const char* filename)
{
	int width, height, channels;
	Utils::Assert::exit_if(!stbi_info(filename, &width, &height, &channels), "Failed to access input image.");
	return channels == 3 || channels == 4;
}



void Image::Convert(const char* input_image, std::string target_extension, unsigned int quality, unsigned int target_width)
{
	std::filesystem::path temp = (std::filesystem::path)input_image;
	const char* input_file = temp.c_str();

	if(target_extension == std::string("png"))
	{
		Image::Png::Convert(input_file, target_width);
	}
	else if(target_extension == std::string("jpg"))
	{
		Image::Jpg::Convert(input_file, quality, target_width);
	}
	else if(target_extension == std::string("webp"))
	{
		Image::Webp::Convert(input_file, quality, target_width);
	}
}