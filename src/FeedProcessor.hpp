/**
 * VUT FIT ISA 2018 project - feed reader.
 *
 * @file Feed processor interface.
 * @author Dominik Harmim <xharmi00@stud.fit.vutbr.cz>
 */

#ifndef FEEDREADER_FEEDDOPROCESSOR_HPP
#define FEEDREADER_FEEDDOPROCESSOR_HPP


#include <string>
#include <vector>

#include "ArgumentProcessor.hpp"


class FeedProcessor
{
public:
	/**
	 * Process list of URLs with feeds.
	 *
	 * @param urlList List of URLs with feeds.
	 * @param argumentProcessor ArgumentProcessor object with processed
	 *        arguments.
	 * @return True if the processing was successful, false otherwise.
	 */
	static bool processFeeds(
		std::vector<std::string> urlList, ArgumentProcessor *argumentProcessor
	);
};


#endif //FEEDREADER_FEEDDOPROCESSOR_HPP
