/**
 * VUT FIT ISA 2018 project - feed reader.
 *
 * @file XML parser implementation.
 * @author Dominik Harmim <xharmi00@stud.fit.vutbr.cz>
 */


#include "XmlParser.hpp"
#include "error.hpp"


#define PRINT_TITLE(_title) printf("*** %s ***\n", (_title))

#define PRINT_ITEM \
	{ \
		if (!itemTitle.empty()) \
		{ \
			printf("%s\n", itemTitle.c_str()); \
			if (!time.empty()) printf("Time: %s\n", time.c_str()); \
			if (!author.empty()) printf("Author: %s\n", author.c_str()); \
			if (!associatedUrl.empty()) \
				printf("URL: %s\n", associatedUrl.c_str()); \
			if ( \
				i < itemCount - 1 \
				&& ( \
					argumentProcessor->isTime() \
					|| argumentProcessor->isAuthor() \
					|| argumentProcessor->isAssociatedUrl() \
				) \
			) printf("\n"); \
		} \
	}


bool XmlParser::parseXmlFeed(
	std::string xml, ArgumentProcessor *argumentProcessor, std::string url
)
{
#ifndef DEBUG
	xmlSetGenericErrorFunc(nullptr, XmlParser::xmlGenericErrorFunc);
	xmlSetStructuredErrorFunc(nullptr, XmlParser::xmlStructuredErrorFunc);
#endif
	xmlKeepBlanksDefault(0);

	xmlDocPtr doc = xmlParseDoc((const xmlChar *) xml.c_str());
	if (!doc)
	{
		PRINTF_ERR("Invalid feed format on '%s'.", url.c_str());
		xmlCleanupParser();
		return false;
	}

	xmlNodePtr root = xmlDocGetRootElement(doc);
	if (!root)
	{
		PRINTF_ERR("Empty feed file on '%s'.", url.c_str());
		xmlFreeDoc(doc);
		xmlCleanupParser();
		return false;
	}

	bool result = false;
	switch (getFeedType(root))
	{
		case FEED_TYPE::RSS1:
			result = parseRss1(root, argumentProcessor, url);
			break;

		case FEED_TYPE::RSS2:
			result = parseRss2(root, argumentProcessor, url);
			break;

		case FEED_TYPE::ATOM:
			result = parseAtom(root, argumentProcessor, url);
			break;

		default:
			PRINTF_ERR("Unknown feed file format on '%s'.", url.c_str());
			break;
	}

	xmlFreeDoc(doc);
	xmlCleanupParser();
	return result;
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


XmlParser::FEED_TYPE XmlParser::getFeedType(xmlNodePtr root)
{
	if (!xmlStrcasecmp(root->name, (xmlChar *) "rdf"))
	{
		return FEED_TYPE::RSS1;
	}
	else if (!xmlStrcasecmp(root->name, (xmlChar *) "rss"))
	{
		return FEED_TYPE::RSS2;
	}
	else if (!xmlStrcasecmp(root->name, (xmlChar *) "feed"))
	{
		return FEED_TYPE::ATOM;
	}

	return FEED_TYPE::UNKNOWN;
}


bool XmlParser::parseRss1(
	xmlNodePtr root, ArgumentProcessor *argumentProcessor, std::string url
)
{
	std::string title;
	for (auto rootNode = root->children; rootNode; rootNode = rootNode->next)
	{
		if (!xmlStrcasecmp(rootNode->name, (xmlChar *) "channel"))
		{
			for (
				auto channelNode = rootNode->children;
				channelNode;
				channelNode = channelNode->next
			)
			{
				if (!xmlStrcasecmp(channelNode->name, (xmlChar *) "title"))
				{
					title = (char *) xmlNodeGetContent(channelNode);
					break;
				}
			}
			break;
		}
	}
	if (title.empty())
	{
		PRINTF_ERR("Feed title is empty on '%s'.", url.c_str());
		return false;
	}
	PRINT_TITLE(title.c_str());

	unsigned long itemCount = xmlChildElementCount(root), i = 0;
	for (
		auto rootNode = root->children;
		rootNode;
		rootNode = rootNode->next, i++
	)
	{
		if (!xmlStrcasecmp(rootNode->name, (xmlChar *) "item"))
		{
			std::string itemTitle, time, author, associatedUrl;
			for (
				auto itemNode = rootNode->children;
				itemNode;
				itemNode = itemNode->next
			)
			{
				if (!xmlStrcasecmp(itemNode->name, (xmlChar *) "title"))
				{
					itemTitle = (char *) xmlNodeGetContent(itemNode);
				}
				else if (
					argumentProcessor->isTime()
					&& !xmlStrcasecmp(itemNode->name, (xmlChar *) "date")
				)
				{
					time = (char *) xmlNodeGetContent(itemNode);
				}
				else if (
					argumentProcessor->isAuthor()
					&& !xmlStrcasecmp(itemNode->name, (xmlChar *) "creator")
				)
				{
					author = (char *) xmlNodeGetContent(itemNode);
				}
				else if (
					argumentProcessor->isAssociatedUrl()
					&& !xmlStrcasecmp(itemNode->name, (xmlChar *) "link")
				)
				{
					associatedUrl = (char *) xmlNodeGetContent(itemNode);
				}
			}

			PRINT_ITEM;
		}
	}

	return true;
}


bool XmlParser::parseRss2(
	xmlNodePtr root, ArgumentProcessor *argumentProcessor, std::string url
)
{
	std::string title;
	for (auto rootNode = root->children; rootNode; rootNode = rootNode->next)
	{
		if (!xmlStrcasecmp(rootNode->name, (xmlChar *) "channel"))
		{
			for (
				auto channelNode = rootNode->children;
				channelNode;
				channelNode = channelNode->next
			)
			{
				if (!xmlStrcasecmp(channelNode->name, (xmlChar *) "title"))
				{
					title = (char *) xmlNodeGetContent(channelNode);
					break;
				}
			}
			break;
		}
	}
	if (title.empty())
	{
		PRINTF_ERR("Feed title is empty on '%s'.", url.c_str());
		return false;
	}
	PRINT_TITLE(title.c_str());

	for (auto rootNode = root->children; rootNode; rootNode = rootNode->next)
	{
		if (!xmlStrcasecmp(rootNode->name, (xmlChar *) "channel"))
		{
			unsigned long itemCount = xmlChildElementCount(rootNode), i = 0;
			for (
				auto channelNode = rootNode->children;
				channelNode;
				channelNode = channelNode->next, i++
			)
			{
				if (!xmlStrcasecmp(channelNode->name, (xmlChar *) "item"))
				{
					std::string itemTitle, time, author, associatedUrl;
					for (
						auto itemNode = channelNode->children;
						itemNode;
						itemNode = itemNode->next
					)
					{
						if (!xmlStrcasecmp(itemNode->name, (xmlChar *) "title"))
						{
							itemTitle = (char *) xmlNodeGetContent(itemNode);
						}
						else if (
							argumentProcessor->isTime()
							&& !xmlStrcasecmp(
								itemNode->name,
								(xmlChar *) "pubDate"
							)
						)
						{
							time = (char *) xmlNodeGetContent(itemNode);
						}
						else if (
							argumentProcessor->isAuthor()
							&& !xmlStrcasecmp(
								itemNode->name,
								(xmlChar *) "author"
							)
						)
						{
							author = (char *) xmlNodeGetContent(itemNode);
						}
						else if (
							argumentProcessor->isAssociatedUrl()
							&& !xmlStrcasecmp(
								itemNode->name,
								(xmlChar *) "link"
							)
						)
						{
							associatedUrl =
								(char *) xmlNodeGetContent(itemNode);
						}
					}

					PRINT_ITEM;
				}
			}
			break;
		}
	}

	return true;
}


bool XmlParser::parseAtom(
	xmlNodePtr root, ArgumentProcessor *argumentProcessor, std::string url
)
{
	std::string title;
	for (auto rootNode = root->children; rootNode; rootNode = rootNode->next)
	{
		if (!xmlStrcasecmp(rootNode->name, (xmlChar *) "title"))
		{
			title = (char *) xmlNodeGetContent(rootNode);
			break;
		}
	}
	if (title.empty())
	{
		PRINTF_ERR("Feed title is empty on '%s'.", url.c_str());
		return false;
	}
	PRINT_TITLE(title.c_str());

	unsigned long itemCount = xmlChildElementCount(root), i = 0;
	for (
		auto rootNode = root->children;
		rootNode;
		rootNode = rootNode->next, i++
	)
	{
		if (!xmlStrcasecmp(rootNode->name, (xmlChar *) "entry"))
		{
			std::string itemTitle, time, author, associatedUrl;
			for (
				auto entryNode = rootNode->children;
				entryNode;
				entryNode = entryNode->next
			)
			{
				if (!xmlStrcasecmp(entryNode->name, (xmlChar *) "title"))
				{
					itemTitle = (char *) xmlNodeGetContent(entryNode);
				}
				else if (
					argumentProcessor->isTime()
					&& !xmlStrcasecmp(entryNode->name, (xmlChar *) "updated")
				)
				{
					time = (char *) xmlNodeGetContent(entryNode);
				}
				else if (
					argumentProcessor->isAuthor()
					&& !xmlStrcasecmp(entryNode->name, (xmlChar *) "author")
				)
				{
					for (
						auto authorNode = entryNode->children;
						authorNode;
						authorNode = authorNode->next
					)
					{
						if (
							!xmlStrcasecmp(authorNode->name, (xmlChar *) "name")
						)
						{
							author = (char *) xmlNodeGetContent(authorNode);
						}
					}
				}
				else if (
					argumentProcessor->isAssociatedUrl()
					&& !xmlStrcasecmp(entryNode->name, (xmlChar *) "link")
				)
				{
					associatedUrl =
						(char *) xmlGetProp(entryNode, (xmlChar *) "href");
				}
			}

			PRINT_ITEM;
		}
	}

	return true;
}
