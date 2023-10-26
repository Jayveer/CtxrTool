#include "interface/cli.h"


int main(int argc, char** argv)
{
	CLI cli = CLI(argc, argv);
	cli.run("CtxrTool", "1.1");
}
