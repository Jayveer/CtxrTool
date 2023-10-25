#include "cli.h"

CLI::CLI(int argc, char** argv)
{
	this->argc = argc;
	this->argv = argv;
}

CLI::~CLI()
{

}

void CLI::convertCTXR()
{
	CTXR ctxr;
	ctxr.open(argv[1]);

	DDS dds;

	uint32_t flags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PITCH | DDSD_PIXELFORMAT | DDSD_MIPMAPCOUNT;

	dds.create(ctxr.getWidth(), ctxr.getHeight(), 0, ctxr.getNMipMaps(), flags, ctxr.getData(), ctxr.getSize() - 0x80);
	std::string outFilename = getExtensionlessName(argv[1]) + ".dds";
	dds.save(outFilename.c_str());
}


void CLI::convertDDS()
{
	DDS dds;

	dds.open(argv[1]);

	CTXR ctxr;
	ctxr.create(dds.getWidth(), dds.getHeight(), dds.getNMipMaps(), dds.getData(), dds.getSize() - 0x80);
	std::string outFilename = getExtensionlessName(argv[1]) + ".ctxr";
	ctxr.saveExtend(outFilename.c_str());
}

void CLI::processArgs() 
{
	std::string ext = getExtension(argv[1]);

	if (ext == ".dds")
	{
		convertDDS();
	}
	else if (ext == ".ctxr")
	{
		convertCTXR();
	}
	else
	{
		printf("Unsupported file type");
	}
}

void CLI::run(const char* programName, const char* version) {
	this->version = version;
	this->programName = programName;

	printWelcome();
	if (!checkInput()) return;
	processArgs();
}

void CLI::printWelcome() {
	printf("Running %s v%s: Visit https://github.com/Jayveer/CtxrTool for updates:\n", programName, version);
}

bool CLI::checkInput() {
	if (argc > 1 && argc < 3) return true;
	printUsage();
	return false;
}

void CLI::printUsage() {
	printf(this->USAGE_MESSAGE);
}