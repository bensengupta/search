#include <datasource.h>
#include <document.h>
#include <index.h>
#include <timer.h>
#include <iostream>

using namespace std;

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

  string delims = " _";
  string charsToSkip = ",.:;'\"()!?";

  cout << "Building index..." << endl;
  timer.start();
  index.indexDocuments(docs, delims, charsToSkip);
  timer.end();

  cout << "Querying..." << endl;
  string query = argv[2];

  timer.start();
  auto hits = index.search(query, 10);
  timer.end();

  cout << "Query: " << query << endl;

  for (auto hit : hits) {
    cout << "Hit: doc " << hit->id << " '" << hit->text << "'" << endl;
  }

  return 0;
}
