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

	switch (outputType)
	{
	case TGA_FILE:
	{
		TGA tga;
		tga.create(ctxr.getWidth(), ctxr.getHeight(), ctxr.getData() + 4, ctxr.getMainTextureSize());
		outFilename = getExtensionlessName(argv[1]) + ".tga";
		tga.save(outFilename.c_str());
		return;
	}
	case BMP_FILE:
	{
		BMP bmp;
		bmp.create(ctxr.getWidth(), ctxr.getHeight(), ctxr.getData() + 4, ctxr.getMainTextureSize());
		outFilename = getExtensionlessName(argv[1]) + ".bmp";
		bmp.save(outFilename.c_str());
		return;
	}
	case DDS_FILE:
	default:
	{
		DDS dds;
		uint32_t flags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PITCH | DDSD_PIXELFORMAT | DDSD_MIPMAPCOUNT;

		dds.create(ctxr.getWidth(), ctxr.getHeight(), 0, ctxr.getNMipMaps(), flags, ctxr.getData(), ctxr.getSize() - 0x80);
		outFilename = getExtensionlessName(argv[1]) + ".dds";
		dds.save(outFilename.c_str());
	}
	}
}

void CLI::convertBMP()
{
	BMP bmp;
	std::string filename;

	bmp.open(argv[1]);

	uint8_t* copy = new uint8_t[bmp.getSize() - 0x36];
	flipVertical(copy, bmp.getData(), bmp.getWidth(), bmp.getHeight(), 4);

	CTXR ctxr;
	ctxr.create(bmp.getWidth(), bmp.getHeight(), 1, copy, bmp.getSize() - 0x36);

	filename = getExtensionlessName(argv[1]) + ".param";
	ctxr.addParams(filename.c_str());

	filename = getExtensionlessName(argv[1]) + ".ctxr";
	ctxr.save(filename.c_str(), generateMipMaps);

	delete[] copy;
}

void CLI::convertTGA()
{
	TGA tga;
	uint8_t* data;
	std::string filename;

	tga.open(argv[1]);

	CTXR ctxr;

	if (tga.isFlipped())
	{
		data = new uint8_t[tga.getSize() - 0x2C];
		flipVertical(data, tga.getData(), tga.getWidth(), tga.getHeight(), 4);
	}
	else
	{
		data = tga.getData();
	}


	ctxr.create(tga.getWidth(), tga.getHeight(), 1, data, tga.getSize() - 0x2C);
	filename = getExtensionlessName(argv[1]) + ".param";
	ctxr.addParams(filename.c_str());

	filename = getExtensionlessName(argv[1]) + ".ctxr";
	ctxr.save(filename.c_str(), generateMipMaps);

	if (tga.isFlipped())
	{
		delete[] data;
	}
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

void CLI::exec()
{
	switch(inputType)
	{
	case CTXR_FILE:
		convertCTXR(); return;
	case DDS_FILE:
		convertDDS();  return;
	case TGA_FILE:
		convertTGA();  return;
	case BMP_FILE:
		convertBMP();  return;
	case UNSUPPORTED_FILE:
	default:
		printf("Unsupported input file type");
		return;
	}
}

void CLI::processArgs() 
{
	setInputType();
	currentArg++;
	processCommands();
	exec();
}

void CLI::processCommands() {
	while (currentArg < 6 && isCommand(argv[currentArg])) 
	{
		setCommand(argv[currentArg], argv[currentArg + 1]);
		currentArg += 2;
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
	if (argc > 1 && argc < 7) return true;
	printUsage();
	return false;
}

bool CLI::isCommand(char* arg)
{
	if (!arg) return false;
	return arg[0] == 0x2D;
}

void CLI::setCommand(char* arg, char* val)
{

	if (!strcmp(arg, "--file") || !strcmp(arg, "-f"))
	{
		setOutputType(val);
		return;
	}

	if (!strcmp(arg, "--mipmaps") || !strcmp(arg, "-m"))
	{
		setGenMipMaps(val);
		return;
	}

	printf("command not recognised");
}

void CLI::setGenMipMaps(char* arg)
{
	if (!strcmp(arg, "n") || !strcmp(arg, "no"))
	{
		generateMipMaps = false;
	}
}

void CLI::setInputType()
{
	std::string ext = getExtension(argv[1]);

	if (ext == ".dds" || ext == ".DDS")
	{
		inputType = DDS_FILE;
		return;
	}

	if (ext == ".ctxr" || ext == ".CTXR")
	{
		inputType = CTXR_FILE;
		return;
	}
	
	if (ext == ".tga" || ext == ".TGA")
	{
		inputType = TGA_FILE;
		return;
	}

	if (ext == ".bmp" || ext == ".BMP")
	{
		inputType = BMP_FILE;
		return;
	}

	inputType = UNSUPPORTED_FILE;
}

void CLI::setOutputType(char* arg)
{
	if (!strcmp(arg, "tga") || !strcmp(arg, "TGA"))
	{
		outputType = TGA_FILE;
		return;
	}

	if (!strcmp(arg, "bmp") || !strcmp(arg, "BMP"))
	{
		outputType = BMP_FILE;
		return;
	}

	outputType = DDS_FILE;

}

void CLI::printUsage()
{
	printf(this->USAGE_MESSAGE);
}