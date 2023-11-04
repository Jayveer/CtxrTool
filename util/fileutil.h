#pragma once
#include <fstream>
#include <filesystem>

inline
void updateDir(const std::string& path, std::string& output) {
	std::filesystem::path p{ output };
	p.append(path);
	output = p.u8string();
}

inline
void resetDir(std::string& output) {
	std::filesystem::path p{ output };
	output = p.parent_path().u8string();
}

inline
std::string getCurrentDir(const std::string& output) {
	std::filesystem::path p{ output };
	return p.filename().u8string();
}

inline
std::string getExtension(const std::string& output) {
	std::filesystem::path p{ output };
	return p.extension().u8string();
}

inline
std::string getExtensionlessName(const std::string& output) {
	std::filesystem::path p{ output };
	return p.stem().u8string();
}

inline
bool filenameContainsString(const std::string& output, const std::string& string) {
	std::string filename = getExtensionlessName(output);

	if (filename.find(string) != std::string::npos)
		return true;

	return false;
}

inline
bool isDirectory(const std::string& output) {
	std::filesystem::path p{ output };
	return std::filesystem::is_directory(p);
}

inline
bool fileExists(const std::string& output) {
	std::filesystem::path p{ output };
	return std::filesystem::exists(p);
}

inline
int64_t getFileSize(const std::string& input) {
	return std::filesystem::file_size(input);
}

inline
int64_t getAlignment(int64_t currentOffset, int64_t alignSize) {
	uint64_t step = (alignSize - (currentOffset % alignSize));
	if (step != alignSize)
		return step;
	return 0;
}

inline
void writeDataToFile(uint8_t* data, int size, const std::string& filename, std::string& output, bool append = false) {
	if (!std::filesystem::exists(output) && output != "")
		std::filesystem::create_directories(output);

	std::ofstream ofs;
	updateDir(filename, output);
	append ? ofs.open(output, std::ofstream::binary | std::ios_base::app) : ofs.open(output, std::ofstream::binary);

	ofs.write((char*)data, size);
	ofs.close();
	resetDir(output);
}

inline
void overwriteDataInFile(uint8_t* data, int size, const std::string& filename, std::string& output) {
	if (!std::filesystem::exists(output) && output != "")
		std::filesystem::create_directories(output);

	std::ofstream ofs;
	updateDir(filename, output);
	ofs.open(output, std::ofstream::in | std::ofstream::binary);

	ofs.write((char*)data, size);
	ofs.close();
	resetDir(output);
}

inline
int32_t writeAlignment(const std::string& filename, std::string& output, uint32_t pos, int64_t alignSize) {
	uint8_t* zero;
	uint32_t align;

	align = getAlignment(pos, alignSize);
	zero = new uint8_t[align];
	memset(zero, 0, align);
	writeDataToFile(zero, align, filename, output, true);
	delete[] zero;

	return align;
}


inline
void writeZeroesToFile(int size, const std::string& filename, std::string& output) {
	if (!std::filesystem::exists(output) && output != "")
		std::filesystem::create_directories(output);

	std::ofstream ofs;
	uint8_t *zero = new uint8_t[size];
	updateDir(filename, output);
	ofs.open(output, std::ofstream::binary | std::ios_base::app);

	ofs.write((char*)zero, size);
	ofs.close();
	delete[] zero;
	resetDir(output);
}

inline
void* loadFile(const char* filename, int* size)
{
	std::ifstream fs;
	*size = std::filesystem::file_size(filename);

	fs.open(filename, std::ios::binary);
	uint8_t* p = new uint8_t[*size];
	fs.read((char*)p, *size);
	fs.close();

	return p;
}
