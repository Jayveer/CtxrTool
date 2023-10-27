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
	std::string filename = getExtensionlessName(argv[1]);
	std::string outFilename;

	outFilename = filename + ".param";
	ctxr.saveParams(outFilename.c_str());

	if (argv[2] != NULL)
	{
		if (strcmp(argv[2], "tga") == 0)
		{
			TGA tga;
			tga.create(ctxr.getWidth(), ctxr.getHeight(), ctxr.getData(), ctxr.getMainTextureSize());
			outFilename = getExtensionlessName(argv[1]) + ".tga";
			tga.save(outFilename.c_str());
			return;
		}
	}

	DDS dds;
	uint32_t flags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PITCH | DDSD_PIXELFORMAT | DDSD_MIPMAPCOUNT;

	dds.create(ctxr.getWidth(), ctxr.getHeight(), 0, ctxr.getNMipMaps(), flags, ctxr.getData(), ctxr.getSize() - 0x80);
	outFilename = getExtensionlessName(argv[1]) + ".dds";
	dds.save(outFilename.c_str());
}


void CLI::convertDDS()
{
	DDS dds;
	std::string filename;

	dds.open(argv[1]);

	CTXR ctxr;
	ctxr.create(dds.getWidth(), dds.getHeight(), dds.getNMipMaps(), dds.getData(), dds.getSize() - 0x80);

	filename = getExtensionlessName(argv[1]) + ".param";
	ctxr.addParams(filename.c_str());

	filename = getExtensionlessName(argv[1]) + ".ctxr";
	ctxr.saveExtend(filename.c_str());
}

void CLI::processArgs() 
{
	std::string ext = getExtension(argv[1]);

	if (ext == ".dds" || ext == ".DDS")
	{
		convertDDS();
	}
	else if (ext == ".ctxr" || ext == ".CTXR")
	{
		convertCTXR();
	}
	else
	{
		printf("Unsupported file type");
	}
}

void CLI::run(const char* programName, const char* version)
{
	this->version = version;
	this->programName = programName;

	printWelcome();
	if (!checkInput()) return;
	processArgs();
}

void CLI::printWelcome()
{
	printf("Running %s v%s: Visit https://github.com/Jayveer/CtxrTool for updates:\n", programName, version);
}

bool CLI::checkInput()
{
	if (argc > 1 && argc < 4) return true;
	printUsage();
	return false;
}

void CLI::setInputType()
{
	std::string ext = getExtension(argv[1]);

	if (ext == ".dds" || ext == ".DDS")
	{
		inputType = DDS_FILE;
	}
	else if (ext == ".ctxr" || ext == ".CTXR")
	{
		inputType = CTXR_FILE;
	}
	else
	{
		printf("Unsupported file type");
	}
}

void CLI::setOutputType()
{
	if (strcmp(argv[2], "tga") == 0)
	{
		outputType = TGA_FILE;
	}
	else
	{
		outputType = DDS_FILE;;
	}
}

void CLI::printUsage()
{
	printf(this->USAGE_MESSAGE);
}
