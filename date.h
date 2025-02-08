#ifndef Date_h
#define Date_h

#include <ctime>
#include <string>
#include <iostream>
#include <format>

typedef long Seconds;
#define SECONDS_IN_DAY 60*60*24 //86'400
#define SECONDS_IN_HOUR 60*60
#define SECONDS_IN_YEAR SECONDS_IN_DAY*365
#define SECONDS_IN_LEAP_YEAR SECONDS_IN_DAY*366
#define SECONDS_IN_MINUTE 60

// const int SECONDS_IN_YEAR=SECONDS_IN_DAY*365;
// const int SECONDS_IN_LEAP_YEAR=SECONDS_IN_DAY*366;
// const int SECONDS_IN_MINUTE=60;

/**
 * Limitations: ignores leap seconds as most unix time does. This means it differs from UTC time slightly by under 1 minute.
 */
class Date {
public:
    Date();
    Date(int year, int month, int day);

    static int now(); //gets unix time for now
    
    Seconds getUnixTime() const;
    void setUnixTime(Seconds newUnixTime);
    double getUTCOffset() const;
    void setUTCOffset(double);
    
    int getYear() const;
    int getMonth() const; //2 for feb
    int getDay() const;

    std::string toString() const;
    std::string toString24HourFormat() const;
    std::string toDateString() const;
private:
    Seconds unixTime; //seconds since 1/1/1970 12:00 UTC
    double utcOffset; //in hours

    // Time fields
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    
    bool isLeapYear(int year) const;
    int daysInMonth(int month, bool leapYear) const;

    void initializeAllVariables();
    void updateTimeFieldsWithUnixTime();
    std::string displayNum(int num) const;
};

std::ostream& operator<<(std::ostream&, Date);
bool operator==(Date, Date);

#endif // Date_h
