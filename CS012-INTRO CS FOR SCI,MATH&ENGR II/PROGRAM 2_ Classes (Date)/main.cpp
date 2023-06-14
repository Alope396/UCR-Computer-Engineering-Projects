#include <iostream>
#include <string>
#include <vector>

using namespace std;
class Date {
 private:
   unsigned day;
   unsigned month;
   string monthName;
   unsigned year;

 public:
   // creates the date January 1st, 2000.
   Date();

   /* parameterized constructor: month number, day, year 
       - e.g. (3, 1, 2010) will construct the date March 1st, 2010

       If any of the arguments are invalid (e.g. 15 for month or 32 for day)
       then the constructor will construct instead a valid Date as close
       as possible to the arguments provided - e.g. in above example,
       Date(15, 32, 2010), the Date would be corrected to Dec 31st, 2010.
       In case of such invalid input, the constructor will issue a console error message: 

       Invalid date values: Date corrected to 12/31/2010.
       (with a newline at the end).
   */
   Date(unsigned m, unsigned d, unsigned y);

   /* parameterized constructor: month name, day, year
      - e.g. (December, 15, 2012) will construct the date December 15th, 2012

       If the constructor is unable to recognize the string argument as a valid month name,
       then it will issue a console error message: 

       Invalid month name: the Date was set to 1/1/2000.
       (with a newline at the end).
 
       If the day argument is invalid for the given month (but the month name was valid),
       then the constructor will handle this error in the same manner as the other
       parameterized constructor. 

       This constructor will recognize both "december" and "December"
       as month name.
   */
   Date(const string &mn, unsigned d, unsigned y);

   /* Outputs to the console (cout) a Date exactly in the format "3/15/2012". 
      Does not output a newline at the end.
   */
   void printNumeric() const;


   /* Outputs to the console (cout) a Date exactly in the format "March 15, 2012".
      The first letter of the month name is upper case, and the month name is
      printed in full - January, not Jan, jan, or january. 
      Does not output a newline at the end.
   */
   void printAlpha() const;
   // string fixName(const string& monthName);

 private:

   /* Returns true if the year passed in is a leap year, otherwise returns false.
   */
   bool isLeap(unsigned y) const;


   /* Returns number of days allowed in a given month
      -  e.g. daysPerMonth(9, 2000) returns 30.
      Calculates February's days for leap and non-leap years,
      thus, the reason year is also a parameter.
   */
   unsigned daysPerMonth(unsigned m, unsigned y) const;

   /* Returns the name of a given month
      - e.g. name(12) returns the string "December"
   */
   string name(unsigned m) const;

