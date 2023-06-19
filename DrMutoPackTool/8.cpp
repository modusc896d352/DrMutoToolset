#include <direct.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <memory>
#include <vector>
#include "1.hpp"

void parse_drmuto_toc(std::shared_ptr<DrMuto000helper::helper1> sp1, std::shared_ptr<DrMuto000helper::header_info> sp2, std::vector<char> &toc_data)
{
	if (sp1->option_level == 2)
	{
		std::string target_output_path {sp1->actual_part_name[0]};
		std::string target_matching_name {sp1->base_namesake};
		std::string target_folder_name {sp1->base_namesake};
		std::string::size_type find_matching_name {0};
		std::string::size_type subtract_matching_name {0};
		std::string::size_type size_of_output_path {0};
		std::string::size_type size_of_matching_name {0};
		std::string::iterator output_path_iterator;

		target_matching_name.append(".000");
		find_matching_name = target_output_path.std::string::find(target_matching_name);
		size_of_output_path = target_output_path.length();
		size_of_matching_name = target_matching_name.length();
		if (find_matching_name > 0)
		{
			subtract_matching_name = size_of_output_path - size_of_matching_name;
			output_path_iterator = target_output_path.erase(target_output_path.begin() + subtract_matching_name, target_output_path.end());
			target_folder_name.append("[extracted]");
			target_output_path.append(target_folder_name);
			target_output_path.append(sp1->default_folder_symbol);
			if (_mkdir(target_output_path.c_str()) == 0)
			{
				std::cout << std::endl << "Creating output folder if it doesn't already exist." << std::endl << std::endl;
			}
			sp1->output_folder_path = target_output_path;
		}
	}
	std::shared_ptr<DrMuto000helper::toc_info> sp3 = std::make_shared<DrMuto000helper::toc_info>();
	std::shared_ptr<DrMuto000helper::dir_name_info> sp4 = std::make_shared<DrMuto000helper::dir_name_info>();
	sp3->current_entry_pos[0] = sp2->entry_info_section2_section2_offset;
	parse_drmuto_dir(sp1, sp2, sp3, sp4, toc_data, 0);
}

