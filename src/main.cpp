#include "../include/datasource.h"
#include "../include/document.h"
#include "../include/index.h"
#include <iostream>

using namespace std;

// Heavily inspired by Victor Lavrenko's "Inverted Indexing" lecture series
// https://www.youtube.com/watch?v=QA_vuzx9mt4&list=PLBv09BD7ez_448q9kRfZRxYb3cbeEanRb

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cerr << "Error: Please specify a search query (\"search <query>\")" << endl;
    return 1;
  }

  auto datasource = FileDataSource(string(argv[1]));

  Index index;

  index.indexDocuments(datasource.getDocuments());

  string query = argv[2];

  auto hits = index.search(query);

  cout << "Query: " << query << endl;

  for (auto hit : hits) {
    cout << "Hit: doc " << hit->id << " '" << hit->text << "'" << endl;
  }

  return 0;
}
