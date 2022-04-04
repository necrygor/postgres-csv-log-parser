//
// Created by berkay on 3.04.2022.
//

#ifndef POSTGRES_CSV_PARSER_HELPERUTILS_H
#define POSTGRES_CSV_PARSER_HELPERUTILS_H

#include <string>
#include <sstream>


class HelperUtils {
public:
    static std::string get_timestamp_from_datetime(std::string datetime) {
        std::stringstream ss;
        int year    = std::stol(datetime.substr(0, 4));
        int month   = std::stol(datetime.substr(5, 2));
        int day     = std::stol(datetime.substr(8, 2));
        int hour    = std::stol(datetime.substr(11, 2));
        int minute  = std::stol(datetime.substr(14, 2));
        int second  = std::stol(datetime.substr(17, 2));

        // figure out how many leap years and add days * seconds

        year = year - 1970;

        long timestamp = (year * 365 * 24 * 60 * 60) + (month * 30 * 24 * 60 * 60) + (day * 24 * 60 * 60) + (hour * 60 * 60) + (minute * 60) + second;
        ss << timestamp;
        return ss.str();
    }
};


#endif //POSTGRES_CSV_PARSER_HELPERUTILS_H
