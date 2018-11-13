/**
 * VUT FIT ISA 2018 project - feed reader.
 *
 * @file Url parser implementation.
 * @author Dominik Harmim <xharmi00@stud.fit.vutbr.cz>
 */


#include <regex>

#include "UrlParser.hpp"


UrlParser::~UrlParser()
{
	delete authority;
	delete path;
}


bool UrlParser::parseUrl(std::string url)
{
	std::regex regex(
		R"(^(https?)://([^\/\?#:]+)(:([0-9]+))?(.*)$)",
		std::regex::extended
	);
	std::smatch matches;

	if (!std::regex_match(url, matches, regex))
	{
		return false;
	}

	https = std::string(matches[1]) == "https";
	authority = new std::string(matches[2]);
	path = new std::string(matches[5]);

	std::string port(matches[4]);
	if (port.empty())
	{
		port = https ? PORT_HTTPS : PORT_HTTP;
	}
	*authority += ":" + port;

	return true;
}


std::string *UrlParser::getAuthority()
{
	return authority;
}


std::string *UrlParser::getPath()
{
	return path;
}


bool UrlParser::isHttps()
{
	return https;
}
