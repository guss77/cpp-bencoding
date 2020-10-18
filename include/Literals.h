/**
 * @file      Literals.h
 * @copyright (c) 2020 by Oded Arbel (guss77@geek.co.il) and contributors
 * @license   BSD, see the @c LICENSE file for more details
 * @brief     C++ custom literals for bencoding
 */

#ifndef BENCODING_LITERALS_H
#define BENCODING_LITERALS_H

#include <memory>

#include "BString.h"
#include "BInteger.h"

bencoding::BStringPtr operator "" _bencoding(const char* str, size_t len);
bencoding::BIntegerPtr operator "" _bencoding(unsigned long long i);

#endif
