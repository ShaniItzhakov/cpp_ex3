#include "doctest.h"
#include "NumberWithUnits.hpp"
using namespace ariel;

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
using namespace std;


TEST_CASE("Test operator functions") {
    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);

    if (units_file.fail() || units_file.bad()) {
        FAIL("Error in file");
    }

    string unit1;
    string unit2;
    double unitNumber;

    units_file.ignore(1);
    units_file >> unit1;
    units_file.ignore(2);
    units_file >> unitNumber >> unit2;

    units_file.close();

    cout << "unit1: " << unit1 << ", unitNumber: " << unitNumber << ", unit2: " << unit2 << endl;

    NumberWithUnits a{3, unit1};
    NumberWithUnits b{5, unit2};
    NumberWithUnits c{6, unit1};

    // Test with same unit + and - operators
    CHECK((a + c) == NumberWithUnits{9, unit1});
    CHECK((a - c) == NumberWithUnits{-3, unit1});
    CHECK((c - a) == NumberWithUnits{3, unit1});

    // Test with different unit + and - operators
    CHECK((a + b) == NumberWithUnits{(3*unitNumber + 5), unit1});
    CHECK((a + b) == NumberWithUnits{3 + 5/unitNumber, unit2});
    CHECK((a - b) == NumberWithUnits{(3*unitNumber - 5), unit1});
    CHECK((a - b) == NumberWithUnits{3 - 5/unitNumber, unit2});


    // Boolean checks

    // Test with same unit
    CHECK((c > a) == true);
    CHECK((a >= c) == false);
    CHECK((c < a) == false);
    CHECK((a <= c) == true);
    CHECK((c == a) == false);
    CHECK((a != c) == true);

    // Test with different unit
    CHECK((a > b) == false);
    CHECK((a >= b) == false);
    CHECK((a < b) == true);
    CHECK((b <= c) == true);
    CHECK((c != b) == true);

    // Test ++ (increment) and -- (decrement) operators as prefix and postfix when a = 3, b = 5, c = 6
    CHECK((a++) == NumberWithUnits{3, unit1});             
    CHECK((a) == NumberWithUnits{4, unit1});
    CHECK((b) == NumberWithUnits{5, unit2});
    CHECK((++b) == NumberWithUnits{6, unit2});
    CHECK((c--) == NumberWithUnits{6, unit1});
    CHECK((c) == NumberWithUnits{5, unit1});
    CHECK((b) == NumberWithUnits{5, unit2});
    CHECK((--b) == NumberWithUnits{4, unit2});

    cout << "a++: " << a++ << "b++: " << b++ << "c++: " << c++ << endl;
    cout << "++a: " << ++a << "++b: " << ++b << "++c: " << ++c << endl;

    cout << "a--: " << a-- << "b--: " << b-- << "c--: " << c-- << endl;
    cout << "--a: " << --a << "--b: " << --b << "--c: " << --c << endl;


    // Test unary plus and unary minus on different units
    CHECK((+a) == NumberWithUnits{4, unit1});             
    CHECK((-a) == NumberWithUnits{-4, unit1});
    CHECK((+b) == NumberWithUnits{4, unit2});             
    CHECK((-b) == NumberWithUnits{-4, unit2});             
    CHECK((+c) == NumberWithUnits{5, unit1});
    CHECK((-c) == NumberWithUnits{-5, unit1});


    NumberWithUnits d{1, unit1};
    NumberWithUnits e{3, unit2};
    NumberWithUnits f{5.3, unit1};

    // Test operator * with double and NumberWithUnits

    CHECK((d * 3) == NumberWithUnits{3, unit1});
    CHECK((2 * d) == NumberWithUnits{2, unit1});
    CHECK((f * 5) == NumberWithUnits{26.5, unit1}); 
    CHECK((2.3 * f) == NumberWithUnits{12.19, unit1}); 
    CHECK((e * 4) == NumberWithUnits{12, unit2});
    CHECK((1 * e) == NumberWithUnits{3, unit2});

    // Test with same unit += and -= operators
    d += f;
    CHECK((d) == NumberWithUnits{6.3, unit1});
    d -= f;
    CHECK((d) == NumberWithUnits{1, unit1});
    f -= d;
    CHECK((f) == NumberWithUnits{4.3, unit1});

    // Test with different unit += and -= operators           
    d += e;
    CHECK((d) == NumberWithUnits{(1*unitNumber + 3), unit1});
    CHECK((d) == NumberWithUnits{1 + 3/unitNumber, unit2});
    d -= e;
    CHECK((d) == NumberWithUnits{1*unitNumber, unit1});
    CHECK((d) == NumberWithUnits{1, unit2});

   // Test << (output) and >> (input) operators
    NumberWithUnits u1{5, "ton"};
    istringstream sample_input{"3[kg]"};
    sample_input >> u1;
    CHECK(NumberWithUnits{3, "kg"} == u1);
    ostringstream sample_output;
    sample_output << u1;
    CHECK(sample_output.str() == "3[kg]");
}

