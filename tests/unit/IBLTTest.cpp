//
// Created by eliez on 7/17/2018.
//

#include <climits>
#include "IBLTTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(IBLTTest);

IBLTTest::IBLTTest() {
}

IBLTTest::~IBLTTest() {
}

void IBLTTest::setUp() {
    const int SEED = 617;
    srand(SEED);
}

void IBLTTest::tearDown() {
}

void IBLTTest::testAll() {
    vector<pair<ZZ, ZZ>> items;
    const int SIZE = 50; // should be even

    const size_t ITEM_SIZE = sizeof(randZZ());
    for(int ii = 0; ii < SIZE; ii++) {
        items.push_back({randZZ(), randZZ()});
    }

    IBLT iblt(SIZE, ITEM_SIZE);
    for(int ii=0; ii < SIZE/2; ii++) {
        iblt.insert(items.at(ii).first, items.at(ii).second);
    }

    for(int ii=SIZE/2; ii < SIZE; ii++) {
        iblt.erase(items.at(ii).first, items.at(ii).second);
    }

    for(int ii=0; ii < SIZE; ii++) {
        IBLT ibltCopy(iblt); // make a copy each time because getting is destructive
        auto pair = items.at(ii);
        ZZ value;
        CPPUNIT_ASSERT(ibltCopy.get(pair.first, value));
        CPPUNIT_ASSERT_EQUAL(pair.second, value);
    }

    vector<pair<ZZ, ZZ>> plus={}, minus={};
    CPPUNIT_ASSERT(iblt.listEntries(plus, minus));
    CPPUNIT_ASSERT_EQUAL(items.size(), plus.size() + minus.size());
}

void IBLTTest::difTest(){
    vector<pair<ZZ, ZZ>> items;
    const int SIZE = 500; // should be even

    const size_t ITEM_SIZE = sizeof(randZZ());
    for(int ii = 0; ii < SIZE; ii++) {
        items.push_back({randZZ(), randZZ()});
    }

    IBLT ibltA(SIZE/20, ITEM_SIZE);
    IBLT ibltB(SIZE/20, ITEM_SIZE);
    for(int ii=0; ii < SIZE; ii++) {
        ibltA.insert(items.at(ii).first, items.at(ii).second);
    }

    for(int ii=SIZE/20; ii < SIZE; ii++) {
        ibltB.insert(items.at(ii).first, items.at(ii).second);
    }
    vector<pair<ZZ, ZZ>> plus={}, minus={};
    CPPUNIT_ASSERT(not ibltA.listEntries(plus,minus));
    ibltA-=ibltB;
    plus.clear();
    minus.clear();
    CPPUNIT_ASSERT(ibltA.listEntries(plus,minus));

}