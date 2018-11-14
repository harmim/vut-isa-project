/**
 * VUT FIT ISA 2018 project - feed reader.
 *
 * @file XML parser implementation.
 * @author Dominik Harmim <xharmi00@stud.fit.vutbr.cz>
 */


#include "XmlParser.hpp"


bool XmlParser::parseXmlFeed(
	std::string xml, ArgumentProcessor *argumentProcessor
)
{
#ifndef DEBUG
	xmlSetGenericErrorFunc(nullptr, XmlParser::xmlGenericErrorFunc);
	xmlSetStructuredErrorFunc(nullptr, XmlParser::xmlStructuredErrorFunc);
#endif

	xmlDocPtr docPtr = xmlParseDoc((const xmlChar *) xml.c_str());
	if (docPtr == nullptr)
	{
		return false;
	}

	(void) argumentProcessor;

	return true;
}


void XmlParser::xmlGenericErrorFunc(void *ctx, const char *msg, ...)
{
	(void) ctx;
	(void) msg;
}


void XmlParser::xmlStructuredErrorFunc(void *userData, xmlErrorPtr error)
{
	(void) userData;
	(void) error;
}
