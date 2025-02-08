#include "date.h"

bool Date::isLeapYear(int year) const {
    bool out=false;
    if (year%4==0) //2024 is leap year
        out=true;
    if (year%100==0) //1900 is not leap year
        out=false;
    if (year%400==0) //2000 is leap year
        out=true;
    return out;
}

int Date::daysInMonth(int month, bool leapYear) const {
    // 30 days hath september, april, june, and november
    switch (month) {
        case 9: case 4: case 6: case 11:
            return 30;
        case 2:
            return leapYear ? 29 : 28;
        default:
            return 30;
    }
}

void Date::initializeAllVariables() { //avoid garbage values from uninitialized variables
    unixTime=0;
    utcOffset=0;
    
    year=1970;
    month=1;
    day=1;
    hour=0;
    minute=0;
    second=0;
}

Date::Date() {
    initializeAllVariables();
    unixTime=now();
    updateTimeFieldsWithUnixTime();
}

int Date::now() {
    return time(NULL);
}

double Date::getUTCOffset() const {
    return utcOffset;
}

void Date::setUTCOffset(double newUTCOffset) {
    utcOffset=newUTCOffset;
    updateTimeFieldsWithUnixTime();
}


// TODO: Date::Date(int year, int month, int day)

Seconds Date::getUnixTime() const {
    return unixTime;
}

void Date::setUnixTime(Seconds newUnixTime) {
    unixTime=newUnixTime;
    updateTimeFieldsWithUnixTime();
}

void Date::updateTimeFieldsWithUnixTime() {
    Seconds remaining=unixTime+utcOffset*SECONDS_IN_HOUR; //remaining seconds
    year=1970;
    while (remaining>SECONDS_IN_YEAR) {
        if (isLeapYear(year))
            remaining-=SECONDS_IN_LEAP_YEAR;
        else
            remaining-=SECONDS_IN_YEAR;
        year++;
    }
    month=1;
    bool iLY=isLeapYear(year);
    while (true) {
        auto secondsInMonth=daysInMonth(month, iLY)*SECONDS_IN_DAY;
        if (remaining>secondsInMonth) {
            remaining-=secondsInMonth;
            month++;
        } else {
            break;
        }
    }
    day=1;
    while (remaining>SECONDS_IN_DAY) {
        day++;
        remaining-=SECONDS_IN_DAY;
    }
    hour=0;
    while (remaining>SECONDS_IN_HOUR) {
        hour++;
        remaining-=SECONDS_IN_HOUR;
    }
    minute=0;
    while (remaining>SECONDS_IN_MINUTE) {
        minute++;
        remaining-=SECONDS_IN_MINUTE;
    }
    second=remaining;

    return;

    /*
        Unix time starts 1/1/1970 12am UTC
        Pseudocode:
        remainingSeconds = time(NULL)
        let seconds in year = seconds in day * 365
        let seconds in leap year = seconds in day * 365
        year=1970
        while remainingSeconds >= seconds in year
            if year is leap year
                remainingSeconds -= seconds in leap year
            else
                remainingSeconds -= seconds in year
            year++
        month = 1 // 1 for jan
        secondsInMonth()
        while remainingSeconds > seconds in month
    */
}

int Date::getYear() const {
    return year;
}
int Date::getMonth() const {
    return month;
}
int Date::getDay() const {
    return day;
}

std::string Date::toString() const {
    if (hour<13) {
        return std::format("{}/{}/{} at {}:{}:{} AM", month, day, year, hour, displayNum(minute), displayNum(second)); //requires C++20
    } else {
        return std::format("{}/{}/{} at {}:{}:{} PM", month, day, year, hour-12, displayNum(minute), displayNum(second)); //requires C++20
    }
}

std::string Date::toString24HourFormat() const {
    return std::format("{}/{}/{} at {}:{}:{}", month, day, year, displayNum(hour), displayNum(minute), displayNum(second));
}

std::string Date::toDateString() const {
    return std::format("{}/{}/{}", month, day, year); //requires C++20
}

std::ostream& operator<<(std::ostream& os, Date d) {
    os << d.toString();
    return os;
}

bool operator==(Date d1, Date d2) {
    return d1.getUnixTime()==d2.getUnixTime();
}

std::string Date::displayNum(int num) const {
    if (num==0)
        return "00";
    if (num>0 && num<10)
        return "0"+std::to_string(num);
    return std::to_string(num);
}
