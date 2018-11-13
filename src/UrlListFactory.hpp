/**
 * VUT FIT ISA 2018 project - feed reader.
 *
 * @file Url list interface.
 * @author Dominik Harmim <xharmi00@stud.fit.vutbr.cz>
 */


#ifndef FEEDREADER_URLLISTFACTORY_HPP
#define FEEDREADER_URLLISTFACTORY_HPP


#include <vector>
#include <string>


class UrlListFactory
{
public:
	/**
	 * Creates URL list from feed file.
	 *
	 * @param feedFile Feed file location.
	 * @return URL list created from feed file.
	 */
	std::vector<std::string> createUrlListFromFeedFile(std::string feedFile);

	/**
	 * Creates URL list from single URL.
	 *
	 * @param url Resource Url.
	 * @return URL list created from single URL.
	 */
	std::vector<std::string> createUrlListFromUrl(std::string url);
};


#endif //FEEDREADER_URLLISTFACTORY_HPP
