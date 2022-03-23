#include "../include/index.h"
#include <iostream>
#include <set>
#include <stdexcept>

using namespace std;

// References:
// - Search Engine Indexing, Wikipedia
//   https://en.wikipedia.org/wiki/Search_engine_indexing

void Index::indexDocuments(vector<Document> documents, string delims,
                           string charsToSkip) {
  // Step 1: Build a forward index
  // Step 2: Convert to intermediate inverse index
  // Step 2: Merge with main inverted index

  // Step 1: Forward Index
  // forwardIndex is a map<doc_id, vector<tuple<term, position_in_doc>>>
  map<int, vector<tuple<string, int>>> forwardIndex;

  for (auto &doc : documents) {
    // Store in document map
    documentIdMap.insert(make_pair(doc.id, doc));

    // Add to forward index
    vector<string> terms = doc.getTerms(delims, charsToSkip);

    for (size_t i = 0; i < terms.size(); i++) {
      auto term = terms[i];

      if (forwardIndex.find(doc.id) == forwardIndex.end()) {
        forwardIndex.insert(make_pair(doc.id, vector<tuple<string, int>>()));
      }
      forwardIndex[doc.id].push_back(make_tuple(term, i));
    }
  }

  // Step 2: Intermediate inverse index
  map<string, vector<tuple<int, int>>> newInverseIndex;
  for (const auto &[docId, tokens] : forwardIndex) {
    for (const auto &[term, pos] : tokens) {
      if (newInverseIndex.find(term) == newInverseIndex.end()) {
        newInverseIndex.insert(make_pair(term, vector<tuple<int, int>>()));
      }
      newInverseIndex[term].push_back(make_tuple(docId, pos));
    }
  }

  // Remove previous occurrences in the main index?
  mergeInverseIndex(newInverseIndex);
}

void Index::mergeInverseIndex(
    map<string, vector<tuple<int, int>>> newInverseIndex) {
  for (const auto &[term, posVec] : newInverseIndex) {
    if (inverseIndex.find(term) == inverseIndex.end()) {
      inverseIndex.insert(make_pair(term, vector<tuple<int, int>>()));
    }

    // Merge vectors with linear merge
    size_t cursorNew = 0;
    size_t cursorMain = 0;

    while (cursorMain != inverseIndex[term].size() &&
           cursorNew != posVec.size()) {
      if (get<0>(inverseIndex[term][cursorMain]) > get<0>(posVec[cursorNew])) {
        inverseIndex[term].insert(inverseIndex[term].begin() + cursorMain,
                                  posVec[cursorNew]);
        cursorMain++;
        cursorNew++;
      }
      cursorMain++;
    }

    // Add rest of positions
    for (size_t i = cursorNew; i < posVec.size(); i++) {
      inverseIndex[term].push_back(posVec[i]);
    }
  }
}

vector<string> Index::getQueryTerms(string query) {
  vector<string> terms{};

  string spaceDelimiter = " ";

  size_t pos = 0;
  while ((pos = query.find(spaceDelimiter)) != string::npos) {
    terms.push_back(query.substr(0, pos));
    query.erase(0, pos + spaceDelimiter.length());
  }
  terms.push_back(query.substr(0, pos));

  return terms;
}

QueryNode *Index::buildQuery(vector<string> queryTerms) {
  if (queryTerms.size() == 0) {
    throw runtime_error("Error: unexpected length 0 of query terms.");
  }

  QueryNode *query;
  if (inverseIndex.find(queryTerms[0]) == inverseIndex.end()) {
    query = QueryNode::create();
  } else {
    query = QueryNodeTerm::create(&inverseIndex[queryTerms[0]]);
  }

  // Start at 1 since first term already taken
  for (size_t i = 1; i < queryTerms.size(); i++) {
    string term = queryTerms[i];
    QueryNode *nextNode;
    if (inverseIndex.find(term) == inverseIndex.end()) {
      nextNode = QueryNode::create();
    } else {
      nextNode = QueryNodeTerm::create(&inverseIndex[term]);
    }
    query = QueryNodePhrase::create(query, nextNode);
  }

  return query;
}

vector<Document *> Index::search(string queryString, int maxResults) {
  vector<string> queryTerms = getQueryTerms(queryString);

  QueryNode *query = buildQuery(queryTerms);

  vector<int> docIds = QueryNode::executeQuery(query, maxResults);

  delete query;

  vector<Document *> hits{};

  for (auto id : docIds) {
    hits.push_back(&documentIdMap.find(id)->second);
  }

  return hits;
}
