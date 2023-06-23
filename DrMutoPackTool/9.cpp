#include <fstream>
#include <filesystem>
#include <iomanip>
#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include "1.hpp"

void detect_input_name_v1(std::string input_name, std::shared_ptr<DrMuto000helper::helper1> sp1)
{
	std::string backup_name1{ input_name };
	std::string::size_type insize{0};
	std::string::size_type find1{0};
	std::string::size_type find2{0};
	std::basic_string <char>::iterator find_out;
	std::string alt_namesake {sp1->base_namesake};

	insize = input_name.length();
	alt_namesake.push_back(0x2e); // "."
	find1 = backup_name1.std::string::find(alt_namesake);
	switch (find1)
	{
	case -1:
		// do absolutely nothing here because there's nothing to find anymore.
		break;
	default:
		find2 = insize - find1;
		find_out = backup_name1.erase(backup_name1.begin() + find1, backup_name1.end());
		break;
	}
	std::filesystem::path path1(backup_name1);
	for (char i1 = 0; i1 < MAX_PARTS; i1++)
	{
		std::ifstream input_file;
		std::filesystem::path backup_path1(path1);
		backup_path1.append(sp1->part_name[i1]);
		input_file.open(backup_path1, std::ios_base::in | std::ios_base::binary | std::ios_base::ate, _SH_DENYRD);
		if (input_file.is_open())
		{
			std::streamoff if_info2;
			if_info2 = input_file.tellg();
			sp1->part_file_exists[i1] = true;
			sp1->actual_part_name[i1] = backup_path1.string();
			sp1->part_offset[i1] = 0;
			sp1->part_size[i1] = if_info2;
			input_file.close();
		}
	}
}
