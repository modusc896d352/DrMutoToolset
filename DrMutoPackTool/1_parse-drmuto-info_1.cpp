#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <memory>
#include <ostream>
#include <vector>
#include "1.hpp"

long r_ffunc::decompress_drmuto_block(std::vector<char> &input_data, long target_input_size, std::vector<char> &output_data, long target_output_size, long &inp_var5, long &inp_var6, long *inp_var7)
{
    //input_file.read(input_data, target_input_size);
    long fc_bl1_sz{ target_input_size }; // size for compressed (input) data, now in a separate variable
    long fc_inp_o{ 0 }; // offset for compressed (input) data
    long fc_inp_o1 = fc_inp_o; // duplicate of the above
    long fc_inp_o2 = fc_inp_o; // duplicate of the above
    long fc_bl2_o{ 0 }; // offset for decompressed data
    long fc_bl2_o1 = fc_bl2_o; // duplicate of the above
    char fc_cf{ 0 }; // control flag meant to help with uploading decompressed data (to a memory block), in practice just a counter that starts from 8 and ends in zero.
    unsigned char fc_nb1{ 0 }, fc_nb2{ 0 }, fc_nb3{ 0 }, fc_nb4{ 0 }, fc_nb5{ 0 }; // "nb" being "new byte"
    unsigned char fc_nb1a{ 0 }; // "a" being "alternative"
    long fc_nl1{ 0 }, fc_nl2{ 0 }, fc_nl3{ 0 }, fc_nl4{ 0 }, fc_nl5{ 0 }, fc_nl6{ 0 }; // "nl" being "new long"
    while ((inp_var7 == 0) || ((*inp_var7 & 0x10000000) == 0))
    {
        fc_inp_o1 = fc_inp_o;
        if (fc_cf == 0)
        {
            fc_inp_o1++;
            fc_nb1 = r_ffunc::read_u8_from_mem(fc_inp_o, input_data);
            fc_cf = 8;
        }
        fc_nb1a = fc_nb1;
        fc_cf--;
        if ((fc_nb1a & 1) == 0)
        {
            fc_nb2 = r_ffunc::read_u8_from_mem(fc_inp_o1, input_data);
            fc_nb3 = r_ffunc::read_u8_from_mem((fc_inp_o1 + 1), input_data);
            fc_inp_o1 += 2;
            fc_inp_o = fc_inp_o1;
            fc_nl1 = ((fc_nb2 & 0xf0) << 4) | fc_nb3;
            fc_nl2 = fc_nb2 & 0xf;
            if ((fc_nl1 | fc_nl2) == 0)
            {
                inp_var5 = fc_inp_o2 + (target_input_size - fc_inp_o1);
                inp_var6 = fc_bl2_o1 - fc_bl2_o;
                auto inp_var8 = (target_output_size != (fc_bl2_o1 - fc_bl2_o));
                fc_nl4 = 0x100;
                if ((inp_var5 != 0) || ((fc_nl4 == 0x100) && (target_output_size != (fc_bl2_o1 - fc_bl2_o))))
                {
                    fc_nl4 = 6;
                }
                return fc_nl4;
            }
            fc_nl5 = fc_nl2 + 1;
            fc_nl6 = fc_bl2_o1 + -fc_nl1;
            do
            {
                fc_nb5 = r_ffunc::read_u8_from_mem(fc_nl6, output_data);
                r_ffunc::put_u8_to_mem(fc_nb5, fc_bl2_o1, output_data);
                fc_nl6++;
                fc_bl2_o1++;
                fc_nl5--;

            } while (fc_nl5 != -1);
        }
        else {
            fc_nb4 = r_ffunc::read_u8_from_mem(fc_inp_o1, input_data);
            r_ffunc::put_u8_to_mem(fc_nb4, fc_bl2_o1, output_data);
            fc_inp_o1++;
            fc_bl2_o1++;
            fc_inp_o = fc_inp_o1;
        }
        fc_nb1 = fc_nb1a >> 1;
    }
    inp_var6 = fc_bl2_o1 - fc_bl2_o;
    return 10;
}

