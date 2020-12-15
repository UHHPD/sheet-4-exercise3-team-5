#include "Data.hh"

#include <iostream>
#include <fstream>
#include <cassert>
#include <stdexcept>

using namespace std;

Data::Data(const std::string& filename) {
  ifstream file(filename);

  // check if file opened correctly
  if (!file.is_open()) {
    throw std::runtime_error("Error could not open file with name: " +
                             filename);
  }

  int size = -1;
  file >> size;

  // read in data from file: m_siz+1 bin edges
  for (int i = 0; i < size + 1; ++i) {
    double edge;
    file >> edge;
    m_bins.push_back(edge);
  }
  // read in data from file: m_siz bin contents
  for (int i = 0; i < size; ++i) {
    double entries;
    file >> entries;
    m_data.push_back(entries);
  }
  // Exercise 1b)
  // read in data from file: m_siz bin uncertainties
  for (int i = 0; i < size; ++i) {
    double uncertainty;
    file >> uncertainty;
    m_sigma.push_back(uncertainty);
  }

  // done! close the file
  file.close();

  assertSizes();
};

void Data::assertSizes() { assert(m_data.size() + 1 == m_bins.size());
                          // Exercise 1b)
                           assert(m_data.size() == m_sigma.size()); }

// Preparing Exercise 1d)
int Data::checkCompatibility(const Data& in, int n) {
  // TODO
};

// Preparing Exercise 1e)
// merges a new Data object to an exiting one:
// sum12 = data1.average(data2);
Data Data::average(Data in) {
  // TODO
};
