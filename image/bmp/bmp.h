#pragma once
#include "../../util/fileutil.h"
#include "../../util/imageutil.h"

#pragma pack(push, 1)
typedef struct tagBITMAPFILEHEADER {
	uint16_t type;
	uint32_t size;
	uint16_t Reserved1 = 0;
	uint16_t Reserved2 = 0;
	uint32_t offBits;
} BITMAPFILEHEADER;


typedef struct tagBITMAPINFOHEADER {
	uint32_t size;
	int32_t  width;
	int32_t  height;
	uint16_t planes;
	uint16_t bitCount;
	uint32_t compression;
	uint32_t sizeImage;
	int32_t  xPelsPerMeter = 2834;
	int32_t  yPelsPerMeter = 2834;
	uint32_t clrUsed;
	uint32_t clrImportant;
} BITMAPINFOHEADER;


typedef struct _BMP_HEADER {
	BITMAPFILEHEADER header;
	BITMAPINFOHEADER info;
} BMP_HEADER;
#pragma pack(pop)

class BMP
{
public:
	BMP();
	~BMP();

	void open(const char* filename);
	void save(const char* filename);
	void create(uint32_t width, uint32_t height, uint8_t* data, int32_t dataSize);

	int32_t  getSize();
	uint8_t* getData();
	uint32_t getWidth();
	uint32_t getHeight();
	uint32_t getNMipMaps();
	int32_t  getMainTextureSize();
	int64_t  getBlockSize(int32_t idx);
private:
	int32_t size;
	void* file;
	uint8_t* data;
	BMP_HEADER* header;
};