#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <memory>
#include <vector>
#include "1.hpp"

void choose_your_mode(std::shared_ptr<DrMuto000helper::helper1> sp1, std::shared_ptr<DrMuto000helper::header_info> sp2, std::vector<char> &toc_data)
{
	std::string typed_option[1]{ "" };

	std::cout << std::endl << std::setw(2) << "TOC file is now ready to be processed." << std::endl;
	std::cout << std::setw(2) << "There are currently two modes, though you can only type either one of them (without apostrophes)." << std::endl;
	std::cout << std::endl << std::setw(3) << " " << std::setw(2) << "'list'" << std::setw(10) << "-" << std::setw(3) << "prints out a list of all available entries and where are they stored into." << std::endl;
	std::cout << std::setw(3) << " " << std::setw(2) << " " << std::setw(10) << " " << std::setw(3) << "can be quite useful wen you're on the look-out for a certain file" << std::endl;
	std::cout << std::setw(3) << " " << std::setw(2) << " " << std::setw(10) << " " << std::setw(3) << "or you want to see what's inside those bigfiles for whatever reason." << std::endl;
	std::cout << std::endl << std::setw(3) << " " << std::setw(2) << "'x'" << std::setw(10) << "-" << std::setw(3) << "extracts all available entries into an specific folder." << std::endl;
	std::cout << std::setw(3) << " " << std::setw(2) << " " << std::setw(10) << " " << std::setw(3) << "said folder will be created on the spot, in the same location as the TOC file." << std::endl;
	std::cin >> typed_option[0];
	// (todo) if you're seeing the same function called two times, it's duplicate code. i'll try to optimize that code somehow so the same function gets called only once.
	if (typed_option[0] == "list")
	{
		sp1->option_level = 1;
		parse_drmuto_toc(sp1, sp2, toc_data);
	}
	else if (typed_option[0] == "x")
	{
		sp1->option_level = 2;
		parse_drmuto_toc(sp1, sp2, toc_data);
		/*
		if (typed_option[1] != "")
		{
			// todo
		}
		*/
	}
	else
	{
		std::cout << "Unknown mode: " << typed_option[0] << std::endl;
	}
}
