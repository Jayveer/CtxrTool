#pragma once
#include "../tga/tga.h"
#include "../dds/dds.h"
#include "../ctxr/ctxr.h"
#include "../util/fileutil.h"

typedef enum CLI_FILETYPE
{
	CTXR_FILE,
	DDS_FILE,
	TGA_FILE
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
		const char* version;
		const char* programName;
		const char* EXIT_MESSAGE  = "Exiting\n";
		const char* USAGE_MESSAGE = "USAGE:\t	Convert CTXR to DDS\n \
	\tCtxrTool.exe <example_file.ctxr>\n \
	\n \
	\tConvert CTXR to TGA\n \
	\tCtxrTool.exe <example_file.ctxr> tga\n \
	\n \
	\tConvert DDS to CTXR\n \
	\tCtxrTool.exe <example_file.dds>\n";

		void printUsage();
		bool checkInput();
		void processArgs();
		void printWelcome();

		void convertDDS();
		void convertCTXR();

		void setInputType();
		void setOutputType();

		CLI_FILETYPE inputType  = CTXR_FILE;
		CLI_FILETYPE outputType = DDS_FILE;
};