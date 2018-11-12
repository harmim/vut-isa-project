/**
 * VUT FIT ISA 2018 project - feed reader.
 *
 * @file Errors processing.
 * @author Dominik Harmim <xharmi00@stud.fit.vutbr.cz>
 */


#ifndef FEEDREADER_ERROR_HPP
#define FEEDREADER_ERROR_HPP


#include <cstdio>


#define PRINT_ERR(_e) fprintf(stderr, (_e "\n"))
#define PRINTF_ERR(_e, ...) fprintf(stderr, (_e "\n"), __VA_ARGS__)


#endif //FEEDREADER_ERROR_HPP
