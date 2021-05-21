#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

//student class
class Inspections
{
private:
  //variables to store unique risk values
  int riskTypeNull = 0;
  int riskTypeAll = 0;
  int riskType1 = 0;
  int riskType2 = 0;
  int riskType3 = 0;

public:
  //inline mutator functions to increase counts by 1
  void increaseTypeNull() { riskTypeNull++; }
  void increaseTypeAll() { riskTypeAll++; }
  void increaseType1() { riskType1++; }
  void increaseType2() { riskType2++; }
  void increaseType3() { riskType3++; }
  //function to open the csv
  bool openFile(string fileName, ifstream &records);
  //function to extract the risk value from a record
  string findRisk(string record);
  //function to count the number of risk values
  void countRisks(ifstream &records);
  //inline function to retrieve all counts
  void getAllCounts()
  {
    cout << "UNIQUE RISK VALUES" << endl;
    cout << "\"All\" - " << riskTypeAll << endl;
    cout << "\"Risk 1 (High)\" - " << riskType1 << endl;
    cout << "\"Risk 2 (Medium)\" - " << riskType2 << endl;
    cout << "\"Risk 3 (Low)\" - " << riskType3 << endl;
    cout << "No value - " << riskTypeNull;
  }
};

//function to open the csv
bool openFile(string fileName, ifstream &records)
{
  //open the file
  records.open(fileName);
  //return true if the file is opened successfully, false otherwise
  if (records.is_open())
    return true;
  return false;
}

string findRisk(string data)
{
  string risk;
  stringstream parse(data);
  //parse the line one value at a time, and search for one of the possible risk values in the csv
  while (getline(parse, risk, ','))
  {
    //return the value if it is found
    if (risk == "All")
      return risk;
    if (risk == "Risk 1 (High)")
      return risk;
    if (risk == "Risk 2 (Medium)")
      return risk;
    if (risk == "Risk 3 (Low)")
      return risk;
  }

  //if it is not one of the possible values, then that line must not have a risk value. return null
  return "null";
}

vector<string> countRisks(ifstream &records)
{
  vector<string> allRisks;
  //string to store the temporary data of the file while parsing
  string data;
  //string to store the value of the risk column
  string risk;
  //ignore the header column
  getline(records, data);
  //continue until the end of the file is reached
  while (!records.eof())
  {
    //collect each row as its own string
    getline(records, data);
    //if it isn't an empty row, search for its risk
    if (!data.empty())
    {
      risk = findRisk(data);
      allRisks.push_back(risk);
    }
  }
  return allRisks;
}

int main()
{
  //create and open input file stream
  ifstream records;
  openFile("Food_Inspections.csv", records);
  //create a class object
  Inspections risks;
  //use the countRisks function to create a vector of all the unique risk values
  vector<string> allRisks = countRisks(records);

  //loop through all the unique values and increase each corresponding count
  for (std::size_t i = 0; i < allRisks.size(); i++)
  {
    if (allRisks.at(i) == "null")
      risks.increaseTypeNull();
    if (allRisks.at(i) == "All")
      risks.increaseTypeAll();
    if (allRisks.at(i) == "Risk 1 (High)")
      risks.increaseType1();
    if (allRisks.at(i) == "Risk 2 (Medium)")
      risks.increaseType2();
    if (allRisks.at(i) == "Risk 3 (Low)")
      risks.increaseType3();
  }

  //print all values and counts
  risks.getAllCounts();
}