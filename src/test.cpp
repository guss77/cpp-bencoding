/**
* @file      main.cpp
* @copyright (c) 2020 by Evan Zhang (pingplus@gmail.com) and contributors
* @license   BSD, see the @c LICENSE file for more details
* @brief     
*/
#include "BDictionary.h"
#include "BString.h"
#include <memory>
#include <iostream>
#include "PrettyPrinter.h"
#include "BList.h"

using namespace std;
using namespace bencoding;

const int SIZE = 10;

class safearay
{
private:
    int arr[SIZE];
public:
    safearay()
    {
        int i;
        for(i = 0; i < SIZE; i++)
        {
            arr[i] = i;
        }
    }
    int& operator[](const int &i)
    {
        if( i > SIZE )
        {
            cout << "索引超过最大值" <<endl;
            // 返回第一个元素
            return arr[0];
        }
        return arr[i];
    }
};

int main() {
    shared_ptr<BDictionary> dict = BDictionary::create();

    shared_ptr<BString> key2 = shared_ptr<BString>(BString::create("key2"));
    shared_ptr<BString> value2 = shared_ptr<BString>(BString::create("value2"));
    shared_ptr<BDictionary> d1 = shared_ptr<BDictionary>(BDictionary::create({{key2, value2}}));

    shared_ptr<BString> key3 = shared_ptr<BString>(BString::create("key3"));
    shared_ptr<BString> value3 = shared_ptr<BString>(BString::create("value3"));

    auto deft = dict->setDefault("key2", value2);
    cout << getPrettyRepr(dict)  << endl;
    cout << getPrettyRepr(deft)  << endl;

    deft = dict->setDefault("key2", value2);
    cout << getPrettyRepr(dict)  << endl;
    cout << getPrettyRepr(deft)  << endl;

    deft = dict->setDefault("key3", value3);
    cout << getPrettyRepr(dict)  << endl;
    cout << getPrettyRepr(deft)  << endl;

    cout << dict->hasKey("key2") << endl;

    cout<< (*dict)["key2"]->as<BString>()->value()->c_str() << endl;

    shared_ptr<BString> value4 = shared_ptr<BString>(BString::create("value4"));
    (*dict)["key4"] = value4;
    cout<< (*dict)["key4"]->as<BString>()->value()->c_str() << endl;

    dict->erase("key4");

    auto vl = BList::create({
        BString::create("abcd"),
        BString::create("1234")
    });

    cout << *(*vl)[1]->as<BString>()->value() << endl;

    return 0;
}

