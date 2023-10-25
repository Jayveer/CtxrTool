#include "ctxr.h"

CTXR::CTXR()
{

}


CTXR::~CTXR()
{
	if (file) delete[] file;
}


void CTXR::open(const char* filename)
{
	file   = loadFile(filename, &size);
	header = (CTXR_HEADER*)file;
	data   = (uint8_t*)&header[1];
}

void CTXR::create(uint32_t width, uint32_t height, uint32_t n_mipmaps, uint8_t *data, int32_t dataSize)
{
	file = new uint8_t[0x80];

	memset(file, 0, 0x80);
	header = (CTXR_HEADER*)file;

	header->magic    = 0x52545854;
	header->field_04 = _byteswap_ulong(7);
	header->width    = width;
	header->height   = height;
	header->width    = _byteswap_ushort(header->width);
	header->height   = _byteswap_ushort(header->height);
	header->field_0C = _byteswap_ushort(1);
	header->field_12 = _byteswap_ushort(0x100);

	header->n_mipmaps = n_mipmaps;

	this->data = data;
	size = dataSize + 0x80;

}

uint32_t CTXR::getWidth()
{
	return _byteswap_ushort(header->width);
}

uint32_t CTXR::getHeight()
{
	return _byteswap_ushort(header->height);
}

uint32_t CTXR::getNMipMaps()
{
	return header->n_mipmaps;
}

uint8_t* CTXR::getData()
{
	return data;
}

int32_t CTXR::getSize()
{
	return size;
}

void CTXR::save(const char* filename)
{
	std::string output = "";
	writeDataToFile((uint8_t*)header, 0x80, filename, output);
	writeDataToFile(data, size - 0x80, filename, output, true);
}

//needed when dds data omits chunk size
void CTXR::saveExtend(const char* filename)
{
	uint8_t* zero;
	uint32_t align;
	uint32_t filePtr;
	uint32_t dataPtr;
	uint32_t chunkSize;
	std::string output = "";

	writeDataToFile((uint8_t*)header, 0x80, filename, output);
	filePtr = 0x80;
	
	chunkSize = *(uint32_t*)data;
	chunkSize = _byteswap_ulong(chunkSize);
	writeDataToFile(data, chunkSize + 4, filename, output, true);
	dataPtr = chunkSize + 4;
	filePtr += dataPtr;

	align = getAlignment(filePtr, 0x20);

	zero = new uint8_t[align];
	memset(zero, 0, align);
	writeDataToFile(zero, align, filename, output, true);
	delete[] zero;
	filePtr += align;

	for (int i = 0; i < header->n_mipmaps - 1; i++)
	{
		chunkSize /= 4;
		chunkSize = _byteswap_ulong(chunkSize);
		writeDataToFile((uint8_t*)&chunkSize, 4, filename, output, true);
		chunkSize = _byteswap_ulong(chunkSize);

		writeDataToFile(&data[dataPtr], chunkSize, filename, output, true);
		dataPtr += chunkSize;
		filePtr += chunkSize + 4;

		align = getAlignment(filePtr, 0x20);
		zero = new uint8_t[align];
		memset(zero, 0, align);
		writeDataToFile(zero, align, filename, output, true);
		delete[] zero;
		filePtr += align;
	}

	int x = 0;
}