   /* Returns the number of a given named month
      - e.g. number("March") returns 3
   */
   unsigned number(const string &mn) const;
};
Date::Date()
{
   day = 1;
   month = 1;
   monthName = "January";
   year = 2000;
}
Date::Date(unsigned month, unsigned day, unsigned year)
{
   bool isValid = true;
   this-> month = month;
   this-> day = day;
   this-> year = year;
   if(month > 12)
   {
      this-> month = 12;
      this-> monthName = name(this-> month);
      isValid = false;
   }
   else if(month < 1)
   {
      this-> month = 1;
      this-> monthName = name(this-> month);
      isValid = false;
   }
   else
   {
      this-> monthName = name(this-> month);
   }
   
   if(day > daysPerMonth(this-> month, this-> year))
   {
      this-> day = daysPerMonth(this-> month, this-> year);
      isValid = false;
   }
   else if(day < 1)
   {
      this-> day = 1;
      isValid = false;
   }
   if(!isValid)
   {
      cout<< "Invalid date values: Date corrected to " << this-> month << "/" << this-> day << "/" << this-> year << "." << endl;
   }
}
Date::Date(const string& monthName, unsigned day,unsigned year)
{
   vector<string> months = {"January", "january", "February", "february", "March", "march", "April", "april", "May", "may", "June", "june", "July", "july", "August", "august", "September", "september",  "October", "october", "November", "november", "December", "december"};
   bool isValid = false;
   bool isValidDay = true;
   this-> monthName =  monthName;
   this-> day = day;
   this-> year = year;
   for(unsigned i = 0; i < months.size(); i++)
   {
      if(this-> monthName == months.at(i))
      {
         isValid = true;
         if(i%2 != 0)
         {
            this-> monthName = months.at(i-1);

         }
         else
         {
            this-> monthName = months.at(i);
         }
         this-> month = number(this-> monthName);
         break;
      }
   }
   if(this-> day > daysPerMonth(this-> month, this-> year))
   {
      this-> day = daysPerMonth(this-> month, this-> year);
      isValidDay = false;
   }
   else if(this-> day < 1)
   {
      this-> day = 1;
      isValidDay = false;
   }
   if(!isValid)
   {
      this-> month = 1;
      this-> monthName = "January";
      this-> year = 2000;
      this-> day = 1;
      cout<< "Invalid month name: the Date was set to " << "1" << "/" << "1" << "/" << "2000." << endl;
   }
   else if(!isValidDay)
   {
      cout<< "Invalid date values: Date corrected to " << this-> month << "/" << this-> day << "/" << this-> year << "." << endl;
   }
}
unsigned Date::daysPerMonth(unsigned month, unsigned year) const
{
   unsigned maxDays;
   if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
   {
      maxDays = 31;
   }
   else if(month == 2 && isLeap(year))
   {
      maxDays = 29;
   }
   else if(month == 2 && !isLeap(year))
   {
      maxDays = 28;
   }
   else
   {
      maxDays = 30;
   }
   return maxDays;
}
bool Date::isLeap(unsigned year) const
{
   bool leap = false;
   if((year % 4 == 0))
   {
      if((year % 100 == 0))
      {
         if((year % 400 == 0))
         {
            leap = true;
         }
      }
      else
      {
         leap = true;
      }
   }
   else
   {
      leap = false;
   }
   return leap;
}
string Date::name(unsigned month) const
{
   if(month == 1)
   {
      return "January";
   }
   else if(month == 2)
   {
      return "February";
   }
   else if(month == 3)
   {
      return "March";
   }
   else if(month == 4)
   {
      return "April";
   }
   else if(month == 5)
   {
      return "May";
   }
   else if(month == 6)
   {
      return "June";
   }
   else if(month == 7)
   {
      return "July";
   }
   else if(month == 8)
   {
      return "August";
   }
   else if(month == 9)
   {
      return "September";
   }
   else if(month == 10)
   {
      return "October";
   }
   else if(month == 11)
   {
      return "November";
   }
   else if(month == 12)
   {
      return "December";
   }
   return "error";
}
unsigned Date::number(const string& monthName) const
{  
   if(monthName == "January")
   {
      return 1;
   }
   else if(monthName == "February")
   {
      return 2;
   }
   else if(monthName == "March")
   {
      return 3;
   }
   else if(monthName == "April")
   {
      return 4;
   }
   else if(monthName == "May")
   {
      return 5;
   }
   else if(monthName == "June")
   {
      return 6;
   }
   else if(monthName == "July")
   {
      return 7;
   }
   else if(monthName == "August")
   {
      return 8;
   }
   else if(monthName == "September")
   {
      return 9;
   }
   else if(monthName == "October")
   {
      return 10;
   }
   else if(monthName == "November")
   {
      return 11;
   }
   else if(monthName == "December")
   {
      return 12;
   }
   return 0;
}
void Date::printNumeric() const
{
   cout<< month << "/" << day << "/" << year;
}
void Date::printAlpha() const
{
   cout<< monthName << " " << day << ", " << year;
}

// Don't change the code below this line.
// You may comment them out if you want to build your own test harness
// while in develope mode, but you will need these to pass tets in submit mode.

Date getDate();

int main() {
   
   Date testDate;
   testDate = getDate();
   cout << endl;
   cout << "Numeric: ";
   testDate.printNumeric();
   cout << endl;
   cout << "Alpha:   ";
   testDate.printAlpha();
   cout << endl;
   
   return 0;
}

Date getDate() {
   int choice;
   unsigned monthNumber, day, year;
   string monthName;

   cout << "Which Date constructor? (Enter 1, 2, or 3)" << endl
      << "1 - Month Number" << endl
      << "2 - Month Name" << endl
      << "3 - default" << endl;
   cin >> choice;
   cout << endl;

   if (choice == 1) {
      cout << "month number? ";
      cin >> monthNumber;
      cout << endl;
      cout << "day? ";
      cin >> day;
      cout << endl;
      cout << "year? ";
      cin >> year;
      cout << endl;
      return Date(monthNumber, day, year);
   } else if (choice == 2) {
      cout << "month name? ";
      cin >> monthName;
      cout << endl;
      cout << "day? ";
      cin >> day;
      cout << endl;
      cout << "year? ";
      cin >> year;
      cout << endl;
      return Date(monthName, day, year);
   } else {
      return Date();
   }
}
