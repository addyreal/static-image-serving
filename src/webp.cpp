#include "conversion.h"



void Image::Webp::Convert(const char* input_file, unsigned int quality, unsigned int target_width)
{
	int init_width;
	int init_height;
	int init_channels;
	unsigned char* init_image = stbi_load(input_file, &init_width, &init_height, &init_channels, 0);

	if(init_image == nullptr)
	{
		std::cout << "[X] Failed to load image when converting to webp, width" << target_width << "." << std::endl;
		return;
	}
	else if(target_width > init_width)
	{
		std::cout << "[I] Aborting conversion to: webp, width: " << init_width << "->" << target_width << "." << std::endl;
		return;
	}

	float init_ratio = (float)init_width/(float)init_height;
	int target_height = (int)target_width/init_ratio;

	const std::string suffix = '-' + std::to_string(target_width) + "px.webp";
	const std::string output_file = Utils::Files::strip_extension(std::string(input_file)).append(suffix);

	unsigned char* target_img = (unsigned char*)malloc(target_width * target_height * init_channels);

	if(stbir_resize_uint8_srgb(init_image, init_width, init_height, 0, target_img, target_width, target_height, 0, (stbir_pixel_layout)init_channels) == 0)
	{
		std::cout << "[X] Failed to resize image when converting to webp, width " << target_width << "." << std::endl;
		stbi_image_free(init_image);
    	free(target_img);
		return;
	}

	uint8_t* target_webp = nullptr;
	size_t target_webp_size;
	switch(init_channels)
	{
		case 3:
			target_webp_size = WebPEncodeRGB(target_img, target_width, target_height, target_width * init_channels, quality, &target_webp);
			break;
		case 4:
			target_webp_size = WebPEncodeRGBA(target_img, target_width, target_height, target_width * init_channels, quality, &target_webp);
			break;
		default:
			std::cout << "[X] Unexpected error, tried to convert image with channels not 3 or 4." << std::endl;
			stbi_image_free(init_image);
			free(target_img);
			WebPFree(target_webp);
			return;
			break;
	}

	if(!target_webp)
	{
		std::cout << "[X] Failed to encode converted image to webp." << std::endl;
		stbi_image_free(init_image);
		free(target_img);
		WebPFree(target_webp);
		return;
	}

	std::ofstream output(output_file.c_str(), std::ios::binary);
	if(!output.is_open())
	{
		std::cout << "[X] Failed to write converted webp image, width " << target_width << "." << std::endl;
		stbi_image_free(init_image);
		free(target_img);
		WebPFree(target_webp);
		return;
	}
	output.write(reinterpret_cast<const char*>(target_webp), target_webp_size);
	output.close();

	std::cout << "[ ] Success converting to: webp, width: " << init_width << "->" << target_width << "." << std::endl;
	stbi_image_free(init_image);
	free(target_img);
	WebPFree(target_webp);
}