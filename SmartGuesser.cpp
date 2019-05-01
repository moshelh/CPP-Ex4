#include "SmartGuesser.hpp"
using namespace bullpgia;

void SmartGuesser::startNewGame(uint length) {
    this->length = length;
    if(length<5 && length>=0) buildSet(length);
    //TODO:
    else {};
}

string SmartGuesser::guess() {
    int randomIndex = rand() % myNumbers.size();
    auto it = myNumbers.begin();
    std::advance(it, randomIndex);
    myGuess = *it;
    return myGuess;
}

void SmartGuesser::learn(string l) {
    auto it = myNumbers.begin();
    while( it != myNumbers.end()) {
        string bullPgia = calculateBullAndPgia(myGuess, *it);
        if(bullPgia != l) {
           it = myNumbers.erase(it);
        }
        else it++;
    }
}

void SmartGuesser::buildSet(uint length) {
    string tmp;
    switch (length) {
        case 0 : return;
        case 1 : {
            for (int i = 0; i < 10; ++i) {
                tmp = to_string(i);
                myNumbers.insert(tmp);
            } break;
        }
        case 2 : {
            for (int i = 0; i < 10; ++i) {
                for (int j = 0; j < 10; ++j) {
                    tmp = to_string(i) + to_string(j);
                    myNumbers.insert(tmp);
                }
            } break;
        }
        case 3 : {
            for (int i = 0; i < 10; ++i) {
                for (int j = 0; j < 10; ++j) {
                    for (int k = 0; k < 10; ++k) {
                        tmp = to_string(i) + to_string(j) + to_string(k);
                        myNumbers.insert(tmp);
                    }
                }
            } break;
        }
        case 4 : {
            for (int i = 0; i < 10; ++i) {
                for (int j = 0; j < 10; ++j) {
                    for (int k = 0; k < 10; ++k) {
                        for (int l = 0; l < 10; ++l) {
                            string number = to_string(i) + to_string(j) + to_string(k) + to_string(l);
                            myNumbers.insert(number);
                        }
                    }
                }
            } break;
        }
    }
}
