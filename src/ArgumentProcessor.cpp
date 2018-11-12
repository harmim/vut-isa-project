/**
 * VUT FIT ISA 2018 project - feed reader.
 *
 * @file Arguments processing implementation.
 * @author Dominik Harmim <xharmi00@stud.fit.vutbr.cz>
 */


#include <unistd.h>
#include <cctype>
#include <cstdio>
#include "ArgumentProcessor.hpp"
#include "error.hpp"


ArgumentProcessor::~ArgumentProcessor()
{
	delete USAGE_STRING;
	delete url;
	delete feedFile;
	delete certFile;
	delete certDir;
}


bool ArgumentProcessor::processArguments(int argc, char *argv[])
{
	opterr = 0;

	int opt;
	while ((opt = getopt(argc, argv, "f:c:C:Tau")) != -1)
	{
		switch (opt)
		{
			case 'f':
				feedFile = new std::string(optarg);
				break;

			case 'c':
				certFile = new std::string(optarg);
				break;

			case 'C':
				certDir = new std::string(optarg);
				break;

			case 'T':
				time = true;
				break;

			case 'a':
				author = true;
				break;

			case 'u':
				associatedUrl = true;
				break;

			case '?':
				if (optopt == 'f' || optopt == 'c' || optopt == 'C')
				{
					PRINTF_ERR("Option '-%c' requires an argument.", optopt);
				}
				else if (isprint(optopt))
				{
					PRINTF_ERR("Unknown option '-%c'.", optopt);
				}
				else
				{
					PRINTF_ERR("Unknown option character '\\x%x'.", optopt);
				}

				printUsageString();
				return false;

			default:
				PRINT_ERR("Processing program arguments failed.");
				printUsageString();

				return false;
		}
	}

	if (optind < argc)
	{
		if (argc - optind > 1)
		{
			auto *unknownArguments = new std::string();
			for (int i = optind + 1; i < argc; i++)
			{
				unknownArguments->append(argv[i]);
				if (i == argc - 1)
				{
					unknownArguments->append(".");
				}
				else
				{
					unknownArguments->append(", ");
				}
			}
			PRINTF_ERR("Unknown arguments: %s", unknownArguments->c_str());
			delete unknownArguments;
			printUsageString();

			return false;
		}

		url = new std::string(argv[optind]);
	}

	if (!checkRequiredArguments())
	{
		printUsageString();
		return false;
	}

	return true;
}


std::string *ArgumentProcessor::getUrl()
{
	return url;
}


std::string *ArgumentProcessor::getFeedFile()
{
	return feedFile;
}


std::string *ArgumentProcessor::getCertFile()
{
	return certFile;
}


std::string *ArgumentProcessor::getCertDir()
{
	return certDir;
}


bool ArgumentProcessor::isTime()
{
	return time;
}


bool ArgumentProcessor::isAuthor()
{
	return author;
}


bool ArgumentProcessor::isAssociatedUrl()
{
	return associatedUrl;
}


void ArgumentProcessor::printUsageString()
{
	printf("\nusage:\n%s\n", USAGE_STRING->c_str());
}


bool ArgumentProcessor::checkRequiredArguments()
{
	if (url == nullptr && feedFile == nullptr)
	{
		PRINT_ERR("Argument 'url' or '-f <feedfile>' is required.");
		return false;
	}

	if (url != nullptr && feedFile != nullptr)
	{
		PRINT_ERR(
			"Argument 'url' or '-f <feedfile>' is required but not both."
		);
		return false;
	}

	return true;
}
