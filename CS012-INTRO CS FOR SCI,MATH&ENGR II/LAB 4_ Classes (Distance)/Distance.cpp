#include <iostream>

using namespace std;

#include "Distance.h"

Distance::Distance()
{
   feet = 0;
   inches = 0;
}

Distance::Distance(unsigned ft, double in)
{  
   feet = ft;
   inches = in;
   init();
}

Distance::Distance(double in)
{
   feet = 0;
   inches = in;
   init();
}

unsigned Distance::getFeet() const
{
   return feet;
}

double Distance::getInches() const
{
   return inches;
}

double Distance::distanceInInches() const
{
   double convertedInches;
   convertedInches = feet * 12 + inches;
   return convertedInches;
}

double Distance::distanceInFeet() const
{
   double convertedFeet;
   convertedFeet = inches/12 + feet;
   return convertedFeet; 
}

double Distance::distanceInMeters() const
{
   double convertedMeters;
   convertedMeters = distanceInInches() * 0.0254;
   return convertedMeters;
}

Distance Distance::operator+(const Distance &rhs) const
{
   Distance totalDistance;
   totalDistance.feet = feet + rhs.feet;
   totalDistance.inches = inches + rhs.inches;
   totalDistance.init();
   return totalDistance;
}

Distance Distance::operator-(const Distance &rhs) const
{
   Distance totalDistance;
   if(feet > rhs.feet)
   {
      totalDistance.feet = feet - rhs.feet;
   }
   else
   {
      totalDistance.feet = rhs.feet - feet;
   }
   if(inches > rhs.inches)
   {
      totalDistance.inches = inches - rhs.inches;
   }
   else if(inches < rhs.inches)
   {
      totalDistance.inches = rhs.inches - inches;
   }
   totalDistance.init();
   return totalDistance;
}

ostream & operator<<(ostream &out, const Distance &rhs)
{
   out << rhs.feet << "' " << rhs.inches << "\""; 
   return out;
}

void Distance::init()
{
   if(inches < 0)
   {
      inches = inches * -1;
   }
   while(inches >= 12)
   {
      feet += 1;
      inches -= 12;
   }
}