void parse_drmuto_dir(std::shared_ptr<DrMuto000helper::helper1> sp1, std::shared_ptr<DrMuto000helper::header_info> sp2, std::shared_ptr<DrMuto000helper::toc_info> sp3, std::shared_ptr<DrMuto000helper::dir_name_info> sp4, std::vector<char> &toc_data, char current_dir_num)
{
	if (sp3->current_entry[current_dir_num] == 0)
	{
		sp3->entries[current_dir_num] = 2;
	}
	long dir_info_offset1 = sp2->entry_info_section2_section1_offset + (sp3->current_directory_entry[current_dir_num] * 4);
	for (char i1 = sp3->current_directory_entry[current_dir_num]; i1 < sp2->num_dirs; i1++)
	{
		if (i1 != sp3->current_directory_entry[current_dir_num])
		{
			break;
		}
		long dir_info_offset2 = r_ffunc::read_s32le_from_mem(dir_info_offset1, toc_data);
		long dir_info_offset3 = 0;
		long dir_info_offset2_alt = sp3->current_entry_pos[current_dir_num] - sp2->entry_info_section2_section2_offset;
		long dir_info_offset3_alt = 0;
		if (i1 == ((sp2->num_dirs) - 1))
		{
			dir_info_offset3 = sp2->entry_info_section2_size;
			dir_info_offset3_alt = sp3->last_entry_pos[current_dir_num] - sp2->entry_info_section2_section2_offset;
		}
		else
		{
			dir_info_offset3 = r_ffunc::read_s32le_from_mem(dir_info_offset1 + 4, toc_data);
			dir_info_offset3_alt = sp3->next_entry_pos[current_dir_num] - sp2->entry_info_section2_section2_offset;
		}
		if (dir_info_offset2_alt >= dir_info_offset2 && dir_info_offset3_alt <= dir_info_offset3)
		{
			break;
		}
	}
	for (short i2 = sp3->current_entry[current_dir_num]; i2 < sp3->entries[current_dir_num]; i2++, sp3->current_entry[current_dir_num]++)
	{
		char relative_directory_components{ 0 };
		char entry_name_size = r_ffunc::read_u8_from_mem(sp3->current_entry_pos[current_dir_num], toc_data);
		sp3->current_entry_pos[current_dir_num] += 1;
		if (entry_name_size != 0)
		{
			sp3->entries[current_dir_num] += 1;
		}
		else
		{
			sp3->last_entry[current_dir_num] = sp3->current_entry[current_dir_num];
			sp3->last_entry_pos[current_dir_num] = sp3->current_entry_pos[current_dir_num];
			break;
		}
		unsigned short entry_info = r_ffunc::read_u16be_from_mem(sp3->current_entry_pos[current_dir_num], toc_data);
		sp3->current_entry_pos[current_dir_num] += 2;
		if ((entry_info & 0x8000) == 0)
		{
			sp3->dir_type[current_dir_num] = 1;
			sp3->selected_file_entry[current_dir_num] = entry_info & 0xffff;
		}
		else
		{
			sp3->dir_type[current_dir_num] = 0;
			sp3->selected_directory_entry[current_dir_num] = entry_info & 0x7fff;
		}
		std::string entry_name_string{ "" };
		for (char j1 = 0; j1 < entry_name_size+1; j1++)
		{
			char entry_name_char = r_ffunc::read_u8_from_mem(sp3->current_entry_pos[current_dir_num], toc_data);
			sp3->current_entry_pos[current_dir_num] += 1;
			entry_name_string.push_back(entry_name_char);
		}
		entry_name_string.pop_back();
		sp3->next_entry_pos[current_dir_num] = sp3->current_entry_pos[current_dir_num];
		sp4->current_dir_name[current_dir_num] = entry_name_string;
		if (entry_name_string == sp3->relative_directory_component1)
		{
			relative_directory_components = 1;
		}
		else if (entry_name_string == sp3->relative_directory_component2)
		{
			relative_directory_components = 2;
		}
		char name_collec = current_dir_num + 1;
		sp3->full_entry_name[current_dir_num] = "";
		std::string tentative_path_name{ "" };
		tentative_path_name.reserve(200);
		for (char j2 = 0; j2 < name_collec; j2++)
		{
			tentative_path_name.push_back(0x2f);
			tentative_path_name.append(sp4->current_dir_name[j2]);
		}
		sp3->full_entry_name[current_dir_num] = tentative_path_name;
		if (sp3->dir_type[current_dir_num] == 0)
		{
			if (relative_directory_components == 0)
			{
				if (tentative_path_name != sp3->empty_pathway)
				{
					if (sp1->option_level == 2)
					{
						std::string mkdir_target{ "" };
						mkdir_target.append(sp1->output_folder_path);
						mkdir_target.pop_back();
						mkdir_target.append(tentative_path_name);
						mkdir_target.append(sp1->default_folder_symbol);
						int mkdir_success = _mkdir(mkdir_target.c_str());
					}
				}
				sp3->current_directory_entry[current_dir_num + 1] = sp3->selected_directory_entry[current_dir_num];
				long cep_dir1 = sp2->entry_info_section2_section1_offset + (sp3->selected_directory_entry[current_dir_num] * 4);
				sp3->current_entry_pos[current_dir_num + 1] = r_ffunc::read_s32le_from_mem(cep_dir1, toc_data);
				sp3->current_entry_pos[current_dir_num + 1] += sp2->entry_info_section2_section2_offset;
				sp3->next_entry_pos[current_dir_num + 1] = sp3->current_entry_pos[current_dir_num + 1];
				parse_drmuto_dir(sp1,sp2,sp3,sp4,toc_data,current_dir_num+1);
			}
		}
		else if (sp3->dir_type[current_dir_num] == 1)
		{
			std::shared_ptr<DrMuto000helper::file_info> sp5 = std::make_shared<DrMuto000helper::file_info>();
			long cep_dir2 = sp2->entry_info_section1_offset + (sp3->selected_file_entry[current_dir_num] * 12);
			parse_drmuto_file(sp1, sp2, sp3, sp4, sp5, toc_data, cep_dir2, sp3->full_entry_name[current_dir_num]);
		}
	}
	for (char i1 = sp3->current_directory_entry[current_dir_num]; i1 < sp2->num_dirs; i1++)
	{
		char check_level{ 0 };
		if (i1 != sp3->current_directory_entry[current_dir_num])
		{
			break;
		}
		long dir_info_offset2 = r_ffunc::read_s32le_from_mem(dir_info_offset1, toc_data);
		long dir_info_offset3 = 0;
		long dir_info_offset2_alt = sp3->current_entry_pos[current_dir_num] - sp2->entry_info_section2_section2_offset;
		if (i1 == ((sp2->num_dirs) - 1))
		{
			dir_info_offset3 = sp2->entry_info_section2_size;
		}
		else
		{
			dir_info_offset3 = r_ffunc::read_s32le_from_mem(dir_info_offset1 + 4, toc_data);
		}
		if (dir_info_offset2_alt == dir_info_offset3)
		{
			sp3->dir_type[current_dir_num] = 0;
			sp3->entries[current_dir_num] = 0;
			sp3->current_directory_entry[current_dir_num] = 0;
			sp3->selected_directory_entry[current_dir_num] = 0;
			sp3->selected_file_entry[current_dir_num] = 0;
			sp3->full_entry_name[current_dir_num] = "";
			sp3->current_entry[current_dir_num] = 0;
			sp3->last_entry[current_dir_num] = 0;
			sp3->current_entry_pos[current_dir_num] = 0;
			sp3->next_entry_pos[current_dir_num] = 0;
			sp3->last_entry_pos[current_dir_num] = 0;
			sp3->first_entry_pos[current_dir_num] = 0;
			sp3->first_entry_name[current_dir_num] = "";
			sp3->second_entry_pos[current_dir_num] = 0;
			sp3->second_entry_name[current_dir_num] = "";
			sp4->current_dir_name[current_dir_num] = "";
			break;
		}
	}
}

