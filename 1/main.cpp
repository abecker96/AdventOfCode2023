#include <stdio.h>
// I would love to use <iostream> here instead as a more c++ style output...
// But for some reason I can't even print "Hello World" without getting a memory access violation error
#include <string>
#include <fstream>
#include <tuple>
#include <ctype.h>
#include <stdint.h>

// Day One of Advent of Code.
// There's a glaring algorithmic improvement I'd like to make, which is to search for the last number from the back of each line.
// Also I'm pretty sure this method of accessing files line-by-line is terrible for performance...
// Also need to figure out why I can't use iostream, but I'll save that for day 2's project.

/**
* Takes a ASCII character input, and returns numerical value
*  
*  @param A numerical character
*  @return The numerical value of the parameter
*  @note There is no handling for non-numeric characters, and it only takes ASCII
*/
uint8_t lazy_ctoi(char num)
{
	return num - '0';
}

/**
* Begins checking a string at a given index for substrings representing numbers
* For example passing the string "2one" and an index of 1 will return 1
* Passing the string "2one" and an index of 0 will return -1
*
* @param A string to check
* @param The index to search from
* @return On success: An int 0-9. On Failure: -1
*/
int lazy_substrtoi(std::string str, int index)
{
	const int keys[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	const std::string values[10] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

	for(int key : keys)
	{
		uint32_t in_idx = index;
		uint32_t key_idx = 0;
		bool mismatch = false;

		while(key_idx < values[key].size() && in_idx < str.size())
		{
			if(values[key][key_idx] != str[in_idx])
			{
				mismatch = true;
				break;
			}

			in_idx++;
			key_idx++;
		}

		// Made it all the way to the end of a key without a mismatch
		if(!mismatch && key_idx == values[key].size())
		{
			return keys[key];
		}
	}

	return -1;
}

/**
* Takes a string representing a line of text as input, and returns the "Calibration Value" as outlined in Prompt.txt
* 
* @param A line of input to check
* @return The "Calibration Value" for that line. Should never be greater than 99.
*/
uint8_t getCalibrationValue(std::string line)
{
	bool found_first = false;
	bool found_last = false;
	uint8_t first, last;
	uint8_t value;	// we know it's only two digits, so it'll fit in an int8
	int temp;
	
	// Probably more efficient to find the first from the front
	// then find the last from the back of the string
	// Tomorrow problems though
	for(uint32_t i = 0; i < line.size(); i++)
	{
		bool found;

		// Check if we get a simple digit
		if(isdigit(line[i]))
		{
			found = true;
			// Yes, I could just use either the 'real' ctoi, or sscanf, or really any library function 
			temp = lazy_ctoi(line[i]);
		}
		// Otherwise check if it's a string representing a digit
		else
		{
			found = true;
			temp = lazy_substrtoi(line, i);
		}

		if(found && temp > 0)
		{
			// Figure out if we found the first or last digit
			if(!found_first)
			{
				first = temp;
				found_first = true;
			}
			else
			{
				last = temp;
				found_last = true;
			}
		}
	}

	// Handle case with only one number
	if(!found_last)
	{
		last = first;
	}

	value = first*10 + last;
	printf("%s: %d\n", line.c_str(), value);

	return value;
}

int main(int argc, char **argv)
{
	std::ifstream input;
	std::string temp;
	uint32_t sum = 0;
	uint32_t previous;

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
		previous = sum;
		sum += getCalibrationValue(temp);
		if(previous > sum)
		{
			printf("Overflow?");
		}
	}

	printf("sum: %d\n", sum);

	input.close();
	return 0;
}
