#include <iostream>

void display_case1_help_message()
{
	std::cout << std::endl << "The following arguments are as follows:" << std::endl;
	std::cout << " In the first argument, we have: " << std::endl;
	std::cout << "  [input file name] - for specifying the input file. " << std::endl;
	std::cout << "  [input folder name] - or you can just put in the input folder of where said file is in. " << std::endl;
	std::cout << std::endl << " Examples:" << std::endl;
	std::cout << "  Example 1 - DrMutoPackTool input.file " << std::endl;
	std::cout << "              input.file can mean any file that's stored on your storage drive. " << std::endl;
	std::cout << "  Example 2 - DrMutoPackTool /folder/to/file/ " << std::endl;
	std::cout << "              /folder/to/file/ can mean any folder that resides on your storage drive. " << std::endl;
}

void display_case2_help_message()
{
	display_case1_help_message();
	std::cout << std::endl << " You need to locate where DRMUTO.000 is." << std::endl;
	std::cout << " DRMUTO.000 is the TOC file that this program needs to be able to do basically anything useful with it. " << std::endl;
	std::cout << " Maybe that file resides somewhere on your storage drive (HDD or SSD), " << std::endl;
	std::cout << " maybe that file is in a folder you just so happened to move it into, or it's already there to begin with, " << std::endl;
	std::cout << " or, I don't know, maybe you have it somewhere? " << std::endl;
	std::cout << std::endl << " Anyway, if you know where DRMUTO.000 is, then you don't have to worry about using the program the 'wrong way'." << std::endl;
}


void display_case3_help_message()
{
	std::cout << std::endl << "How DrMutoPackTool works:" << std::endl;
	std::cout << " Just by specifying either the input file or the input folder as the first argument of the program, " << std::endl;
	std::cout << " it will then handle either of them no problem. " << std::endl;
	std::cout << std::endl << " After that point, it will operate on two modes: " << std::endl;
	std::cout << std::endl << "  Single-file mode - Triggered by specifying an input file. " << std::endl;
	std::cout << "                     The program will then make an internal list of file names " << std::endl;
	std::cout << "                     to see if the input file has a file name that it is looking for. " << std::endl;
	std::cout << "                     If the input file you specified just to happened to be a TOC file, " << std::endl;
	std::cout << "                     then it'll be loaded on the spot. " << std::endl;
	std::cout << "                     If not, the program will then look out for the it and will check if it's is present, " << std::endl;
	std::cout << "                     at which point it's going to get loaded anyway. " << std::endl;
	std::cout << std::endl << "  Directory mode - Triggered by specifying an input folder. " << std::endl;
	std::cout << "                   The program will then make an internal list of file names " << std::endl;
	std::cout << "                   to see if the input folder has whatever files are present on said list. " << std::endl;
	std::cout << "                   If said folder has all the files that the program is looking for, " << std::endl;
	std::cout << "                   then it will write out another list meant for easier loading of these files " << std::endl;
	std::cout << "                   when necessary. " << std::endl;
	std::cout << "                   One of the files that'll be loaded first is the TOC file. " << std::endl;
	std::cout << std::endl << " Anyway, for the first two modes at least, when either of them are active, " << std::endl;
	std::cout << " The program will then make an internal list of file names to see if " << std::endl;
	std::cout << " any of the files present on that list actually exist. " << std::endl;
	std::cout << std::endl << " On single-file mode, it will grab the name of the input file and " << std::endl;
	std::cout << " will then check if that name is actually present on the list. " << std::endl;
	std::cout << " If the name of the input file is indeed present on that list, " << std::endl;
	std::cout << " that means you picked a valid input file and you don't need to do anything. " << std::endl;
	std::cout << std::endl << " As for directory mode, it will check for the existence of the files " << std::endl;
	std::cout << " (as specified by that list) as they reside in the input folder you specified the program to. " << std::endl;
	std::cout << " If successful, then, again, you don't need to do anything. Your files are correct. " << std::endl;
	std::cout << std::endl << " Either way though, it will load the TOC file and will make whatever is necessary " << std::endl;
	std::cout << " to make sure that said file is fully read and understood. " << std::endl;
	std::cout << " From then on it give you two options - be it to extract all the files as specified in the TOC file, " << std::endl;
	std::cout << " or to just list them and print additional info from that file. " << std::endl;
	std::cout << " If you specify one of the two options to the program (whichever you prefer!), " << std::endl;
	std::cout << " then it will work to give you the option you want. That's it. " << std::endl;
}
