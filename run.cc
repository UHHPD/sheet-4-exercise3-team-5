#include <iostream>
#include <vector>
#include <functional>
#include <string>

#include "Data.hh"
#include <cmath>

// generic function comparing two values of some type T used later
// for int and double
template <class T>
bool testEqual(const std::string& name, T expected, T real) {
  if (expected != real) {
    std::cout << "(" << name << ": <" << expected << ">"
              << ", " << real << ") ";
    return false;
  }
  return true;
}

bool testReadingSize() {
  std::cout << "testReadingSize...";
  Data datA("testA");
  return testEqual<int>("size", 1, datA.size());
}

bool testReadingMeasurement() {
  std::cout << "testReadingMeasurement...";
  Data datA("testA");
  return testEqual("measurement", 10., datA.measurement(0));
}

bool testReadingBinEdges() {
  std::cout << "testReadingBinEdges...";
  Data datA("testA");
  return testEqual("bin low", 0., datA.binLow(0)) &&
         testEqual("bin high", 1., datA.binHigh(0));
}

bool testReadingErrors() {
  std::cout << "testReadingErrors...";
  Data datA("testA");
  return testEqual("error", 2., datA.error(0));
}

bool testCopyConstructor() {
  std::cout << "testCopyConstructor...";
  Data a("testA");
  Data b(a);
  Data c = a;  // equivalent to Data c(a)
  return testEqual("measurement", 10., b.measurement(0)) &&
         testEqual("measurement", 10., c.measurement(0));
}

void runTests() {
  std::cout << "running tests...\n";
  std::vector<std::function<bool()> > tests(
      {testReadingSize, testReadingMeasurement, testReadingBinEdges,
       testReadingErrors, testCopyConstructor});
  for (auto test : tests)
    std::cout << (test() ? " ok" : " FAILED!") << std::endl;
}


int main() {
  using namespace std;
  // Exercise 1c)
  std::vector<Data> allSets;
  std::string filenames[] = {"exp_A", "exp_B", "exp_C", "exp_D"};

  cout << "******************************************************" << endl;
  cout << endl << "Exercise 1a)" << endl;
  runTests();
  cout << "******************************************************" << endl;
  cout << endl << "Exercise 1b)" << endl;
  // create an object which holds data of experiment A
  Data datA("exp_A");
  // here is the data from experiment A
  cout << "bin 27: from " << datA.binLow(27) << " to " << datA.binHigh(27)
       << endl;
  cout << "measurement of experiment A in bin 27: " << datA.measurement(27)
       << endl;
  // Exercise 1b)
  cout << "uncertainty of experiment A in bin 27: " << datA.error(27)
       << endl << endl;

  // Exercise 1c)
  cout << "******************************************************" << endl;
  cout << endl << "Exercise 1c)" << endl;
  for (int i = 0; i < 4; i++) {
    Data set(filenames[i]);
    allSets.push_back(set);
    cout << "cros-section of experiment " << filenames[i]
         << " in bin 27: " << set.measurement(27)
         << " +- " << set.error(27) << endl;
  }
  
  // Exercise 1d)
  cout << "******************************************************" << endl;
  cout << endl << "Exercise 1d)" << endl;
  int d;
  for (int i = 0; i <=2; i++) {
    for (int j = i + 1; j <= 3; j++) {
      cout << "Compatibility check of " << filenames[i] 
           << " with " << filenames[j] << ", measurements differing"
           << endl;
      for (int n = 1; n <= 3; n++) {
        d = allSets[i].checkCompatibility(allSets[j], n);
        cout << "    more than " << n << " * sigma = " << d << " points" << endl;
      }
      cout << endl;
    }
  }

  // Exercise 1e)
  cout << "******************************************************" << endl;
  cout << endl << "Exercise 1e)" << endl;
  Data sum12 = allSets[0].average(allSets[1]);
  cout << "cros-section of experiment A & B"
         << " in bin 27: " << sum12.measurement(27)
         << " +- " << sum12.error(27) << endl;
  return 0;
}
