//
//  helper.hpp
//  mxl2ly
//
//  Created by Reventar on 17/11/2021.
//

#ifndef helper_hpp
#define helper_hpp

#include <vector>

template <class InputIt, class T>
constexpr inline bool is_element(InputIt first, InputIt last, const T& value) {
    for (; first != last; ++first) {
        if (*first == value) {
            return true;
        }
    }
    return false;
}

const std::vector<std::string> number_names{"zero",  "one",  "two", "three",
                                            "four",  "five", "six", "seven",
                                            "eight", "nine"};
const inline std::string       convert_number_names(const std::string test) {
    std::string returner;
    for (auto ch : test) {
        // if ch is any number from 0 to 9
        if (ch - '0' >= 0 && ch - '9' <= 0) {
            returner += number_names.at(ch - '0');
        } else {
            returner += ch;
        }
    }
    return returner;
}
const inline std::string convert_number_names(const int test) {
    if (test < 0 || test > 9) {
        return "";
    }
    return number_names.at(test);
}

namespace lmt {
class Length {
  public:
    operator long double() { return this->length_millimeters; }
    operator double() { return static_cast<double>(this->length_millimeters); }
    operator float() { return static_cast<float>(this->length_millimeters); }

    long double get_millimeters() const { return length_millimeters; }
    long double get_inches() const { return length_millimeters / 25.4; }
    long double get_points() const { return length_millimeters * 2.835; }

    friend Length millimeters(long double d);
    friend Length inches(long double d);
    friend Length points(long double d);
    friend Length tenths(long double amt, long double conversion);

  private:
    Length(double length_millimeters)
        : length_millimeters(length_millimeters){};

    const long double length_millimeters;
};

inline Length millimeters(long double d) { return Length(d); }

inline Length inches(long double d) { return Length(d * 25.4); }

inline Length points(long double d) { return Length(d / 2.835); }

inline Length tenths(long double amt, long double conversion) {
    return Length(amt * conversion);
}

enum class StartStopType { Start, Stop, Both };
} // namespace lmt

#endif /* helper_hpp */
