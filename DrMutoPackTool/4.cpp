#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <memory>
#include <vector>
#include "1.hpp"

void start_work_on_everything(std::shared_ptr<DrMuto000helper::helper1> sp1)
{
	std::ifstream toc_file;
	std::shared_ptr<DrMuto000helper::header_info> sp2 = std::make_shared<DrMuto000helper::header_info>();
	long result1{ 0 }, result2{ 0 };
	long blck2_result{ 0 }, blck2_asz{ 0 }, blck4_result{ 0 }, blck4_asz{ 0 }; // "asz" being "actual size"
	if (sp1->part_file_exists[0] == true)
	{
		toc_file.open(sp1->actual_part_name[0], std::ios_base::in | std::ios_base::binary | std::ios_base::ate, _SH_DENYRD);
		toc_file.seekg(sp1->part_offset[0], std::ios_base::beg);
		unsigned char blck1_presize = r_ffunc::read_u8(0, toc_file);
		long temp_offset = (sp1->part_offset[0] + 1);
		toc_file.seekg(temp_offset, std::ios_base::beg);
		std::vector<char> blck1(blck1_presize);
		toc_file.read(reinterpret_cast<char*>(blck1.data()), blck1_presize);
		std::vector<char> blck2(20);
		result1 = r_ffunc::decompress_drmuto_block(blck1, (long)blck1_presize, blck2, 0x14, blck2_result, blck2_asz, 0);
		sp1->part_offset[0] += (1 + blck1_presize);
		if ((result1 == 0x100) && (blck2_result == 0) && (blck2_asz == 0x14))
		{
			long calc1{ 0 }, calc2{ 0 }, calc3{ 0 }, decompressed_toc_size{ 0 }, compressed_toc_size{ 0 };
			sp2->num_parts = r_ffunc::read_s32le_from_mem(0,blck2);
			sp2->avg_part_size = r_ffunc::read_s32le_from_mem(4,blck2);
			sp2->num_files = r_ffunc::read_s32le_from_mem(8,blck2);
			sp2->num_dirs = r_ffunc::read_s32le_from_mem(12,blck2);
			sp2->entry_name_depot_size = r_ffunc::read_s32le_from_mem(16,blck2);
			calc1 = sp2->num_files * 12;
			calc2 = sp2->num_dirs << 2;
			calc3 = calc2 + sp2->entry_name_depot_size;
			decompressed_toc_size = calc3 + calc1;
			compressed_toc_size = (long)sp1->part_size[0] - sp1->part_offset[0];
			sp2->entry_info_section1_offset = 0;
			sp2->entry_info_section1_size = calc1;
			sp2->entry_info_section2_section1_offset = calc1;
			sp2->entry_info_section2_section2_offset = calc1 + calc2;
			sp2->entry_info_section2_size = calc3;
			toc_file.seekg(sp1->part_offset[0], std::ios_base::beg);
			std::vector<char> blck3(compressed_toc_size);
			toc_file.read(reinterpret_cast<char*>(blck3.data()), compressed_toc_size);
			sp1->part_offset[0] += compressed_toc_size;
			std::vector<char> blck4(decompressed_toc_size);
			result2 = r_ffunc::decompress_drmuto_block(blck3, compressed_toc_size, blck4, decompressed_toc_size, blck4_result, blck4_asz, 0);
			// (todo) destroy blck3 as we no longer see any use for it.
			choose_your_mode(sp1, sp2, blck4);
		}
	}
}
