#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include "1.hpp"

int main(int argc, char* argv[])
{
	std::cout << "DrMutoPackTool (v0)" << std::endl;

	/* how many arguments this program currently has. */
	int arg_count{ 0 };
	/* the thing that serves as the program's first argument. */
	std::string input_name{""};
	/* how many substance these arguments currently have. */
	std::string arguments[16]{ "" };
	/* a trigger for if the user is having trouble using the tool. */
	bool help_message_enabled{ false };
	/* an lever that dictates how much help text is fed to the user. */
	char help_level{ 0 };
	/* wanna use an struct or an class across various functions? this is how. */
	std::shared_ptr<DrMuto000helper::helper1> p2_up1 = std::make_shared<DrMuto000helper::helper1>();

	for (arg_count = 1; arg_count < argc; arg_count++)
	{
		arguments[arg_count] = argv[arg_count];
		if (arg_count == 1)
		{
			if (arguments[arg_count] == "help")
			{
				help_message_enabled = true;
				help_level = 1;
			}
			else if (arguments[arg_count] == "more-help")
			{
				help_message_enabled = true;
				help_level = 2;
			}
			else if (arguments[arg_count] == "behind-the-scenes")
			{
				help_message_enabled = true;
				help_level = 3;
			}
			else
			{
				input_name = arguments[arg_count];
			}
		}
	}
	/* how many arguments this program expects to take. */
	long expected_arguments{ 1 };
	/* how many arguments this program has actually gotten. */
	long got_these_args{ arg_count - 1 };
	/*
	a stand-in for a word that can change itself to plural adjective
	depending on how many arguments this program expects to take.
	*/
	const char* arg_word = "";
	if (expected_arguments == 1) {
		arg_word = "argument";
	}
	else if (expected_arguments >= 2) {
		arg_word = "arguments";
	}
	fill_drmuto_info1(p2_up1);
	switch (arg_count)
	{
	case 0:
		goto finish;
		break;
	case 1:
		goto help_message;
		break;
	case 2:
		if (help_message_enabled == false) {
			auto temp2 = input_name.c_str();
			std::u8string temp3{ reinterpret_cast<const char8_t*>(temp2) };
			detect_input_name_v1(temp3, p2_up1);
			start_work_on_everything(p2_up1);
		}
		else {
			switch (help_level) {
			case 1:
				display_case1_help_message();
				break;
			case 2:
				display_case2_help_message();
				break;
			case 3:
				display_case3_help_message();
				break;
			default:
				break;
			}
		}
		goto finish;
		break;
	default:
		goto unk_args;
		break;
	}
/* if the user has only typed DrMutoPackTool on the command-line terminal and pressed enter. */
help_message:
	std::cout << std::endl << " Just in case you don't know what to do here, type 'help' (without apostrophes), like this: " << std::endl;
	std::cout << " DrMutoPackTool help " << std::endl;
	std::cout << std::endl << " Or 'more-help' if you want to know more, like this: " << std::endl;
	std::cout << " DrMutoPackTool more-help " << std::endl;
	std::cout << std::endl << " If you're curious about the ins-and-outs of this tool, type 'behind-the-scenes', like this: " << std::endl;
	std::cout << " DrMutoPackTool behind-the-scenes " << std::endl;
	goto finish;
/* if the user types in more arguments than necessary or is just straight-up dumb with it. */
unk_args:
	std::cout << std::endl << " Expected " << expected_arguments << " " << arg_word << ", got " << got_these_args << " instead. " << std::endl;
	std::cout << " If you just want the in-game assets, " << std::endl;
	std::cout << " just specify the input file or the input folder and press enter. " << std::endl;
	goto finish;
/* if this program decides we're done here, we're done. */
finish:
	return 0;
}
