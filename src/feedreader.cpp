/**
 * VUT FIT ISA 2018 project - feed reader.
 *
 * @file Main file.
 * @author Dominik Harmim <xharmi00@stud.fit.vutbr.cz>
 */


#include <cstdlib>
#include "ArgumentProcessor.hpp"
#include "UrlListFactory.hpp"


int main(int argc, char *argv[])
{
	ArgumentProcessor argumentProcessor;
	if (!argumentProcessor.processArguments(argc, argv))
	{
		return EXIT_FAILURE;
	}
	if (argumentProcessor.isHelp())
	{
		return EXIT_SUCCESS;
	}

	UrlListFactory urlListFactory;
	std::vector<std::string> urlList;
	if (argumentProcessor.getUrl() != nullptr)
	{
		urlList = urlListFactory.createUrlListFromUrl(
			*argumentProcessor.getUrl()
		);
	}
	else if (argumentProcessor.getFeedFile() != nullptr)
	{
		try
		{
			urlList = urlListFactory.createUrlListFromFeedFile(
				*argumentProcessor.getFeedFile()
			);
		}
		catch (std::exception &e)
		{
			return EXIT_FAILURE;
		}
	}

	return EXIT_SUCCESS;
}
