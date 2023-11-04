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
	header->version = _byteswap_ulong(7);
	header->width    = width;
	header->height   = height;
	header->width    = _byteswap_ushort(header->width);
	header->height   = _byteswap_ushort(header->height);
	header->depth	 = _byteswap_ushort(1);
	header->field_12 = _byteswap_ushort(0x100);

	//these are unknown, may be params that indiciate colour
	header->field_14 = 0;
	header->field_15 = 0;
	header->field_16 = 0;
	header->field_17 = 255;
	header->field_18 = 255;
	header->field_19 = 255;
	header->field_1A = 255;
	header->field_1B = 255;
	header->field_1C = 255;
	header->field_1D = 255;
	header->field_1E = 255;
	header->field_1F = 255;
	header->field_20 = 255;

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

int32_t CTXR::getMainTextureSize()
{
	int width  = _byteswap_ushort(header->width);
	int height = _byteswap_ushort(header->height);

	int a = std::max(1, (width +  3) / 4);
	int b = std::max(1, (height + 3) / 4);

	return a * b * 64;
}

bool CTXR::addParams(const char* filename)
{
	int i;
	uint8_t* param;
	std::string str;
	std::ifstream file(filename);

	if (!file) return false;

	param = &header->field_14;
	std::regex r("\\s+");

	i = 0;
	while (std::getline(file, str) || i < MAX_PARAM)
	{
		str = std::regex_replace(str, r, "");
		
		std::regex re(MATCH_PARAM);
		std::smatch match;

		if (std::regex_search(str, match, re))
		{
			int x = std::stoi(match[2]);
			param[i++] = std::clamp(x, 0, 255);
		}
	}

	file.close();
	return true;
}

void CTXR::saveParams(const char* filename)
{
	uint8_t *param;
	std::ofstream paramFile;
	paramFile.open(filename);

	param = &header->field_14;


	for (int i = 0; i < MAX_PARAM; i++)
	{
		int val = param[i];
		paramFile << "Param_" << i << " = " << std::clamp(val, 0, 255) << "\n";
	}

	paramFile.close();
}

void CTXR::saveMipMaps(const char* filename, std::string &output, uint32_t filePtr)
{
	uint32_t chunkSize = getMainTextureSize() / 4;

	for (; chunkSize >= 4;)
	{
		uint8_t* copy;
		uint32_t align;

		copy = new uint8_t[getMainTextureSize()];

		chunkSize = _byteswap_ulong(chunkSize);
		writeDataToFile((uint8_t*)&chunkSize, 4, filename, output, true);
		chunkSize = _byteswap_ulong(chunkSize);
		filePtr += 0x4;

		resample(data, copy, getWidth(), getHeight(), getWidth() / (header->n_mipmaps * 2), getHeight() / (header->n_mipmaps * 2));

		writeDataToFile(copy, chunkSize, filename, output, true);
		filePtr += chunkSize;
		header->n_mipmaps++;

		delete[] copy;

		align = writeAlignment(filename, output, filePtr, 0x20);
		filePtr += align;

		chunkSize /= 4;

		if (chunkSize > 1 && chunkSize < 4) chunkSize = 4;
	}

	overwriteDataInFile((uint8_t*)header, 0x80, filename, output);
}

void CTXR::save(const char* filename, bool generateMipMaps)
{
	uint32_t align;
	uint32_t filePtr;
	uint32_t chunkSize;
	std::string output = "";	

	filePtr = 0;
	header->n_mipmaps = 1;
	chunkSize = getMainTextureSize();

	//write header
	writeDataToFile((uint8_t*)header, 0x80, filename, output);
	filePtr += 0x80;

	//write size
	chunkSize = _byteswap_ulong(chunkSize);
	writeDataToFile((uint8_t*)&chunkSize, 4, filename, output, true);
	chunkSize = _byteswap_ulong(chunkSize);
	filePtr += 0x4;

	//write data
	writeDataToFile(data, chunkSize, filename, output, true);
	filePtr += chunkSize;

	//write alignment
	align = writeAlignment(filename, output, filePtr, 0x20);
	filePtr += align;

	if (generateMipMaps) saveMipMaps(filename, output, filePtr);
}

//save with user mipmaps
void CTXR::saveExtend(const char* filename)
{
	uint32_t align;
	uint32_t filePtr;
	uint32_t dataPtr;
	uint32_t chunkSize;
	std::string output = "";

	chunkSize = getMainTextureSize();
	writeDataToFile((uint8_t*)header, 0x80, filename, output);

	dataPtr = 0x0;
	filePtr = 0x80;

	for (int i = 0; i < header->n_mipmaps; i++)
	{
		chunkSize = _byteswap_ulong(chunkSize);
		writeDataToFile((uint8_t*)&chunkSize, 4, filename, output, true);
		chunkSize = _byteswap_ulong(chunkSize);

		writeDataToFile(&data[dataPtr], chunkSize, filename, output, true);
		dataPtr += chunkSize;
		filePtr += chunkSize + 4;

		align = writeAlignment(filename, output, filePtr, 0x20);
		filePtr += align;

		chunkSize /= 4;
	}
}