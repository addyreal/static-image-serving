#pragma once
#include "utils.h"
#include <iostream>
#include <fstream>
#include "stb_image.h"
#include "stb_image_write.h"
#include "stb_image_resize2.h"
#include "webp/encode.h"



namespace Image
{
	bool can_be_converted(const char*);
	void Convert(const char*, std::string, unsigned int, unsigned int);
	namespace Png
	{
		void Convert(const char*, unsigned int);
	}
	namespace Jpg
	{
		void Convert(const char*, unsigned int, unsigned int);
	}
	namespace Webp
	{
		void Convert(const char*, unsigned int, unsigned int);
	}
}