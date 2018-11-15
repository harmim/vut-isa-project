/**
 * VUT FIT ISA 2018 project - feed reader.
 *
 * @file XML parser interface.
 * @author Dominik Harmim <xharmi00@stud.fit.vutbr.cz>
 */


#ifndef FEEDREADER_XMLPARSER_HPP
#define FEEDREADER_XMLPARSER_HPP


#include <string>
#include <libxml/parser.h>

#include "ArgumentProcessor.hpp"


class XmlParser
{
public:
	/**
	 * Parses XML feed and prints appropriate information.
	 *
	 * @param xmlData XML data to be parsed.
	 * @param argumentProcessor ArgumentProcessor object with processed
	 *        arguments.
	 * @param url Feed URL.
	 * @return True if XML has been parsed successfully, false otherwise.
	 */
	static bool parseXmlFeed(
		std::string xml, ArgumentProcessor *argumentProcessor, std::string url
	);

	/**
	 * Signature of the function to use when there is an error and
	 * no parsing or validity context available.
	 *
	 * @param ctx A parsing context.
	 * @param msg The message.
	 * @param ... The extra arguments of the varags to format the message.
	 */
	static void xmlGenericErrorFunc(void *ctx, const char *msg, ...);

	/**
	 * Signature of the function to use when there is an error and
	 * the module handles the new error reporting mechanism.
	 *
	 * @param userData User provided data for the error callback.
	 * @param error The error being raised.
	 */
	static void xmlStructuredErrorFunc(void *userData, xmlErrorPtr error);

private:
	/**
	 * Feed types.
	 */
	enum FEED_TYPE { UNKNOWN, RSS1, RSS2, ATOM };

	/**
	 * Finds out the type of feed.
	 *
	 * @param root Root element of feed.
	 * @return Type of given feed.
	 */
	static FEED_TYPE getFeedType(xmlNodePtr root);

	/**
	 * Parses RSS1 feed.
	 *
	 * @param root Root element of feed.
	 * @param argumentProcessor ArgumentProcessor object with processed
	 *        arguments.
	 * @param url Feed URL.
	 * @return True if XML has been parsed successfully, false otherwise.
	 */
	static bool parseRss1(
		xmlNodePtr root, ArgumentProcessor *argumentProcessor, std::string url
	);

	/**
	 * Parses RSS2 feed.
	 *
	 * @param root Root element of feed.
	 * @param argumentProcessor ArgumentProcessor object with processed
	 *        arguments.
	 * @param url Feed URL.
	 * @return True if XML has been parsed successfully, false otherwise.
	 */
	static bool parseRss2(
		xmlNodePtr root, ArgumentProcessor *argumentProcessor, std::string url
	);

	/**
	 * Parses Atom feed.
	 *
	 * @param root Root element of feed.
	 * @param argumentProcessor ArgumentProcessor object with processed
	 *        arguments.
	 * @param url Feed URL.
	 * @return True if XML has been parsed successfully, false otherwise.
	 */
	static bool parseAtom(
		xmlNodePtr root, ArgumentProcessor *argumentProcessor, std::string url
	);
};


#endif //FEEDREADER_XMLPARSER_HPP
