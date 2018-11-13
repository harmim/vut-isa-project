/**
 * VUT FIT ISA 2018 project - feed reader.
 *
 * @file Url list implementation.
 * @author Dominik Harmim <xharmi00@stud.fit.vutbr.cz>
 */


#include <utility>
#include <fstream>
#include "UrlListFactory.hpp"
#include "error.hpp"


std::vector<std::string> UrlListFactory::createUrlListFromFeedFile(
	std::string feedFile
)
{
	std::ifstream file(feedFile);
	if (!file.is_open())
	{
		PRINTF_ERR("Unable to open file %s.", feedFile.c_str());
		throw std::exception();
	}

	std::vector<std::string> urlList;
	std::string line;
	while (getline(file, line))
	{
		if (line.empty() || !line.compare(0, 1, "#"))
		{
			continue;
		}
		urlList.push_back(line);
	}
	file.close();

	return urlList;
}


std::vector<std::string> UrlListFactory::createUrlListFromUrl(std::string url)
{
	return std::vector<std::string>({std::move(url)});
}
