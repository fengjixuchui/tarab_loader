#pragma once
#include <thread>
#include <chrono>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

#include "client.h"
#include "utils.h"

class mmap {
	uint32_t pid;
	std::map<std::string, uint64_t> imports;
	uint8_t* raw_data;
	size_t data_size;

public:
	bool attach_to_process(const char* process_name);
	bool load_dll(uint8_t file[]);
	bool inject();

private:
	uint64_t* get_ptr_from_rva(uint64_t rva, IMAGE_NT_HEADERS* nt_header, uint8_t* image_base);
	PIMAGE_SECTION_HEADER get_enclosing_section_header(uint64_t rva, PIMAGE_NT_HEADERS nt_header);

	void solve_imports(uint8_t* base, IMAGE_NT_HEADERS* nt_header, IMAGE_IMPORT_DESCRIPTOR* impDesc);
	void solve_relocations(uint64_t base, uint64_t relocation_base, IMAGE_NT_HEADERS* nt_header, IMAGE_BASE_RELOCATION* reloc, size_t size);
	void map_pe_sections(uint64_t base, IMAGE_NT_HEADERS* nt_header);


	uint64_t get_proc_address(char* module_name, char* func);
	bool parse_imports();
};

