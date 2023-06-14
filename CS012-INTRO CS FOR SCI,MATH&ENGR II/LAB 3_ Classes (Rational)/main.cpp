#include <iostream>

using namespace std;

// Rational Class declaration
class Rational {
   private:
      int numerator;
      int denominator; 
   public:
      Rational();
      explicit Rational(int); 
      Rational(int, int); 
      const Rational add(const Rational &) const; 
      const Rational subtract(const Rational &) const; 
      const Rational multiply(const Rational &) const; 
      const Rational divide(const Rational &) const;
      void simplify();
      void display() const;
      int getNumerator() const;
      int getDenominator() const;
   private:
      int gcd(int, int) const;
};

// Implement Rational class member functions here
Rational::Rational()
{
   this-> numerator = 0;
   this-> denominator = 1;
}
Rational::Rational(int x)
{
   this-> numerator = x;
   this-> denominator = 1;
}
Rational::Rational(int x, int y)
{
   this-> numerator = x;
   this-> denominator = y;
}
int Rational::getNumerator() const
{
   return numerator;
}
int Rational::getDenominator() const
{
   return denominator;
}
const Rational Rational::add(const Rational & B) const
{
   int finalNumerator;
   int finalDenominator;
   finalNumerator = (numerator * B.getDenominator()) + (denominator * B.getNumerator());
   finalDenominator = denominator * B.getDenominator();
   Rational FinalSolution(finalNumerator, finalDenominator);
   return FinalSolution;
   
}
const Rational Rational::subtract(const Rational & B) const
{
   int finalNumerator;
   int finalDenominator;
   finalNumerator = (numerator * B.getDenominator()) - (denominator * B.getNumerator());
   finalDenominator = denominator * B.getDenominator();
   Rational FinalSolution(finalNumerator, finalDenominator);
   return FinalSolution;
}
const Rational Rational::multiply(const Rational & B) const
{
   int finalNumerator;
   int finalDenomenator;
   finalNumerator = this -> numerator * B.getNumerator();
   finalDenomenator = this -> denominator * B.getDenominator();
   Rational FinalSolution(finalNumerator, finalDenomenator);
   return FinalSolution;
}
const Rational Rational::divide(const Rational & B) const
{
   int finalNumerator;
   int finalDenominator;
   finalNumerator = this -> numerator * B.getDenominator();
   finalDenominator = this -> denominator * B.getNumerator();
   Rational FinalSolution(finalNumerator, finalDenominator);
   return FinalSolution;
}
void Rational::simplify()
{
   int GCD = gcd(numerator, denominator);
   numerator = numerator / GCD;
   denominator = denominator / GCD;
}
int Rational::gcd(int x, int y) const
{
   while(x != y)
      if(x > y)
      {
         x = x - y;
      } 
      else
      {
         y = y - x;
      }

   return x;
}
void Rational::display() const
{
   cout<< numerator << " / " << denominator;

}

// Do not change any of the code below this line!!

Rational getRational();
void displayResult(const string &, const Rational &, const Rational&, const Rational&);

int main() {
   Rational A, B, result;
   char choice;
   
   cout << "Enter Rational A:" << endl;
   A = getRational();
   cout << endl;
   
   cout << "Enter Rational B:" << endl;
   B = getRational();
   cout << endl;
   
   cout << "Enter Operation:" << endl
      << "a - Addition (A + B)" << endl
      << "s - Subtraction (A - B)" << endl
      << "m - Multiplication (A * B)" << endl
      << "d - Division (A / B)" << endl
      << "y - Simplify A" << endl;
   cin >> choice;
   cout << endl;
   
   if (choice == 'a') {
      result = A.add(B);
      displayResult("+", A, B, result);
   } else if (choice == 's') {
      result = A.subtract(B);
      displayResult("-", A, B, result);
   } else if (choice == 'm') {
      result = A.multiply(B);
      displayResult("*", A, B, result);
   } else if (choice == 'd') {
      result = A.divide(B);
      displayResult("/", A, B, result);
   } else if (choice == 'y') {
      A.simplify();
      A.display();
   } else {
      cout << "Unknown Operation";
   }
   cout << endl;
   
   return 0;
}


Rational getRational() {
   int choice;
   int numer, denom;
   
   cout << "Which Rational constructor? (Enter 2, 1, or 0)" << endl
      << "2 - 2 parameters (numerator & denominator)" << endl
      << "1 - 1 parameter (numerator)" << endl
      << "0 - 0 parameters (default)" << endl;
   cin >> choice;
   cout << endl;
   
   if (choice == 2) {
      cout << "numerator? ";
      cin >> numer;
      cout << endl;
      cout << "denominator? ";
      cin >> denom;
      cout << endl;
      return Rational(numer, denom);
   } else if (choice == 1) {
      cout << "numerator? ";
      cin >> numer;
      cout << endl;
      return Rational(numer);
   } else {
      return Rational();
   }
}

void displayResult(const string &op, const Rational &lhs, const Rational&rhs, const Rational &result) {
   cout << "(";
   lhs.display();
   cout << ") " << op << " (";
   rhs.display();
   cout << ") = (";
   result.display();
   cout << ")";
}

