#pragma once
#include "../image/bmp/bmp.h"
#include "../image/tga/tga.h"
#include "../image/dds/dds.h"
#include "../image/ctxr/ctxr.h"
#include "../util/fileutil.h"

typedef enum CLI_FILETYPE
{
	CTXR_FILE,
	DDS_FILE,
	TGA_FILE,
	BMP_FILE,
	UNSUPPORTED_FILE
} CLI_FILETYPE;

class CLI 
{

	public:
		CLI(int argc, char** argv);
		~CLI();

		void run(const char* programName, const char* version);
		void exit();
	private:
		int argc;
		char** argv;
		int currentArg = 1;
		const char* version;
		const char* programName;
		const char* EXIT_MESSAGE  = "Exiting\n";
		const char* USAGE_MESSAGE = "USAGE:\t	Convert CTXR to DDS\n \
	\tCtxrTool.exe <example_file.ctxr>\n \
	\n \
	\tConvert CTXR to TGA\n \
	\tCtxrTool.exe <example_file.ctxr> -f tga\n \
	\n \
	\tConvert CTXR to BMP\n \
	\tCtxrTool.exe <example_file.ctxr> -f bmp\n \
	\n \
	\tConvert DDS to CTXR\n \
	\tCtxrTool.exe <example_file.dds>\n \
	\n \
	\tConvert TGA to CTXR\n \
	\tCtxrTool.exe <example_file.tga>\n \
	\n \
	\tConvert BMP to CTXR\n \
	\tCtxrTool.exe <example_file.bmp>\n \
	\n \
	\tConvert BMP or TGA to CTXR without mip maps\n \
	\tCtxrTool.exe <example_file.(bmp|tga)> -m no\n";
		void printUsage();
		bool checkInput();
		void processArgs();
		void printWelcome();
		void processCommands();
		bool isCommand(char* arg);

		void convertDDS();
		void convertTGA();
		void convertBMP();
		void convertCTXR();

		void exec();
		void setInputType();
		void setGenMipMaps(char* arg);
		void setOutputType(char *arg);
		void setCommand(char* arg, char* val);

		bool generateMipMaps = true;
		CLI_FILETYPE inputType  = CTXR_FILE;
		CLI_FILETYPE outputType = DDS_FILE;
};