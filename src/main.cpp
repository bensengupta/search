#include "../include/datasource.h"
#include "../include/document.h"
#include "../include/index.h"
#include "../include/timer.h"
#include <iostream>

using namespace std;

// Heavily inspired by Victor Lavrenko's "Inverted Indexing" lecture series
// https://www.youtube.com/watch?v=QA_vuzx9mt4&list=PLBv09BD7ez_448q9kRfZRxYb3cbeEanRb

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cerr << "Error: Please specify a search query (\"search <query>\")" << endl;
    return 1;
  }

  Index index;
  Timer timer;

  FileDataSource datasource = FileDataSource(string(argv[1]));

  cout << "Reading file..." << endl;
  timer.start();
  vector<Document> docs = datasource.getDocuments();
  timer.end();

  cout << "Building index..." << endl;
  timer.start();
  index.indexDocuments(docs);
  timer.end();

  cout << "Querying..." << endl;
  string query = argv[2];
  timer.start();
  auto hits = index.search(query);
  timer.end();

  cout << "Query: " << query << endl;

  for (auto hit : hits) {
    cout << "Hit: doc " << hit->id << " '" << hit->text << "'" << endl;
  }

  return 0;
}
