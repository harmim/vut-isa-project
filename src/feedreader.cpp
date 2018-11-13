/**
 * VUT FIT ISA 2018 project - feed reader.
 *
 * @file Main file.
 * @author Dominik Harmim <xharmi00@stud.fit.vutbr.cz>
 */


#include <cstdlib>

#include "ArgumentProcessor.hpp"
#include "UrlListFactory.hpp"
#include "FeedProcessor.hpp"


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

	std::vector<std::string> urlList;
	if (argumentProcessor.getUrl())
	{
		urlList = UrlListFactory::createUrlListFromUrl(
			*argumentProcessor.getUrl()
		);
	}
	else if (argumentProcessor.getFeedFile())
	{
		try
		{
			urlList = UrlListFactory::createUrlListFromFeedFile(
				*argumentProcessor.getFeedFile()
			);
		}
		catch (std::exception &e)
		{
			return EXIT_FAILURE;
		}
	}

	return FeedProcessor::processFeeds(urlList, &argumentProcessor)
		? EXIT_SUCCESS
		: EXIT_FAILURE;
}