void r_ffunc::extract_file_data(std::shared_ptr<DrMuto000helper::helper1> sp1, std::string input_name, long file_offset, long file_size, long part_number)
{
    bool ok1{ false }, ok2{ false }, ok3{ false }, ok4{ false };
    std::ifstream target_input_file;
    std::ofstream target_output_file;
    std::string output_file_name{ "" };
    short block_size{ 2048 };
    long file_blocks{ 0 };
    long last_block{ 0 };
    long remaining_size{ 0 };
    long modulus{ 0 };
    long output_file_offset{ 0 };
    long bytes_left_to_write{ file_size };

    output_file_name.append(sp1->output_folder_path);
    output_file_name.append(input_name);
    if (sp1->part_file_exists[part_number] == true)
    {
        ok1 = true;
    }
    if (ok1 == true)
    {
        target_input_file.open(sp1->actual_part_name[part_number], std::ios_base::in | std::ios_base::binary | std::ios_base::ate, _SH_DENYRD);
        if (target_input_file.is_open())
        {
            ok2 = true;
        }
        if (ok2 == true)
        {
            target_output_file.open(output_file_name, std::ios_base::out | std::ios_base::binary | std::ios_base::app, _SH_DENYWR);
            if (target_output_file.is_open())
            {
                ok3 = true;
            }
            if (ok3 == true)
            {
                file_blocks = file_size / block_size;
                remaining_size = file_size - (file_blocks * block_size);
                modulus = block_size - remaining_size;
                if (modulus != 0x800) file_blocks++;
                last_block = (file_blocks - 1);
                for (long i1 = 0; i1 < file_blocks; i1++)
                {
                    ok4 = false;
                    if (file_offset == sp1->part_size[part_number])
                    {
                        target_input_file.close();
                        part_number++;
                        file_offset = 0;
                        switch (sp1->part_file_exists[part_number])
                        {
                        case true:
                            ok4 = true;
                            break;
                        case false:
                            std::cout << std::endl << "Seems like we've reached a limit." << std::endl;
                            std::cout
                                << "The file we're trying to extract to (" << input_name << ") needs about "
                                << std::dec
                                << std::nouppercase
                                << bytes_left_to_write
                                << " bytes left to be fully extracted,"
                                << std::endl;
                            std::cout
                                << "and yet the bigfile ("
                                << sp1->part_name[part_number]
                                << ") that holds said file is simply not present."
                                << std::endl;
                            break;
                        }
                        if (ok4 == true)
                        {
                            target_input_file.open(sp1->actual_part_name[part_number], std::ios_base::in | std::ios_base::binary | std::ios_base::ate, _SH_DENYRD);
                        }
                    }
                    if (sp1->part_file_exists[part_number] == false)
                    {
                        break;
                    }
                    if (i1 == last_block)
                    {
                        // ugly hack to ensure that certain files ("/audio/ui.mbx" in particular) don't come away empty.
                        if (modulus != 0x800)
                        {
                            block_size = (short)remaining_size;
                        }
                        else
                        {
                            block_size = (short)modulus;
                        }
                    }
                    target_input_file.seekg(file_offset, std::ios_base::beg);
                    std::vector<char> file_block(block_size);
                    target_input_file.read(reinterpret_cast<char*>(file_block.data()), block_size);
                    file_offset += block_size;
                    target_output_file.seekp(output_file_offset, std::ios_base::beg);
                    target_output_file.write(reinterpret_cast<char*>(file_block.data()), block_size);
                    output_file_offset += block_size;
                    bytes_left_to_write -= block_size;
                }
                if (bytes_left_to_write == 0)
                {
                    std::cout << "Current file (" << input_name << ") is now extracted. " << std::endl;
                }
            }
        }
    }
}
