#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
#include "1.hpp"

void fill_drmuto_info1(std::shared_ptr<DrMuto000helper::helper1> sp1)
{
	for (char i1 = 0; i1 < MAX_PARTS; i1++)
	{
		sp1->part_number[i1] = i1;
		std::ostringstream temp_name;
		temp_name << sp1->base_namesake << "." << std::dec << std::uppercase << std::setw(3) << std::setfill('0') << std::to_string(sp1->part_number[i1]);
		sp1->part_name[i1] = temp_name.str();
	}
}

/*
void detect_input_name(std::string input_name, size_t name_size, std::shared_ptr<DrMuto000helper::helper1> sp1)
{
	std::string backup_name1{ input_name };
	std::string backup_name2{ input_name };
	short last_name_char{ (short)name_size - 1 };
	short char_number_of_last_folder{ 0 };
	short char_number_of_penultimate_folder{ 0 }; // (todo) not used, if deleted probably wouldn't be that big a loss
	bool input_name_has_folder_symbols{ false };
	bool input_name_ends_with_folder_symbols{ false };
	std::string folder_symbol{""};

	for (char i2 = 0; i2 < name_size; i2++) {
		std::string::reference iNameRef1 = input_name.std::string::at(i2);
		if (iNameRef1 == '\\' || iNameRef1 == '/')
		{
			switch (char_number_of_last_folder)
			{
			case 0:
				input_name_has_folder_symbols = true;
				folder_symbol = (std::string::value_type)iNameRef1;
				sp1->default_folder_symbol = folder_symbol;
				char_number_of_last_folder = i2;
				break;
			default:
				char_number_of_last_folder = i2;
				break;
			}
		}
	}
	switch (input_name_has_folder_symbols)
	{
	case true:
		std::string::reference iNameRef2 = input_name.std::string::at(last_name_char);
		if (iNameRef2 == '\\' || iNameRef2 == '/')
		{
			input_name_ends_with_folder_symbols = true;
		}
		switch (input_name_ends_with_folder_symbols)
		{
		case false:
			backup_name2.std::string::append(folder_symbol);
			break;
		}
		for (char i2 = 0; i2 < (char_number_of_last_folder - 1); i2++) {
			std::string::reference iNameRef3 = input_name.std::string::at(i2);
			if (iNameRef3 == '\\' || iNameRef3 == '/')
			{
				char_number_of_penultimate_folder = i2;
			}
		}
		break;
	}
	char max_tries = 2;
	std::string::size_type tn1size{0};
	std::string::size_type tn2size{0};
	std::string::size_type find1{0};
	std::string::size_type find2{0};
	std::string alt_namesake {sp1->base_namesake};
	alt_namesake.push_back(0x2e);
	for (char i3 = 0; i3 < MAX_PARTS; i3++)
	{
		std::string tentative_name1{""};
		std::string tentative_name2{""};
		for (char j1 = 0; j1 < max_tries; j1++)
		{
			std::ifstream input_file;
			switch (j1)
			{
			case 0:
				tentative_name1 = backup_name1;
				break;
			case 1:
				tentative_name1 = backup_name2;
				break;
			default:
				break;
			}
			std::basic_string <char>::iterator tn1iter1;
			std::basic_string <char>::iterator tn1iter2;
			std::basic_string <char>::iterator tn1iter3;
			tn1size = tentative_name1.length();
			find1 = tentative_name1.std::string::find(alt_namesake);
			std::string::reference iNameRef4 = tentative_name1.std::string::at(tn1size - 1);
			tentative_name2 = tentative_name1;
			tn2size = tentative_name2.length();
			switch (find1)
			{
			case -1:
				if (j1 == 0)
				{
					if (char_number_of_last_folder != 0 && input_name_ends_with_folder_symbols == false)
					{
						tentative_name2.append(folder_symbol);
					}
				}
				tentative_name2.append(sp1->part_name[i3]);
				break;
			default:
				find2 = tn2size - find1;
				tn1iter2 = tentative_name2.erase(tentative_name2.begin() + find1, tentative_name2.end());
				tentative_name2.append(sp1->part_name[i3]);
				break;
			}
			input_file.open(tentative_name2, std::ios_base::in | std::ios_base::binary | std::ios_base::ate, _SH_DENYRD);
			if (input_file.rdbuf()->is_open())
			{
				std::streamoff if_info2;
				if_info2 = input_file.tellg();
				sp1->part_file_exists[i3] = true;
				sp1->actual_part_name[i3] = tentative_name2;
				sp1->part_offset[i3] = 0;
				sp1->part_size[i3] = if_info2;
				input_file.close();
			}
		}
	}
}
*/
