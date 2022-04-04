//
// Created by berkay on 3.04.2022.
//

#ifndef POSTGRES_CSV_PARSER_HELPERUTILS_H
#define POSTGRES_CSV_PARSER_HELPERUTILS_H

#include <string>


class HelperUtils {
public:
    static long get_timestamp_from_datetime(std::string datetime) {
        int year    = std::stol(datetime.substr(0, 4));
        int month   = std::stol(datetime.substr(5, 2));
        int day     = std::stol(datetime.substr(8, 2));
        int hour    = std::stol(datetime.substr(11, 2));
        int minute  = std::stol(datetime.substr(14, 2));
        int second  = std::stol(datetime.substr(17, 2));

        // figure out how many leap years and add days * seconds

        long timestamp = (year * 365 * 24 * 60 * 60) + (month * 30 * 24 * 60 * 60) + (day * 24 * 60 * 60) + (hour * 60 * 60) + (minute * 60) + second;
        return timestamp;
    }
};


#endif //POSTGRES_CSV_PARSER_HELPERUTILS_H
