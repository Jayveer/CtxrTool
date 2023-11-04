#pragma once
#include "../../util/fileutil.h"

#pragma pack(push, 1)
typedef struct _TGA_HEADER
{
    uint32_t magic = 0x20000;			//0x00
	uint32_t colourMapSpec;				//0x04
	uint16_t xOffset;					//0x08
	uint16_t yOffset;					//0x0A
    uint16_t width;						//0x0C
    uint16_t height;					//0x0E
    uint8_t  bpp = 0x20;				//0x10
	uint8_t  descriptor = 0x20;			//0x10
} TGA_HEADER;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct _TGA_FOOTER
{
	uint32_t extOffset = 0;							//0x00
	uint32_t devOffset = 0;							//0x04
	char signature[18] = "TRUEVISION-XFILE.";		//0x0C
} TGA_FOOTER;
#pragma pack(pop)


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

	bool isFlipped();
	void save(const char* filename);
	void open(const char* filename);
	void create(uint32_t width, uint32_t height, uint8_t* data, int32_t dataSize);
private:
	void* file;
	TGA_HEADER* header;
	TGA_FOOTER* footer;
	uint8_t* data;
	int32_t size;
	const int HEADER_SIZE = 0x12;
};