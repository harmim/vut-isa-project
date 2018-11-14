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
	 * @return True if XML has been parsed successfully, false otherwise.
	 */
	static bool parseXmlFeed(
		std::string xml, ArgumentProcessor *argumentProcessor
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
};


#endif //FEEDREADER_XMLPARSER_HPP
