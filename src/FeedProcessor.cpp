/**
 * VUT FIT ISA 2018 project - feed reader.
 *
 * @file Feed processor implementation.
 * @author Dominik Harmim <xharmi00@stud.fit.vutbr.cz>
 */


#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#include "FeedProcessor.hpp"
#include "UrlParser.hpp"
#include "error.hpp"


#define READ_BUFFER_SIZE 4096

#define PROCESS_ERROR \
	{ \
		if (argumentProcessor->getFeedFile()) continue; \
		return false; \
	}

#define CLEAN_RESOURCES \
	{ \
		if (bio) BIO_free_all(bio); \
		if (ctx) SSL_CTX_free(ctx); \
	}

#define PROCESS_BIO_ERROR \
	{ \
		PRINTF_ERR("Error: %s.\n", ERR_reason_error_string(ERR_get_error())); \
		CLEAN_RESOURCES; \
		PROCESS_ERROR; \
	}


bool FeedProcessor::processFeeds(
	std::vector<std::string> urlList, ArgumentProcessor *argumentProcessor
)
{
	SSL_library_init();
	SSL_load_error_strings();
	ERR_load_BIO_strings();
	OpenSSL_add_all_algorithms();

	for (const auto &url : urlList)
	{
		UrlParser urlParser;
		if (!urlParser.parseUrl(url))
		{
			PRINTF_ERR("URL '%s' is not valid http(s) URL.", url.c_str());
			PROCESS_ERROR;
		}

		BIO *bio = nullptr;
		SSL_CTX *ctx = nullptr;
		if (!urlParser.isHttps())
		{
			bio = BIO_new_connect(urlParser.getAuthority()->c_str());
		}
		else
		{
			ctx = SSL_CTX_new(SSLv23_client_method());

			int verify = 0;
			if (
				!argumentProcessor->getCertFile()
				&& !argumentProcessor->getCertDir()
			)
			{
				verify = SSL_CTX_set_default_verify_paths(ctx);
			}
			else if (
				argumentProcessor->getCertFile()
				&& argumentProcessor->getCertDir()
			)
			{
				verify = SSL_CTX_load_verify_locations(
					ctx,
					argumentProcessor->getCertFile()->c_str(),
					argumentProcessor->getCertDir()->c_str()
				);
			}
			else if (argumentProcessor->getCertFile())
			{
				verify = SSL_CTX_load_verify_locations(
					ctx,
					argumentProcessor->getCertFile()->c_str(),
					nullptr
				);
			}
			else
			{
				verify = SSL_CTX_load_verify_locations(
					ctx,
					nullptr,
					argumentProcessor->getCertDir()->c_str()
				);
			}

			if (!verify)
			{
				PRINTF_ERR(
					"Verification of certificates on '%s' failed.", url.c_str()
				);
				PROCESS_BIO_ERROR;
			}

			bio = BIO_new_ssl_connect(ctx);
		}

		if (bio == nullptr)
		{
			PRINTF_ERR("Connection to '%s' failed.", url.c_str());
			PROCESS_BIO_ERROR;
		}

		SSL *ssl = nullptr;
		if (urlParser.isHttps())
		{
			BIO_get_ssl(bio, &ssl);
			SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);
			BIO_set_conn_hostname(bio, urlParser.getAuthority()->c_str());
		}

		if (BIO_do_connect(bio) <= 0)
		{
			PRINTF_ERR("Connection to '%s' failed.", url.c_str());
			PROCESS_BIO_ERROR;
		}

		if (ssl && SSL_get_verify_result(ssl) != X509_V_OK)
		{
			PRINTF_ERR(
				"Verification of certificates on '%s' failed.", url.c_str()
			);
			PROCESS_BIO_ERROR;
		}

		std::string writeData(
			"GET " + *urlParser.getPath() + " HTTP/1.0\r\n"
			"Host: " + *urlParser.getAuthority() + "\r\n"
			"Connection: Close\r\n"
			"User-Agent: Mozilla/5.0 Chrome/70.0.3538.77 Safari/537.36\r\n"
			"\r\n"
		);
		auto writeDataSize = static_cast<int>(writeData.size());
		bool firstWrite = true, writeDone = false;
		while (firstWrite || BIO_should_retry(bio))
		{
			firstWrite = false;
			if (BIO_write(bio, writeData.c_str(), writeDataSize))
			{
				writeDone = true;
				break;
			}
		}
		if (!writeDone)
		{
			PRINT_ERR("Bio write error");
			PROCESS_BIO_ERROR;
		}

		char readBuffer[READ_BUFFER_SIZE] = {'\0'};
		std::string readData;
		int readResult = 0;
		do
		{
			bool firstRead = true, readDone = false;
			while (firstRead || BIO_should_retry(bio))
			{
				firstRead = false;
				readResult = BIO_read(bio, readBuffer, READ_BUFFER_SIZE - 1);
				if (readResult >= 0)
				{
					if (readResult > 0)
					{
						readBuffer[readResult] = '\0';
						readData += readBuffer;
					}

					readDone = true;
					break;
				}
			}
			if (!readDone)
			{
				PRINT_ERR("Bio read error");
				PROCESS_BIO_ERROR;
			}
		}
		while (readResult != 0);

		CLEAN_RESOURCES;
	}

	return true;
}