TEST_CASE("Test custom file") {
    ofstream custom_file{"custom_file.txt"};  
    custom_file << "1 hour = 60 min" << endl;
    custom_file << "1 min = 60 min" << endl;
    custom_file << "1 EUR = 1.19 USD" << endl;
    custom_file << "1 USD = 3.33 ILS" << endl;  
    custom_file.close();

    ifstream units_file{"custom_file.txt"};
    NumberWithUnits::read_units(units_file);

    if (units_file.fail() || units_file.bad()) {
        FAIL("Error in file");
    }

    string unit1;
    string unit2;
    double unitNumber;

    NumberWithUnits a{2, unit1};
    NumberWithUnits b{4, unit2};
    NumberWithUnits c{1, unit1};

    // Test with same unit + and - operators
    CHECK((a + c) == NumberWithUnits{3, unit1});
    CHECK((a - c) == NumberWithUnits{1, unit1});
    CHECK((c - a) == NumberWithUnits{-1, unit1});

    // Test with different unit + and - operators                                           
    CHECK((a + b) == NumberWithUnits{(2*unitNumber + 4), unit1});
    CHECK((a + b) == NumberWithUnits{2 + 4/unitNumber, unit2});
    CHECK((a - b) == NumberWithUnits{(2*unitNumber - 4), unit1});
    CHECK((a - b) == NumberWithUnits{2 - 4/unitNumber, unit2});


    // Boolean checks

    // Test with same unit
    CHECK((c > a) == false);
    CHECK((a >= c) == true);
    CHECK((c < a) == true);
    CHECK((a <= c) == false);
    CHECK((c == a) == false);
    CHECK((a != c) == true);

    // Test with different unit
    CHECK((a > b) == false);
    CHECK((a >= b) == false);
    CHECK((a < b) == true);
    CHECK((b <= c) == false);
    CHECK((c != b) == true);

    // Test ++ (increment) and -- (decrement) operators as prefix and postfix when a = 2, b = 4, c = 1
    CHECK((a++) == NumberWithUnits{2, unit1});             
    CHECK((a) == NumberWithUnits{3, unit1});
    CHECK((b) == NumberWithUnits{4, unit2});
    CHECK((++b) == NumberWithUnits{5, unit2});
    CHECK((c--) == NumberWithUnits{1, unit1});
    CHECK((c) == NumberWithUnits{0, unit1});
    CHECK((b) == NumberWithUnits{4, unit2});
    CHECK((--b) == NumberWithUnits{3, unit2});
    CHECK((++c) == NumberWithUnits{1, unit1});

    cout << "a++: " << a++ << "b++: " << b++ << "c++: " << c++ << endl;
    cout << "++a: " << ++a << "++b: " << ++b << "++c: " << ++c << endl;

    cout << "a--: " << a-- << "b--: " << b-- << "c--: " << c-- << endl;
    cout << "--a: " << --a << "--b: " << --b << "--c: " << --c << endl;


    // Test unary plus and unary minus on different units
    CHECK((+a) == NumberWithUnits{3, unit1});             
    CHECK((-a) == NumberWithUnits{-3, unit1});
    CHECK((+b) == NumberWithUnits{3, unit2});             
    CHECK((-b) == NumberWithUnits{-3, unit2});             
    CHECK((+c) == NumberWithUnits{1, unit1});
    CHECK((-c) == NumberWithUnits{-1, unit1});

    NumberWithUnits d{2, unit1};
    NumberWithUnits e{5, unit2};
    NumberWithUnits f{2.1, unit1};
    
    // Test operator * with double and NumberWithUnits

    CHECK((d * 3) == NumberWithUnits{6, unit1});
    CHECK((1 * d) == NumberWithUnits{2, unit1});
    CHECK((f * 7) == NumberWithUnits{14.7, unit1}); 
    CHECK((2 * f) == NumberWithUnits{4.2, unit1}); 
    CHECK((e * 4.3) == NumberWithUnits{21.5, unit2});
    CHECK((2.1 * e) == NumberWithUnits{10.5, unit2});

    // Test with same unit += and -= operators
    d += f;
    CHECK((d) == NumberWithUnits{4.1, unit1});
    d -= f;
    CHECK((d) == NumberWithUnits{2, unit1});
    f -= d;
    CHECK((f) == NumberWithUnits{0.1, unit1});

    // Test with different unit += and -= operators        
    d += e;
    CHECK((d) == NumberWithUnits{(2*unitNumber + 5), unit1});
    CHECK((d) == NumberWithUnits{2 + 5/unitNumber, unit2});
    d -= e;
    CHECK((d) == NumberWithUnits{2*unitNumber, unit1});
    CHECK((d) == NumberWithUnits{2, unit2});

    // Test << (output) and >> (input) operators
    NumberWithUnits u1{3, "hour"};
    istringstream sample_input{"7[min]"};
    sample_input >> u1;
    CHECK(NumberWithUnits{7, "min"} == u1);
    ostringstream sample_output;
    sample_output << u1;
    CHECK(sample_output.str() == "7[min]");
}

TEST_CASE("Test bad cases") {
    ifstream units_file{"custom_file.txt"};
    NumberWithUnits::read_units(units_file);

    if (units_file.fail() || units_file.bad()) {
        FAIL("Error in file");
    }

    NumberWithUnits u1{3, "hour"};
    NumberWithUnits u2{5, "USD"};

    CHECK_THROWS((u1 + u2));
    CHECK_THROWS((u1 - u2));
    CHECK_THROWS((NumberWithUnits{3, "dog"}));
    CHECK_THROWS((NumberWithUnits{3, "Hour"}));
}