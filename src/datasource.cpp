#include <datasource.h>
#include <fstream>
#include <iostream>
#include <utility>

using namespace std;

vector<Document> DataSource::getDocuments() { return {}; }

FileDataSource::FileDataSource(string filename) { this->filename = std::move(filename); }

vector<Document> FileDataSource::getDocuments() {
  ifstream in(filename);

  if (in.fail()) {
    cerr << "Error: Could not find file '" << filename << "'" << endl;
    exit(1);
  }

  vector<Document> docs{};

  int i = 0;
  string line;
  while (getline(in, line)) {
    docs.emplace_back(i++, line);
  }

  in.close();

  return docs;
}
