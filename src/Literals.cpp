/**
 * @file      Literals.cpp
 * @copyright (c) 2020 by Oded Arbel (guss77@geek.co.il) and contributors
 * @license   BSD, see the @c LICENSE file for more details
 * @brief     Implementation of C++ custom literals
 */

#include "Literals.h"

using namespace bencoding;

/**
* @brief Create a BString litaral
*/
BStringPtr operator "" _bencoding(const char* str, size_t len) {
	return BString::create(std::string(str, len));
}

BIntegerPtr operator "" _bencoding(unsigned long long i) {
	return BInteger::create(i);
}
