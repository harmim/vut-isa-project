/**
 * VUT FIT ISA 2018 project - feed reader.
 *
 * @file Arguments processing interface.
 * @author Dominik Harmim <xharmi00@stud.fit.vutbr.cz>
 */


#ifndef FEEDREADER_ARGUMENT_PROCESSOR_HPP
#define FEEDREADER_ARGUMENT_PROCESSOR_HPP


#include <string>


class ArgumentProcessor
{
public:

	/**
	 * Destructs argument processor object.
	 */
	~ArgumentProcessor();

	/**
	 * Processes program arguments.
	 *
	 * @param argc Number of given program arguments.
	 * @param argv Array of program arguments.
	 * @return True if arguments were processed successfully, false otherwise.
	 */
	bool processArguments(int argc, char *argv[]);

	/**
	 * @return Resource URL.
	 */
	std::string *getUrl();

	/**
	 * @return Feed file location.
	 */
	std::string *getFeedFile();

	/**
	 * @return Certificates file location.
	 */
	std::string *getCertFile();

	/**
	 * @return Certificates directory location.
	 */
	std::string *getCertDir();

	/**
	 * @return Display modification or creation time?
	 */
	bool isTime();

	/**
	 * @return Display author name or email?
	 */
	bool isAuthor();

	/**
	 * @return Display associated URL?
	 */
	bool isAssociatedUrl();


private:

	/**
	 * Help usage string.
	 */
	const std::string *USAGE_STRING = new std::string(
		"    feedreader <url | -f <feedFile>> [-c <certFile>] [-C <certDir>]"
		" [-T] [-a] [-u]\n"
		"        url           - resource URL\n"
		"        -f <feedFile> - feed file location\n"
		"        -c <certFile> - certificates file location\n"
		"        -C <certDir>  - certificates directory location\n"
		"        -T            - display modification or creation time\n"
		"        -a            - display author name or email\n"
		"        -u            - display associated URL\n"
	);

	/**
	 * Resource URL.
	 */
	std::string *url = nullptr;

	/**
	 * Feed file location.
	 */
	std::string *feedFile = nullptr;

	/**
	 * Certificates file location.
	 */
	std::string *certFile = nullptr;

	/**
	 * Certificates directory location.
	 */
	std::string *certDir = nullptr;

	/**
	 * Display modification or creation time?
	 */
	bool time = false;

	/**
	 * Display author name or email?
	 */
	bool author = false;

	/**
	 * Display associated URL?
	 */
	bool associatedUrl = false;


	/**
	 * Prints help usage string.
	 */
	void printUsageString();

	/**
	 * Checks whether required arguments are passed.
	 *
	 * @return True if required arguments are passed, false otherwise.
	 */
	bool checkRequiredArguments();
};


#endif //FEEDREADER_ARGUMENT_PROCESSOR_HPP
