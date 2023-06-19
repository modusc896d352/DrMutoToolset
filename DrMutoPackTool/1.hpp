#ifndef _I_H_
#define _I_H_

#include <fstream>
#include <string>
#include <vector>

#define MAX_PARTS 17
#define MAX_TOC_DIRS 10
#define MAX_FILES 640

/*
As the name suggests, it is a namespace meant to help with the essential ins-and-outs of the tool.
*/
namespace DrMuto000helper
{
	/*
	An struct with essential info,
	meant to act as a list of file names
	for the program to rely on.
	*/
	struct helper1
	{
		/* the namesake that serves as a base for what would be part_name. */
		std::string base_namesake{ "DRMUTO" };
		/* the current part number (1 as an example). */
		char part_number[MAX_PARTS]{ 0 };
		/* the current part file name (DRMUTO.001 as an example). */
		std::string part_name[MAX_PARTS]{ "" };
		/* if this part file actually exists. */
		bool part_file_exists[MAX_PARTS]{ false };
		//long part_size[MAX_PARTS]{ 0 };
		/* the actual part file that exists on someone's old hard drive. */
		std::ifstream actual_part_file[MAX_PARTS];
		/* the registered file name. */
		std::string actual_part_name[MAX_PARTS]{ "" };
		/* if this part file has an offset number associated with it.*/
		long part_offset[MAX_PARTS]{ 0 };
		/* the size of the part file (in bytes). */
		std::streamoff part_size[MAX_PARTS]{ 0 };
		//helper1(std::string[MAX_PARTS], char[MAX_PARTS], std::string[MAX_PARTS], bool[MAX_PARTS], long[MAX_PARTS], std::ifstream[MAX_PARTS], std::streamoff[MAX_PARTS]);
		/* the "option level", set based on user input. */
		char option_level{ 0 };
		/* the folder symbol that came with the input name, if it has one. */
		std::string default_folder_symbol{ "" };
		/* the output folder path we're extracting the files to. */
		std::string output_folder_path{ "" };
	};
	struct header_info
	{
		long num_parts;
		long avg_part_size;
		long num_files;
		long num_dirs;
		long entry_name_depot_size;
		long entry_info_section1_offset;
		long entry_info_section1_size;
		long entry_info_section2_section1_offset;
		long entry_info_section2_section2_offset;
		long entry_info_section2_size;
	};
	struct toc_info
	{
		std::string relative_directory_component1{ "." };
		std::string relative_directory_component2{ ".." };
		std::string empty_pathway{ "" };
		char dir_num[MAX_TOC_DIRS]{ 0 };
		char dir_type[MAX_TOC_DIRS]{ 0 }; // if dir_type equals 1, then we're dealing with a folder here
		short entries[MAX_TOC_DIRS]{ 0 };
		short current_directory_entry[MAX_TOC_DIRS]{ 0 };
		short current_file_entry[MAX_TOC_DIRS]{ 0 };
		short selected_entry[MAX_TOC_DIRS]{ 0 };
		short selected_directory_entry[MAX_TOC_DIRS]{ 0 };
		short selected_file_entry[MAX_TOC_DIRS]{ 0 };
		std::string full_entry_name[MAX_TOC_DIRS]{ "" };
		short current_entry[MAX_TOC_DIRS]{ 0 };
		short last_entry[MAX_TOC_DIRS]{ 0 };
		long current_entry_pos[MAX_TOC_DIRS]{ 0 };
		long next_entry_pos[MAX_TOC_DIRS]{ 0 };
		long last_entry_pos[MAX_TOC_DIRS]{ 0 };
		char entry_pos_if_entry_is_file[MAX_TOC_DIRS]{ 0 };
		long first_entry_pos[MAX_TOC_DIRS]{ 0 }; // reserved for an entry whose name is "."
		std::string first_entry_name[MAX_TOC_DIRS]{ "" }; // ditto
		long second_entry_pos[MAX_TOC_DIRS]{ 0 }; // reserved for an entry whose name is ".."
		std::string second_entry_name[MAX_TOC_DIRS]{ "" }; // ditto
	};
	struct dir_name_info
	{
		std::string current_dir_name[MAX_TOC_DIRS]{ "" };
	};
	struct file_info
	{
		bool sizes_dont_match{ false };
		long file_size1{ 0 };
		long file_size2{ 0 };
		long file_offset{ 0 };
		long deduced_part_number{ 0 };
		long additional_flags{ 0 };
		long deduced_file_offset{ 0 };
		std::string full_file_name{ "" };
	};
};

