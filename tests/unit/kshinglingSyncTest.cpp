//
// Created by Bowen on 9/24/18.
//
#include <climits>
#include "kshinglingSyncTest.h"
//#include "GenSync.h"
//#include "kshinglingSync.h"
//#include "TestAuxiliary.h"
#include "kshingling.h"  // rest should not be here
#include "CommSocket.h"
#include "InterCPISync.h"
#include "TestAuxiliary.h"

CPPUNIT_TEST_SUITE_REGISTRATION(kshinglingSyncTest);

kshinglingSyncTest::kshinglingSyncTest() {}
kshinglingSyncTest::~kshinglingSyncTest() {}

void kshinglingSyncTest::setUp() {}

void kshinglingSyncTest::tearDown() {}

void kshinglingSyncTest::testAll() {

    int string_len = 500;

    // CPISYNC k = 3 b = 38; k = 4 b = 46; k = 5 b = 54
    size_t shingle_len = 4;
    int editDistance_bar = 7;
    GenSync::SyncProtocol base_set_proto = GenSync::SyncProtocol::IBLTSync;
    //GenSync::SyncProtocol base_set_proto = GenSync::SyncProtocol::CPISync;
    char stopword = '$';
    string Alicetxt = randAsciiStr(string_len);
    string Bobtxt = randStringEdit(Alicetxt, editDistance_bar);
    size_t bits = sizeof(string);

    GenSync Alice = GenSync::Builder().
            setProtocol(GenSync::SyncProtocol::IBLTSync).
            setStringProto(GenSync::StringSyncProtocol::kshinglingSync).
            setComm(GenSync::SyncComm::socket).
            setBits(bits).
            setShingleLen(shingle_len).
            build();

    Alice.addStr(new DataObject(Alicetxt));


    GenSync Bob = GenSync::Builder().
            setProtocol(GenSync::SyncProtocol::IBLTSync).
            setStringProto(GenSync::StringSyncProtocol::kshinglingSync).
            setComm(GenSync::SyncComm::socket).
            setBits(bits).
            setShingleLen(shingle_len).
            build();

    Bob.addStr(new DataObject(Bobtxt));

    string  AliceSyncTxt, BobSyncTxt;

    forkHandleReport report = forkHandle(Alice,Bob,true);

//    CPPUNIT_ASSERT(editDistance_bar * (shingleLen - 1) + 4 >= numDif);

    //number of difference between should alwasy be editDistance_bar*(shingleLen-1)

    //CPISync Setup
    //kshinglingSync kshingling = kshinglingSync(base_set_proto, base_comm, 14+(shingle_len+2)*6,ceil(numDif*2.3), 0,0);

    //InteractiveCPISync Set up
    //kshinglingSync kshingling = kshinglingSync(base_set_proto, base_comm, 14+(shingle_len+2)*6, 7, 3, 0);

    //IBLTSync Setup
    //kshinglingSync kshingling = kshinglingSync(baseSetProto, base_comm, 8, 0, 0, numDif*10);


    //forkHandleReport report = forkHandle(Alice, Bob);

    CPPUNIT_ASSERT(report.success);
    cout << "bits: " + to_string(report.bytes) << endl;
    cout << "bitsTot: " + to_string(report.bytesTot) << endl;
    cout << "bitsR: " + to_string(report.bytesRTot) << endl;



//    syncTest(GenSyncServer, GenSyncClient);

}