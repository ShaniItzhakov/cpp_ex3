#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <map>

namespace ariel {
    class NumberWithUnits {
    private:
        double numOfUnit;
        std::string unitType;
    
    public:
        NumberWithUnits(double value, const std::string &type);
        static void read_units(std::ifstream& units_file);
        NumberWithUnits operator+(const NumberWithUnits &unit) const;
        NumberWithUnits& operator+=(const NumberWithUnits &unit);
        NumberWithUnits operator+() const;
        NumberWithUnits operator-(const NumberWithUnits &unit) const;
        NumberWithUnits& operator-=(const NumberWithUnits &unit);
        NumberWithUnits operator-() const;
        bool operator>(const NumberWithUnits &unit) const;
        bool operator>=(const NumberWithUnits &unit) const;
        bool operator<(const NumberWithUnits &unit) const;
        bool operator<=(const NumberWithUnits &unit) const;
        bool operator==(const NumberWithUnits &unit) const;
        bool operator!=(const NumberWithUnits &unit) const;
        NumberWithUnits& operator++();
        NumberWithUnits operator++(int flag);
        NumberWithUnits& operator--();
        NumberWithUnits operator--(int flag);
        NumberWithUnits operator*(double number) const;
        friend NumberWithUnits operator*(double number, const NumberWithUnits &unit);
        friend std::ostream& operator<<(std::ostream &os, const NumberWithUnits &unit);
        friend std::istream& operator>>(std::istream &is, NumberWithUnits &unit);
    };
}