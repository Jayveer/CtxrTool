#pragma once
#include <algorithm>
#include <regex>
#include "../../util/fileutil.h"
#include "../../util/imageutil.h"

#define MAX_PARAM 13
#define MATCH_PARAM "(.*)=(.*)"


typedef enum _CTXR_GTT
{
	kGTT_White,
	kGTT_Grey,
	kGTT_Black,
	kGTT_FlatNormal,
	kGTT_SpecularPower
} CTXR_GTT;

typedef enum _CTXR_AA
{
	kAA_None,
	kAA_MSAA2x,
	kAA_MSAA4x,
	kAA_Count,
	kAA_Invalid = 0xFFFFFFFF
} CTXR_AA;

typedef enum _CTXR_USAGE
{
	kUsage_Texture,
	kUsage_TextureLinear,
	kUsage_RenderTarget,
	kUsage_DepthBuffer
} _CTXR_USAGE;

typedef enum _CTXR_TYPE
{
	kType_Normal,
	kType_Cube
} CTXR_TYPE;


typedef enum _CTXR_FORMAT
{
  kFormat_A8R8G8B8		= 0x0,
  kFormat_A16B16G16R16F = 0x2,
  kFormat_R32F			= 0x3,
  kFormat_D24X8			= 0x4,
  kFormat_DXT1			= 0x5,
  kFormat_DXT3			= 0x6,
  kFormat_DXT5			= 0x7,
  kFormat_A32B32G32R32F = 0x8,
  kFormat_Luminance8	= 0x9,
  kFormat_D24FS8		= 0xA,
  kFormat_Count			= 0xB,
  kFormat_Invalid		= 0xFFFFFFFF
} CTXR_FORMAT;

#pragma pack(push, 1)
typedef struct _CTXR_HEADER
{
	uint32_t magic    = 0x52545854;
	uint32_t version  = 7;
	uint16_t width;
	uint16_t height;
	uint16_t depth;
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
	uint32_t padding[22];
} CTXR_HEADER;
#pragma pack(pop)

class CTXR
{
	public:
		CTXR();
		~CTXR();

		void open(const char* filename);
		void saveExtend(const char* filename);
		bool addParams(const char* filename);
		void saveParams(const char* filename);
		void save(const char* filename, bool generateMipMaps = true);
		void saveMipMaps(const char* filename, std::string& output, uint32_t filePtr);
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