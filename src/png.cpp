#include "conversion.h"



void Image::Png::Convert(const char* input_file, unsigned int target_width)
{
	int init_width;
	int init_height;
	int init_channels;
	unsigned char* init_image = stbi_load(input_file, &init_width, &init_height, &init_channels, 0);

	if(init_image == nullptr)
	{
		std::cout << "[X] Failed to load image when converting to png, width" << target_width << "." << std::endl;
		return;
	}
	else if(target_width > init_width)
	{
		std::cout << "[I] Aborting conversion to: png, width: " << init_width << "->" << target_width << "." << std::endl;
		return;
	}

	float init_ratio = (float)init_width/(float)init_height;
	int target_height = (int)target_width/init_ratio;

	const std::string suffix = '-' + std::to_string(target_width) + "px.png";
	const std::string output_file = Utils::Files::strip_extension(std::string(input_file)).append(suffix);

	unsigned char* target_img = (unsigned char*)malloc(target_width * target_height * init_channels);

	if(stbir_resize_uint8_srgb(init_image, init_width, init_height, 0, target_img, target_width, target_height, 0, (stbir_pixel_layout)init_channels) == 0)
	{
		std::cout << "[X] Failed to resize image when converting to png, width " << target_width << "." << std::endl;
		stbi_image_free(init_image);
    	free(target_img);
		return;
	}

	if(!stbi_write_png(output_file.c_str(), target_width, target_height, init_channels, target_img, target_width * init_channels))
	{
		std::cout << "[X] Failed to write converted png image, width " << target_width << "." << std::endl;
		stbi_image_free(init_image);
    	free(target_img);
		return;
	}

	std::cout << "[ ] Success converting to: png, width: " << init_width << "->" << target_width << "." << std::endl;
	stbi_image_free(init_image);
    free(target_img);
}