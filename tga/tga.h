#pragma once
#include "../util/fileutil.h"

typedef struct _TGA_HEADER
{
    uint32_t magic = 0x20000;
    uint32_t pad[2] = { 0, 0 };
    uint16_t width;
    uint16_t height;
    uint16_t twenty = 0x2020;
} TGA_HEADER;

class TGA
{
public:
	TGA();
	~TGA();

	uint8_t* getData();
	int32_t  getSize();
	uint32_t getWidth();
	uint32_t getHeight();
	uint32_t getNMipMaps();
	void save(const char* filename);
	void open(const char* filename);
	void create(uint32_t width, uint32_t height, uint8_t* data, int32_t dataSize);
private:
	void* file;
	TGA_HEADER* header;
	uint8_t* data;
	int32_t size;
	const int HEADER_SIZE = 0x12;
};