void parse_drmuto_file(std::shared_ptr<DrMuto000helper::helper1> sp1, std::shared_ptr<DrMuto000helper::header_info> sp2, std::shared_ptr<DrMuto000helper::toc_info> sp3, std::shared_ptr<DrMuto000helper::dir_name_info> sp4, std::shared_ptr<DrMuto000helper::file_info> sp5, std::vector<char>& toc_data, long file_info_pos, std::string input_name)
{
	sp5->file_size1 = r_ffunc::read_u32le_from_mem(file_info_pos, toc_data);
	sp5->file_size2 = r_ffunc::read_u32le_from_mem(file_info_pos+4, toc_data);
	sp5->file_offset = r_ffunc::read_u32le_from_mem(file_info_pos+8, toc_data);
	long avg_part_size1 = sp2->avg_part_size >> 11;
	sp5->deduced_part_number = ((sp5->file_offset >> 23) & 0xf) + 1;
	sp5->additional_flags = ((sp5->file_offset >> 27) & 0x1f);
	sp5->deduced_file_offset = (sp5->file_offset & 0x7fffff) << 11;
	if (sp5->file_size1 != sp5->file_size2)
	{
		sp5->sizes_dont_match = true;
	}
	switch (sp1->option_level)
	{
	case 1:
		std::cout << "file name (folders included): " << input_name << std::endl;
		switch (sp5->sizes_dont_match)
		{
		case false:
			std::cout << " file size: " << std::hex << std::nouppercase << sp5->file_size2 << std::endl;
			break;
		case true:
			std::cout << " file size (main value): " << std::hex << std::nouppercase << sp5->file_size1 << std::endl;
			std::cout << " file size (alternate value): " << std::hex << std::nouppercase << sp5->file_size2 << std::endl;
			break;
		}
		std::cout << " file offset (on physical file): " << std::hex << std::nouppercase << sp5->deduced_file_offset << std::endl;
		std::cout << " physical file number: " << std::dec << std::nouppercase << sp5->deduced_part_number << std::endl;
		std::cout << " additional flags: " << std::dec << std::nouppercase << sp5->additional_flags << std::endl;
		break;
	case 2:
		r_ffunc::extract_file_data(sp1, input_name, sp5->deduced_file_offset, sp5->file_size2, sp5->deduced_part_number);
		break;
	}
}
