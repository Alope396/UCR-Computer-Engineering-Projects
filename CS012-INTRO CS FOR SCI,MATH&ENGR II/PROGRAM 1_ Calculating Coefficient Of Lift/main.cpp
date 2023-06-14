#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

void readData(const string &, vector<double> &, vector<double> &);
double interpolation(double, const vector<double> &, const vector<double> &);
bool isOrdered(const vector<double> &);
void reorder(vector<double> &, vector<double> &);
unsigned int swap(vector<double>);

int main(int argc, char* argv[])
{
    string fileName;
    string answer = "Yes";
    double angle;
    fileName = argv[1];
    vector<double> flightPath;
    vector<double> flightCOE;
    readData(fileName, flightPath, flightCOE);
    if(!isOrdered(flightPath))
    {
        reorder(flightPath, flightCOE);
    }
    while(answer != "No")
    {
    cout<< "Please enter an angle: ";
    cin>> angle;
    cout<< endl;
    while(angle < flightPath.at(0) || angle > flightPath.at(flightPath.size()-1))
    {
        cout<< "Please enter a valid angle: ";
        cin>> angle;
        cout<< endl;
    }
    cout<< interpolation(angle, flightPath, flightCOE) << endl;
    cout<< "Continue?" << endl;
    cin>> answer;
    }
    return 0;
}
double interpolation( double angle, const vector<double>& flightPath, const vector<double>& flightCOE)
{
    double resultantPath;
    double fa;
    double a;
    double fc;
    double c;
    for(unsigned i = 0; i < flightPath.size(); i++)
    {
        if(flightPath.at(i) < angle)
        {
            a = flightPath.at(i);
            fa = flightCOE.at(i);
        }
        else if(flightPath.at(i) > angle)
        {
            c = flightPath.at(i);
            fc = flightCOE.at(i);
            break;
        }
        if(angle == flightPath.at(i))
        {
            return flightCOE.at(i);
        }
    }
    resultantPath = fa + ((angle-a)/(c-a)) * (fc-fa);
    return resultantPath;
}
void readData(const string & fileName, vector<double> & flightPath, vector<double> & flightCOE)
{
    ifstream inFS;
    vector<double> flightData;
    double data;
    inFS.open(fileName);
    if(!inFS.is_open())
    {
        cout<< "Error opening " << fileName << endl;
        exit(1);
    }
    while(inFS >> data)
    {
        flightData.push_back(data);
    }
    for(unsigned i = 0; i < flightData.size(); i = i + 2)
    {
        flightPath.push_back(flightData.at(i));
    }
    for(unsigned j = 1; j < flightData.size(); j = j + 2)
    {
        flightCOE.push_back(flightData.at(j));
    }
}
bool isOrdered(const vector<double> & dataStream)
{
    double min;
    for(unsigned i = 0; i < dataStream.size(); i++)
    {
        min = dataStream.at(i);
        for(unsigned j = i+1; j < dataStream.size(); j++)
        {
            if(min > dataStream.at(j))
            {
              return false;
            }
        }
    }
    return true;
}
void swap(vector<double>& flightPath, vector<double>& flightCOE, unsigned int j)
{
    double min1 = flightPath.at(j);
    double matching = flightCOE.at(j);
    double temp1 = min1;
    double temp2 = matching;
    for(unsigned i = j+1; i < flightPath.size(); i++)
    {
        if(min1 > flightPath.at(i))
        {
            min1 = flightPath.at(i);
            matching = flightCOE.at(i);
            flightPath.at(j) = min1;
            flightPath.at(i) = temp1;
            flightCOE.at(j) = matching;
            flightCOE.at(i) = temp2;
        }
    }
}
void reorder(vector <double> & flightPath, vector <double> & flightCOE)
{
    for(unsigned i = 0; i < flightPath.size(); i++)
    {
        swap(flightPath, flightCOE, i);
    }
}