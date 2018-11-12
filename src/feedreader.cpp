/**
 * VUT FIT ISA 2018 project - feed reader.
 *
 * @file Main file.
 * @author Dominik Harmim <xharmi00@stud.fit.vutbr.cz>
 */


#include <cstdlib>
#include "ArgumentProcessor.hpp"


int main(int argc, char *argv[])
{
	auto *argumentProcessor = new ArgumentProcessor();
	if (!argumentProcessor->processArguments(argc, argv))
	{
		delete argumentProcessor;
		return EXIT_FAILURE;
	}



	delete argumentProcessor;
	return EXIT_SUCCESS;
}
