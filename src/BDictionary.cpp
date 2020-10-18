/**
* @file      BDictionary.cpp
* @copyright (c) 2014 by Petr Zemek (s3rvac@gmail.com) and contributors
* @license   BSD, see the @c LICENSE file for more details
* @brief     Implementation of the BDictionary class.
*/
#include "BDictionary.h"
#include <map>

#include "BItemVisitor.h"
#include "BString.h"
#include "BList.h"

namespace bencoding {

/**
* @brief Checks if <tt>lhs->value() < rhs->value()</tt>.
*
* @return @c true if <tt>lhs->value() < rhs->value()</tt>, @c false otherwise.
*/
bool BDictionary::BStringByValueComparator::operator()(
		const std::shared_ptr<BString> &lhs,
		const std::shared_ptr<BString> &rhs) const {

	return *(lhs->value()) < *(rhs->value());
}

/**
* @brief Constructs an empty dictionary.
*/
BDictionary::BDictionary() = default;

/**
* @brief Constructs a dictionary from the given items.
*/
BDictionary::BDictionary(std::initializer_list<value_type> items):
	itemMap(items) {}

/**
* @brief Creates and returns a new dictionary.
*/
std::shared_ptr<BDictionary> BDictionary::create() {
	return std::shared_ptr<BDictionary>(new BDictionary());
}

/**
* @brief Creates and returns a new dictionary containing the given @a items.
*/
std::shared_ptr<BDictionary> BDictionary::create(
		std::initializer_list<value_type> items) {
	return std::shared_ptr<BDictionary>(new BDictionary(items));
}

/**
* @brief Returns the number of items in the dictionary.
*/
BDictionary::size_type BDictionary::size() const {
	return itemMap.size();
}

/**
* @brief Checks if the dictionary is empty.
*
* @return @c true if the dictionary is empty, @c false otherwise.
*/
bool BDictionary::empty() const {
	return itemMap.empty();
}

/**
* @brief Accesses the specified element.
*
* @returns A reference to the value that is mapped to a key equivalent to key.
*
* If there is no value mapped to @a key, an insertion of a null pointer is
* automatically performed, and a reference to this null pointer is returned.
*/
BDictionary::mapped_type &BDictionary::operator[](key_type key) {
	return itemMap[key];
}

BDictionary::mapped_type &BDictionary::operator[](std::string key) {
    key_type tmpKey = BString::create(key);
    return itemMap[tmpKey];
}

BDictionary::size_type BDictionary::erase(const std::string key) {
    key_type keystr = BString::create(key);
    return erase(keystr);
}

BDictionary::size_type BDictionary::erase(const key_type& key) {
    return itemMap.erase(key);
}

std::shared_ptr<BList> BDictionary::values() {
    BListPtr rst = BList::create();
    for(auto item : itemMap){
        rst->push_back(item.second);
    }

    return rst;
}

/**
* @brief Returns an iterator to the beginning of the dictionary.
*/
BDictionary::iterator BDictionary::begin() {
	return itemMap.begin();
}

/**
* @brief Returns an iterator to the end of the dictionary.
*/
BDictionary::iterator BDictionary::end() {
	return itemMap.end();
}

/**
* @brief Returns a constant iterator to the beginning of the dictionary.
*/
BDictionary::const_iterator BDictionary::begin() const {
	return itemMap.begin();
}

/**
* @brief Returns a constant iterator to the end of the dictionary.
*/
BDictionary::const_iterator BDictionary::end() const {
	return itemMap.end();
}

/**
* @brief Returns a constant iterator to the beginning of the dictionary.
*/
BDictionary::const_iterator BDictionary::cbegin() const {
	return itemMap.cbegin();
}

/**
* @brief Returns a constant iterator to the end of the dictionary.
*/
BDictionary::const_iterator BDictionary::cend() const {
	return itemMap.cend();
}

void BDictionary::accept(BItemVisitor *visitor) {
	visitor->visit(this);
}

BDictionary::mapped_type BDictionary::setDefault(std::string key, std::shared_ptr<BItem> value) {

    return setDefault(BString::create(key), value);
}

BDictionary::mapped_type BDictionary::setDefault(key_type key, mapped_type value) {
    mapped_type tmp = itemMap[key];
    if (tmp == nullptr) {
        itemMap[key] = value;
    }

    return itemMap[key];
}

bool BDictionary::hasKey(std::string key) {
    key_type tmpKey = BString::create(key);
    return hasKey(tmpKey);
}

bool BDictionary::hasKey(key_type key) {
    // mapped_type tmp = itemMap[key];
    if (itemMap.find(key) == itemMap.end()) {
       return false;
    }

    return true;
}

} // namespace bencoding
