/**
 * @file      Literals.cpp
 * @copyright (c) 2020 by Oded Arbel (guss77@geek.co.il) and contributors
 * @license   BSD, see the @c LICENSE file for more details
 * @brief     Implementation of C++ custom literals
 */

#include "Literals.h"

namespace bencoding {

/**
* @brief Create a BString litaral
*/
std::shared_ptr<BString> operator "" _bencoding(const char* val) { return BString::create(val); }

} // namespace bencoding
