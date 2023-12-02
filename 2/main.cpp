#include <stdio.h>
#include <string>
#include <fstream>
#include <ctype.h>
#include <stdint.h>

int main(int argc, char **argv)
{
	std::ifstream input;
	std::string temp;

	input.open("input.txt");
	
	if(!input.is_open())
	{
		printf("Couldn't open file\n");
		return -1;
	}

	while(input.good())
	{
		input >> temp;
		if(input.eof())
		{
			break;
		}

		// Start processing after eof check to avoid reading last line twice
	}

	input.close();
	return 0;
}
