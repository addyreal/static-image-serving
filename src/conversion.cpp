#include "conversion.h"



bool Image::can_be_converted(const char* filename)
{
	return Utils::Files::file_has_extension(filename, ".jpg") || Utils::Files::file_has_extension(filename, ".png");
}



void Image::Convert(const char* input_file, std::string target_extension, unsigned int target_width)
{
	if(target_extension == std::string("png"))
	{
		Image::Png::Convert(input_file, target_width);
	}
	else if(target_extension == std::string("jpg"))
	{
		Image::Jpg::Convert(input_file, target_width);
	}
	else if(target_extension == std::string("webp"))
	{
		Image::Webp::Convert(input_file, target_width);
	}
}



void Image::Png::Convert(const char* input_file, unsigned int target_width)
{
	int init_width;
	int init_height;
	int init_channels;
	unsigned char* init_image = stbi_load(Utils::Files::locate_file(input_file).c_str(), &init_width, &init_height, &init_channels, 0);

	Utils::Assert::exit_if(init_image == nullptr, "Failed to open image.");
	if(target_width > init_width)
	{
		std::cout << "Aborting resize from width " << init_width << " to " << target_width << "." << std::endl;
		return;
	}

	float init_ratio = (float)init_width/(float)init_height;

	const std::string suffix = '-' + std::to_string(target_width) + "px.png";
	const std::string output_file = Utils::Files::strip_extension(std::string(input_file)).append(suffix);
	int target_height = (int)target_width/init_ratio;
	unsigned char* target_img = (unsigned char*)malloc(target_width * target_height * init_channels);
	stbir_resize_uint8_srgb(init_image, init_width, init_height, 0, target_img, target_width, target_height, 0, (stbir_pixel_layout)init_channels);
	Utils::Assert::exit_if(!stbi_write_png(Utils::Files::locate_file(output_file).c_str(), target_width, target_height, init_channels, target_img, target_width * init_channels), "Failed to write converted image.");

	std::cout << "Success converting to: png, width: " << init_width << "->" << target_width << "." << std::endl;
	stbi_image_free(init_image);
    free(target_img);
}



void Image::Jpg::Convert(const char* input_file, unsigned int target_width)
{
	int init_width;
	int init_height;
	int init_channels;
	unsigned char* init_image = stbi_load(Utils::Files::locate_file(input_file).c_str(), &init_width, &init_height, &init_channels, 0);

	Utils::Assert::exit_if(init_image == nullptr, "Failed to open image.");
	if(target_width > init_width)
	{
		std::cout << "Aborting resize from width " << init_width << " to " << target_width << "." << std::endl;
		return;
	}
	if(init_channels == 4)
	{
		std::cout << "Warning: Converting an image with an alpha channel to jpg." << std::endl;
	}

	float init_ratio = (float)init_width/(float)init_height;

	const std::string suffix = '-' + std::to_string(target_width) + "px.jpg";
	const std::string output_file = Utils::Files::strip_extension(std::string(input_file)).append(suffix);
	int target_height = (int)target_width/init_ratio;
	unsigned char* target_img = (unsigned char*)malloc(target_width * target_height * init_channels);
	stbir_resize_uint8_srgb(init_image, init_width, init_height, 0, target_img, target_width, target_height, 0, (stbir_pixel_layout)init_channels);
	Utils::Assert::exit_if(!stbi_write_jpg(Utils::Files::locate_file(output_file).c_str(), target_width, target_height, init_channels, target_img, 100), "Failed to write converted image.");

	std::cout << "Success converting to: jpg, width: " << init_width << "->" << target_width << "." << std::endl;
	stbi_image_free(init_image);
    free(target_img);
}



void Image::Webp::Convert(const char* input_file, unsigned int target_width)
{
	// return if init_width < target_width
	std::cout << "Converting to webp not yet supported." << std::endl;
}