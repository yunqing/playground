#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>

struct Date {
  int64_t year;
  int month;
  int day;
  std::string to_str() {
    return std::to_string(year) + "/" + std::to_string(month) + "/" + std::to_string(day);
  }

};

bool is_leap(int64_t year) {
  bool result = false;
  if (year % 400 == 0) {
    result = true;
  } else if (year % 100 == 0) {
    result = false;
  } else if (year % 4 == 0) {
    result = true;
  } else {
    result = false;
  }
  return result;
}

int get_days_of_year(int64_t year) {
  if (is_leap(year)) {
    return 366;
  } else {
    return 365;
  }
}

int get_days_of_400years(){
  int num_leap_years = 0;
  for (int i = 1; i <= 400; i ++) {
    if (is_leap(i)) {
      num_leap_years += 1;
    }
  }
  return 365 * 400 + num_leap_years;
}

int get_days_of_month(int64_t year, int month) {
  int days = 0;
  switch (month) {
    case 2:
      days = is_leap(year) ? 29 : 28;
      break;
    default:
      if (month <= 7) {
        days = month % 2 == 0 ? 30 : 31;
      } else {
        days = month % 2 == 0 ? 31 : 30;
      }
      break;
  }
  return days;
}

int consumed_days_in_this_year(struct Date date) {
  int days = 0;
  // day
  days += date.day;
  // month
  int month = date.month;
  while (month - 1 > 0) {
    days += get_days_of_month(date.year, month - 1);
    month -= 1;
  }
  return days;
}

struct Date get_date(struct Date date, int64_t days) {
  int64_t year = date.year;
  int month = date.month;
  int day = date.day;

  // check by interval 400 years
  int days_400years = get_days_of_400years();
  int64_t num_periods = days / days_400years;
  year += num_periods * 400;
  days = days % days_400years;

  // get year
  int remain_days_this_year =
    get_days_of_year(date.year)
    - consumed_days_in_this_year(date);
  while (true) {
    if (days > remain_days_this_year) {
      year += 1;
      month = 1;
      day = 1;
      days = days - remain_days_this_year - day;
      remain_days_this_year = get_days_of_year(year) - day;
    } else {
      break;
    }
  }

  // get month
  int remain_days_this_month =
    get_days_of_month(year, month) - day;
  while (true) {
    if (days > remain_days_this_month) {
      month += 1;
      day = 1;
      days = days - remain_days_this_month - day;
      remain_days_this_month = get_days_of_month(year, month) - day;
    } else {
      break;
    }
  }

  // get day
  day += days;

  // return result
  struct Date new_date;
  new_date.year = year;
  new_date.month = month;
  new_date.day = day;
  return new_date;
}

int main() {
  std::time_t t = std::time(0);
  std::tm* now = std::localtime(&t);

  struct Date date;
  date.year = now->tm_year + 1900;
  date.month = now->tm_mon + 1;
  date.day = now->tm_mday;

  std::vector<int64_t> cases = {
      1, 10, 20, 60, 100, 200, 300, 400, 10000, 100000, 1000000000, 200000000000000000};
  for (auto &days: cases) {
    auto new_date = get_date(date, days);
    std::cout << days << " days later from " << date.to_str() << " is " << new_date.to_str() << std::endl;
  }
}

/* stdout
1 days later from 2019/6/19 is 2019/6/20
10 days later from 2019/6/19 is 2019/6/29
20 days later from 2019/6/19 is 2019/7/9
60 days later from 2019/6/19 is 2019/8/18
100 days later from 2019/6/19 is 2019/9/27
200 days later from 2019/6/19 is 2020/1/5
300 days later from 2019/6/19 is 2020/4/14
400 days later from 2019/6/19 is 2020/7/23
10000 days later from 2019/6/19 is 2046/11/4
100000 days later from 2019/6/19 is 2293/4/3
1000000000 days later from 2019/6/19 is 2739926/6/22
200000000000000000 days later from 2019/6/19 is 547581401399720/12/28
 */
