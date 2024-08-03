#pragma once
#include "clsDate.h"

class clsPeriod
{
public:
    clsDate StartDate;
    clsDate EndDate;

    clsPeriod(clsDate StartDate, clsDate DateTo)
    {
        this->StartDate = StartDate;
        this->EndDate = EndDate;
    }

    static bool IsOverlapPeriods(clsPeriod Period1, clsPeriod Period2)
    {

        if (
            clsDate::CompareDates(Period2.EndDate, Period1.StartDate) == clsDate::enDateCompare::Before ||
            clsDate::CompareDates(Period2.StartDate, Period1.EndDate) == clsDate::enDateCompare::After)
            return false;
        else
            return true;
    }

    bool IsOverLapWith(clsPeriod Period2)
    {
        return IsOverlapPeriods(*this, Period2);
    }

    void Print()
    {
        cout << "Period Start: ";
        StartDate.Print();

        cout << "Period End: ";
        EndDate.Print();
    }

    static int PeriodLengthInDays(clsPeriod Period1, bool isIncludingEndDay = false)
    {
        int Days = 0;

        while (clsDate::IsDate1BeforeDate2(Period1.StartDate, Period1.EndDate))
        {
            Days++;
            Period1.StartDate = clsDate::AddOneDay(Period1.StartDate);
        }

        return isIncludingEndDay == true ? ++Days : Days;
    }

    int PeriodLengthInDays(bool isIncludingEndDay = false)
    {
        return PeriodLengthInDays(*this);
    }

    static bool isDateWithinPeriod(clsPeriod Period1, clsDate CheckDate)
    {

        if (clsDate::IsDate1BeforeDate2(CheckDate, Period1.EndDate) && clsDate::CompareDates(CheckDate, Period1.StartDate) == 1)
        {
            return true;
        }
        return false;
    }

    bool isDateWithinPeriod(clsDate Date)
    {
        return isDateWithinPeriod(*this, Date);
    }

    static int CountOverlapDays(clsPeriod Period1, clsPeriod Period2)
    {
        int Period1Lenghth = PeriodLengthInDays(Period1);
        int Period2Lenghth = PeriodLengthInDays(Period2);
        int CountOverlap = 0;

        if (!IsOverlapPeriods(Period1, Period2))
        {
            return CountOverlap;
        }

        if (Period1Lenghth < Period2Lenghth)
        {
            while (clsDate::IsDate1BeforeDate2(Period1.StartDate, Period1.EndDate))
            {
                if (isDateWithinPeriod(Period2, Period1.StartDate))
                {
                    CountOverlap++;
                }
                Period1.StartDate = clsDate::AddOneDay(Period1.StartDate);
            }
        }

        else
        {
            while (clsDate::IsDate1BeforeDate2(Period2.StartDate, Period2.EndDate))
            {
                if (isDateWithinPeriod(Period1, Period2.StartDate))
                {
                    CountOverlap++;
                }
                Period2.StartDate = clsDate::AddOneDay(Period2.StartDate);
            }
        }

        return CountOverlap;
    }

    int CountOverlapDays(clsPeriod Period)
    {
        return CountOverlapDays(*this, Period);
    }
};