/*
A namespace that houses input/output read/write functions, all related to certain bits within binary files.
*/
namespace r_ffunc
{
	//char read_s8(long offset, std::ifstream &input_file);
	unsigned char read_u8(long offset, std::ifstream &input_file);
	unsigned char read_u8_from_mem(long offset, std::vector<char> input_data);
	short read_s16le_from_mem(long offset, std::vector<char> input_data);
	unsigned short read_u16le_from_mem(long offset, std::vector<char> input_data);
	short read_s16be_from_mem(long offset, std::vector<char> input_data);
	unsigned short read_u16be_from_mem(long offset, std::vector<char> input_data);
	long read_s32le_from_mem(long offset, std::vector<char> input_data);
	unsigned long read_u32le_from_mem(long offset, std::vector<char> input_data);
	void put_u8_to_mem(unsigned char target_var, long offset, std::vector<char> &input_data);
	long decompress_drmuto_block(std::vector<char> &input_data, long target_input_size, std::vector<char> &output_data, long target_output_size, long &inp_var5, long &inp_var6, long *inp_var7);
	void extract_file_data(std::shared_ptr<DrMuto000helper::helper1> sp1, std::string input_name, long file_offset, long file_size, long part_number);
};

/*
Prints out an basic help message.
*/
void display_case1_help_message();
/*
Prints out an help message that tries to be helpful somehwat.
*/
void display_case2_help_message();
/*
Prints out the "behind-the-scenes" text of the program.
*/
void display_case3_help_message();
/*
Uses two fields (out of four) from the DrMuto000helper::helper1 struct,
and fills them in with actual data (part number and part name, respectively).
*/
void fill_drmuto_info1(std::shared_ptr<DrMuto000helper::helper1> sp1);
/*
Uses the input name as a basis to determine whether or not the program has everything it needs to basically get going.
*/
void detect_input_name(std::string input_name, size_t name_size, std::shared_ptr<DrMuto000helper::helper1> sp1);
/*
Function name should be hopefully self-explanatory.
*/
void start_work_on_everything(std::shared_ptr<DrMuto000helper::helper1> sp1);
/*
After all the trauma that the program went through in preparing the TOC file for futher use,
the user will then be asked what exactly are they going to do with it.
In practice it just gives the user two choices, both of which should kinda work I think? Errrrrrr...
*/
void choose_your_mode(std::shared_ptr<DrMuto000helper::helper1> sp1, std::shared_ptr<DrMuto000helper::header_info> sp2, std::vector<char> &toc_data);
/*
After all the trauma that the program went through in preparing the TOC file for futher use,
the user will then be asked what exactly are they going to do with it.
In practice it just gives the user two choices, both of which should kinda work I think? Errrrrrr...
*/
void parse_drmuto_toc(std::shared_ptr<DrMuto000helper::helper1> sp1, std::shared_ptr<DrMuto000helper::header_info> sp2, std::vector<char> &toc_data);
/*
After all the trauma that the program went through in preparing the TOC file for futher use,
the user will then be asked what exactly are they going to do with it.
In practice it just gives the user two choices, both of which should kinda work I think? Errrrrrr...
*/
void parse_drmuto_dir(std::shared_ptr<DrMuto000helper::helper1> sp1, std::shared_ptr<DrMuto000helper::header_info> sp2, std::shared_ptr<DrMuto000helper::toc_info> sp3, std::shared_ptr<DrMuto000helper::dir_name_info> sp4, std::vector<char> &toc_data, char current_dir_num);
/*
After all the trauma that the program went through in preparing the TOC file for futher use,
the user will then be asked what exactly are they going to do with it.
In practice it just gives the user two choices, both of which should kinda work I think? Errrrrrr...
*/
void parse_drmuto_file(std::shared_ptr<DrMuto000helper::helper1> sp1, std::shared_ptr<DrMuto000helper::header_info> sp2, std::shared_ptr<DrMuto000helper::toc_info> sp3, std::shared_ptr<DrMuto000helper::dir_name_info> sp4, std::shared_ptr<DrMuto000helper::file_info> sp5, std::vector<char>& toc_data, long file_info_pos, std::string input_name);

#endif _I_H_
