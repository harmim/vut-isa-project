/**
 * VUT FIT ISA 2018 project - feed reader.
 *
 * @file Url parser interface.
 * @author Dominik Harmim <xharmi00@stud.fit.vutbr.cz>
 */

#ifndef FEEDREADER_URLPARSER_HPP
#define FEEDREADER_URLPARSER_HPP


#include <string>


class UrlParser
{
public:
	/**
	 * Destructs Url parser.
	 */
	~UrlParser();

	/**
	 * Parses given URL.
	 *
	 * @param url URL to be parsed.
	 * @return True if parsing was successful, false otherwise.
	 */
	bool parseUrl(std::string url);

	/**
	 * @return URL authority.
	 */
	std::string *getAuthority();

	/**
	 * @return URL path with query and fragment.
	 */
	std::string *getPath();

	/**
	 * @return Is scheme https?
	 */
	bool isHttps();

private:
	const std::string PORT_HTTP = "80"; // HTTP port number
	const std::string PORT_HTTPS = "443"; // HTTPS port number

	/**
	 * URL authority ([user[:password]@]host[:port]).
	 */
	std::string *authority = nullptr;

	/**
	 * URL path with query and fragment (eg. /foo/bar?foo=bar#foo).
	 */
	std::string *path = nullptr;

	/**
	 * Is scheme https?
	 */
	bool https = false;
};


#endif //FEEDREADER_URLPARSER_HPP
