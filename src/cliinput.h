#include <iostream>
#include "utils.h"
#include "config.h"



class CLI
{
	public:
		CLI() = delete;
		CLI(int, char**);
		~CLI() = default;
	private:
		char* m_image;
		char* m_config;
	public:
		const char* GetImage();
		const char* GetConfig();
};