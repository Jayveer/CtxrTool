#pragma once
#include "../util/fileutil.h"

typedef enum _DDS_FLAGS
{
	DDSD_CAPS		 = 0x1,
	DDSD_HEIGHT		 = 0x2,
	DDSD_WIDTH		 = 0x4,
	DDSD_PITCH		 = 0x8,
	DDSD_PIXELFORMAT = 0x1000,
	DDSD_MIPMAPCOUNT = 0x20000,
	DDSD_LINEARSIZE	 = 0x80000,
	DDSD_DEPTH		 = 0x800000,
} DDS_FLAGS;

typedef enum _DDS_PIXELFORMAT_FLAGS
{
	DDPF_ALPHAPIXELS = 0x1,
	DDPF_ALPHA		 = 0x2,
	DDPF_FOURCC		 = 0x4,
	DDPF_RGB		 = 0x40,
	DDPF_YUV		 = 0x200,
	DDPF_LUMINANCE   = 0x20000
} DDS_PIXELFORMAT_FLAGS;

typedef struct _DDS_PIXELFORMAT
{
	uint32_t pxlFmtSize = 0x20;
	uint32_t flags = 0;
	uint32_t fourcc = 0;
	uint32_t bitCount = 0;
	uint32_t rBitmask = 0;
	uint32_t gBitmask = 0;
	uint32_t bBitmask = 0;
	uint32_t aBitmask = 0;
} DDS_PIXELFORMAT;

typedef enum _DDS_CAPS
{
	DDSCAPS_COMPLEX = 0x8,
	DDSCAPS_MIPMAP  = 0x400000,
	DDSCAPS_TEXTURE = 0x1000,
} DDS_CAPS;

typedef struct _DDS_HEADER
{
	uint32_t magic   = 0x20534444;
	uint32_t hdrSize = 0x7C;
	uint32_t flags;
	uint32_t height;
	uint32_t width;
	uint32_t pitch;
	uint32_t depth;
	uint32_t n_mipmaps;
	uint32_t reserved[11];
	DDS_PIXELFORMAT format;
	uint32_t caps;
	uint32_t caps2;
	uint32_t caps3;
	uint32_t caps4;
	uint32_t reserved2;
} DDS_HEADER;

class DDS
{
public:
	DDS();
	~DDS();

	uint8_t* getData();
	int32_t  getSize();
	uint32_t getWidth();
	uint32_t getHeight();
	uint32_t getNMipMaps();
	void save(const char *filename);
	void open(const char *filename);
	void create(uint32_t width, uint32_t height, uint32_t pitch, uint32_t n_mipmaps, uint32_t flags, uint8_t* data, int32_t dataSize);
private:
	void       *file;
	DDS_HEADER *header;
	uint8_t    *data;
	int32_t size;
	const int HEADER_SIZE = 0x80;
};