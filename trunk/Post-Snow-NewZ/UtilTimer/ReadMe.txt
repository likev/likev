//
//  UtilTimer ReadMe.txt
//
//  Created by Setsu on 5/27/2010.
//  Copyright 2010 RoundSquare Inc. All rights reserved.
//

//----------------------------------------
// What is UtilTimer?
//----------------------------------------
Sample code which uses Poco::Util::Timer.
   http://pocoproject.org/docs/Poco.Util.Timer.html

//----------------------------------------
// Building on Linux
//----------------------------------------
1. bootstrap
     chmod +x bootstrap
     ./bootstrap
2. configure
    for debug build:
     CXXFLAGS="-g -D_DEBUG -Wall" ./configure --cache=/dev/null --prefix=/usr
    for release build:
     CXXFLAGS="-O2 -Wall" ./configure --cache=/dev/null --prefix=/usr
3. make
     make

//----------------------------------------
// Building on Mac OS X
//----------------------------------------
1. bootstrap
     cat bootstrap | sed s/libtoolize/glibtoolize/ > bootstrap.mac
     chmod +x bootstrap.mac
     ./bootstrap.mac
2. configure
    for debug build:
     CXXFLAGS="-g -D_DEBUG -Wall" ./configure --cache=/dev/null --prefix=/usr
    for release build:
     CXXFLAGS="-O2 -Wall" ./configure --cache=/dev/null --prefix=/usr
3. make
     make

//----------------------------------------
// Building on Windows
//  NOTE: Assuming environment variable POCO_BASE is properly defined.
//----------------------------------------
Open UtilTimerTest.sln file from VC++, then build and run it.

//----------------------------------------
// Console output for UtilTimerTest
//  NOTE: Number in bracket indicates threadID
//----------------------------------------
[0] UtilTimerTest start
[0] --- schedule ---
[1]   MyTimerTask::onTimer() called
[0]     execution delay from scheduled: 259usec
[0] --- schedule fixed rate ---
[1]   MyTimerTask::onTimer() called
[0]     delay   : 500.117msec
[1]   MyTimerTask::onTimer() called
[0]     interval: 500.236msec
[1]   MyTimerTask::onTimer() called
[0]     interval: 500.253msec
[0] --- schedule interval ---
[1]   MyTimerTask::onTimer() called
[0]     delay   : 500.170msec
[1]   MyTimerTask::onTimer() called
[0]     interval: 600.252msec
[1]   MyTimerTask::onTimer() called
[0]     interval: 600.240msec
[0] UtilTimerTest end
