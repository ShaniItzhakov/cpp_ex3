#include <string>
#include <iostream>
using namespace std;

#include "NumberWithUnits.hpp"

namespace ariel {
    NumberWithUnits::NumberWithUnits(double value, const string &type) : numOfUnit(value), unitType(type){}

    void NumberWithUnits::read_units(ifstream& units_file) {
        cout << "Shani" << endl;
    }

    NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits &unit) const{
        return {0, ""};
    }

    NumberWithUnits& NumberWithUnits::operator+=(const NumberWithUnits &unit) {
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator+() const {
        return {0, ""};
    }

    NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits &unit) const {
        return {0, ""};
    }

    NumberWithUnits& NumberWithUnits::operator-=(const NumberWithUnits &unit) {
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator-() const {
        return {0, ""};
    }

    bool NumberWithUnits::operator>(const NumberWithUnits &unit) const {
        return true;
    }

    bool NumberWithUnits::operator>=(const NumberWithUnits &unit) const {
        return true;
    }

    bool NumberWithUnits::operator<(const NumberWithUnits &unit) const {
        return true;
    }

    bool NumberWithUnits::operator<=(const NumberWithUnits &unit) const {
        return true;
    }

    bool NumberWithUnits::operator==(const NumberWithUnits &unit) const {
        return true;
    }

    bool NumberWithUnits::operator!=(const NumberWithUnits &unit) const {
        return !(*this == unit);
    }

    NumberWithUnits& NumberWithUnits::operator++() {
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator++(int flag) {
        return {0, ""};
    }

    NumberWithUnits& NumberWithUnits::operator--() {
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator--(int flag) {
        return {0, ""};
    }

    NumberWithUnits NumberWithUnits::operator*(double number) const {
        return {0, ""};
    }

    NumberWithUnits operator*(double number, const NumberWithUnits &unit) {
        return {0, ""};
    }

    ostream& operator<<(ostream &os, const NumberWithUnits &unit) {
        return os << unit.numOfUnit << unit.unitType;
    }

    istream& operator>>(istream &is, NumberWithUnits &unit) {
        return is >> unit.numOfUnit >> unit.unitType;
    }
}