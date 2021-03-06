#include "commandlinemanager.h"
#include <stdio.h>
#include <stdlib.h>

static const char FLAG_EPSILON = 'e';
static const char FLAG_DISTANCE = 'd';
static const char FLAG_REFERENCE_PATH = 'r';
static const char FLAG_DATA_PATH = 'i';
static const char FLAG_USERS = 'n';
static const char FLAG_FRAMES = 'f';
static const char * FLAG_ENABLE_DOUBLE_ZONE = "enable-double-zone";
static const char * FLAG_PRINT_VERBOSE = "verbose";
static const char * METHOD = "method";

using namespace std;

CommandLineManager::CommandLineManager( int argc, char **argv ) {

    bool epsilonIsSet = false;
    bool distanceIsSet = false;
    bool referenceIsSet = false;
    bool dataIsSet = false;
    bool usersIsSet = false;
    bool framesIsSet = false;

    doubleZoneIsEnable = false;
    printVerboseEnable = false;

    int c;
    while( true ) {
        int option_index = 0;

        static struct option long_options[] = {
            { FLAG_ENABLE_DOUBLE_ZONE, no_argument, 0, 0 },
            { METHOD, required_argument, 0, 1 },
            { FLAG_PRINT_VERBOSE, no_argument, 0, 'v' }
        };

        c = getopt_long( argc, argv, "e:d:r:i:n:f:", long_options, &option_index );
        if( c == -1 ) {
            break;
        }

        switch(c) {
        case 0:
            doubleZoneIsEnable = true;
            break;

        case 1:
            method = optarg;
            break;

        case 'v':
            printVerboseEnable = true;
            break;

        case FLAG_EPSILON:
            epsilonIsSet = true;
            epsilon = atof(optarg);
            break;

        case FLAG_DISTANCE:
            distanceIsSet = true;
            distance = atoi(optarg);
            break;

        case FLAG_REFERENCE_PATH:
            referenceIsSet = true;
            referencePath = optarg;
            break;

        case FLAG_DATA_PATH:
            dataIsSet = true;
            dataPath = optarg;
            break;

        case FLAG_USERS:
            usersIsSet = true;
            users = atoi(optarg);
            break;

        case FLAG_FRAMES:
            framesIsSet = true;
            frames = atoi(optarg);
            break;
        }
    }

    bool validInput;
    if( method != "bhi" && method != "cus") {
        validInput = false;
        cout << "ERROR! Invalid evaluation method." << endl;
        cout << "Possible values are: bhi, cus" << endl;
    }
    else if( method == "bhi" && epsilonIsSet && distanceIsSet && referenceIsSet && dataIsSet && usersIsSet && framesIsSet || // Valid input for BHI
            method == "cus" && epsilonIsSet && !distanceIsSet && referenceIsSet && dataIsSet && usersIsSet && framesIsSet) { // Valid input for CUS
        validInput = true;
    }
    else {
        validInput = false;
        cout << "ERROR! Run BHI or CUS evaluation method:" << endl;
        cout << "./osm --method bhi -e [epsilon] -d [distance] -n [users count] -r [reference path] -i [data path]" << endl;
        cout << "./osm --method cus -e [epsilon] -n [users count] -r [reference path] -i [data path]" << endl;
        cout << "Optional flags: --enable-double-zone (BHI only) --verbose" << endl;
    }

    this->validInput = validInput;
}

float CommandLineManager::getEpsilon() {
    return this->epsilon;
}

int CommandLineManager::getDistance() {
    return this->distance;
}

int CommandLineManager::getUsersNumber() {
    return this->users;
}

int CommandLineManager::getFramesNumber() {
    return this->frames;
}

string CommandLineManager::getReferencePath() {
    return this->referencePath;
}

string CommandLineManager::getDataPath() {
    return this->dataPath;
}

string CommandLineManager::getMethod() {
    return this->method;
}

bool CommandLineManager::isDoubleEnabled() {
    return this->doubleZoneIsEnable;
}

bool CommandLineManager::isPrintVerbose() {
    return this->printVerboseEnable;
}

bool CommandLineManager::isInputValid() {
    return this->validInput;
}
