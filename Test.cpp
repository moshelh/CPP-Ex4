/**
 * A demo program for bull-pgia.
 * 
 * @author Erel Segal-Halevi
 * @since  2019-04
 */



#include <iostream>
using namespace std;

#include "play.hpp"
#include "DummyChoosers.hpp"
#include "DummyGuessers.hpp"
#include "SmartGuesser.hpp"
#include "badkan.hpp"

#define COMMA ,

using namespace bullpgia;

int main() {

	badkan::TestCase testcase;
	int grade=0;
	int signal = setjmp(badkan::longjmp_buffer);
	if (signal == 0) {

		// BASIC TESTS - DO NOT CHANGE
		ConstantChooser c1234{"1234"}, c12345{"12345"}, c9999{"9999"};
		ConstantGuesser g1234{"1234"}, g12345{"12345"}, g9999{"9999"};

        ConstantGuesser myg5678{"5678"},myg44445{"44445"},myg1{"1"};
        ConstantChooser myc5678{"5678"}, myc44445{"44445"}, myc1{"1"};

		testcase.setname("Calculate bull and pgia")
		.CHECK_OUTPUT(calculateBullAndPgia("1234","1234"), "4,0")      // 4 bull, 0 pgia
		.CHECK_OUTPUT(calculateBullAndPgia("1234","4321"), "0,4")      // 0 bull, 4 pgia
		;

		testcase.setname("Play with dummy choosers and guessers")
		.CHECK_EQUAL(play(c1234, g1234, 4, 100), 1)      // guesser wins in one turn.
		.CHECK_EQUAL(play(c1234, g9999, 4, 100), 101)    // guesser loses by running out of turns 
		.CHECK_EQUAL(play(c1234, g12345, 4, 100), 101)   // guesser loses technically by making an illegal guess (too long).
		.CHECK_EQUAL(play(c12345, g1234, 4, 100), 0)     // chooser loses technically by choosing an illegal number (too long).
		;
        testcase.setname("My Test-Calculate bull and pgia")
        .CHECK_OUTPUT(calculateBullAndPgia("1111","1234"), "1,0")
        .CHECK_OUTPUT(calculateBullAndPgia("1111","1111"), "4,0")
        .CHECK_OUTPUT(calculateBullAndPgia("1234","1324"), "2,2")
        .CHECK_OUTPUT(calculateBullAndPgia("12345","15342"), "3,2")
        .CHECK_OUTPUT(calculateBullAndPgia("1423","1234"), "1,3")
        .CHECK_OUTPUT(calculateBullAndPgia("1","2"), "0,0")
        .CHECK_OUTPUT(calculateBullAndPgia("9999","1234"), "0,0")
        .CHECK_OUTPUT(calculateBullAndPgia("12","21"), "0,2")
        .CHECK_OUTPUT(calculateBullAndPgia("1234567","1234568"), "6,0")
        .CHECK_OUTPUT(calculateBullAndPgia("12345","43215"), "1,4")
        .CHECK_OUTPUT(calculateBullAndPgia("2214","3721"), "0,2")
        .CHECK_OUTPUT(calculateBullAndPgia("3721","2214"), "0,2")
        .CHECK_OUTPUT(calculateBullAndPgia("5222","2552"), "1,2")
        ;
        testcase.setname("My Test")
        .CHECK_EQUAL(play(myc5678,myg5678 , 4, 100),1)
        .CHECK_EQUAL(play(myc1, myg5678, 1, 100), 101)
        .CHECK_EQUAL(play(myc1, myg1, 1, 100), 1)
        .CHECK_EQUAL(play(myc44445, myg5678, 5, 100), 101)
        .CHECK_EQUAL(play(myc44445, myg44445, 5, 100), 1)
        ;
        testcase.setname("Play with smart guesser");
		RandomChooser randy;
		SmartGuesser smarty;
		for (uint i=0; i<100; ++i) {
			testcase.CHECK_EQUAL(play(randy, smarty, 4, 100)<=100, true);  // smarty should always win in at most 10 turns!
		}
        //Length less than 4
        int wordLength;
        int maxGuesses;
        for (uint i = 0; i < 100; ++i) {
            testcase.CHECK_EQUAL(play(randy, smarty, wordLength, 100)<=maxGuesses, true);
        }
        //Length more than 4
        int wordLength2;
        int maxGuesses2;
        for (uint i = 0; i < 100; ++i) {
            testcase.CHECK_EQUAL(play(randy, smarty, wordLength2, 100)<=maxGuesses2, true);
        }
    grade = testcase.grade();
	} else {
		testcase.print_signal(signal);
		grade = 0;
	}
	cout << "Your grade is: "  << grade << endl;
	return 0;
}

