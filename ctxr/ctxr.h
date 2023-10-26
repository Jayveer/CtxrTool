#pragma once
#include <algorithm>
#include <regex>
#include "../util/fileutil.h"

#define MAX_PARAM 13
#define MATCH_PARAM "(.*)=(.*)"

typedef struct _CTXR_HEADER
{
	uint32_t magic    = 0x52545854;
	uint32_t field_04 = 07;
	uint16_t width;
	uint16_t height;
	uint16_t field_0C;
	uint16_t field_0E;
	uint16_t field_10;
	uint16_t field_12;
	uint8_t  field_14;
	uint8_t  field_15;
	uint8_t  field_16;
	uint8_t  field_17;
	uint8_t  field_18;
	uint8_t  field_19;
	uint8_t  field_1A;
	uint8_t  field_1B;
	uint8_t  field_1C;
	uint8_t  field_1D;
	uint8_t  field_1E;
	uint8_t  field_1F;
	uint8_t  field_20;
	uint8_t  field_21;
	uint8_t  field_22;
	uint8_t  field_23;
	uint8_t  field_24;
	uint8_t  field_25;
	uint8_t  n_mipmaps;
	uint8_t  field_27;
	uint8_t  field_28;
	uint32_t padding[21];
} CTXR_HEADER;


class CTXR
{
	public:
		CTXR();
		~CTXR();

		void open(const char* filename);
		void save(const char* filename);
		void saveExtend(const char* filename);
		bool addParams(const char* filename);
		void saveParams(const char* filename);
		void create(uint32_t width, uint32_t height, uint32_t n_mipmaps, uint8_t* data, int32_t dataSize);

		int32_t  getSize();
		uint8_t *getData();
		uint32_t getWidth();
		uint32_t getHeight();
		uint32_t getNMipMaps();
		int32_t  getMainTextureSize();
		int64_t  getBlockSize(int32_t idx);
	private:
		int32_t		 size;
		void		*file;
		uint8_t		*data;
		CTXR_HEADER *header;

};