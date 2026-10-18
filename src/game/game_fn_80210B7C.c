/* GetDates (Dolphin SDK OS/OSTime.c) */

typedef int BOOL;

typedef struct OSCalendarTime {
    int sec;
    int min;
    int hour;
    int mday;
    int mon;
    int year;
    int wday;
    int yday;
    int msec;
    int usec;
} OSCalendarTime;

#define MONTH_MAX 12
#define WEEK_DAY_MAX 7
#define YEAR_DAY_MAX 365

extern int YearDays[MONTH_MAX]; /* YearDays */
extern int LeapYearDays[MONTH_MAX]; /* LeapYearDays */

static inline BOOL IsLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

static inline int GetLeapDays(int year) {
    if (year < 1) {
        return 0;
    }
    return (year + 3) / 4 - (year - 1) / 100 + (year - 1) / 400;
}

void GetDates(int days, OSCalendarTime *td) {
    int year;
    int n;
    int month;
    int *p_days;

    td->wday = (days + 6) % WEEK_DAY_MAX;

    for (year = days / YEAR_DAY_MAX; days < (n = year * YEAR_DAY_MAX + GetLeapDays(year)); year--) {
        ;
    }
    days -= n;
    td->year = year;
    td->yday = days;

    p_days = IsLeapYear(year) ? LeapYearDays : YearDays;
    for (month = MONTH_MAX; days < p_days[--month];) {
        ;
    }
    td->mon = month;
    td->mday = days - p_days[month] + 1;
}
