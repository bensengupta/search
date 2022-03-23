#ifndef INDEX_H
#define INDEX_H

#include "document.h"
#include "query.h"
#include <map>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

class Index {
public:
  void indexDocuments(std::vector<Document> documents);
  std::vector<Document *> search(std::string query);

private:
  std::unordered_map<int, Document> documentIdMap;
  /// unordered_map<term, tuple<doc_id, position_in_doc>>
  std::unordered_map<std::string, std::vector<std::tuple<int, int>>>
      inverseIndex;
  void mergeInverseIndex(
      std::map<std::string, std::vector<std::tuple<int, int>>> newInverseIndex);
  QueryNode *buildQuery(std::vector<std::string>);
  std::vector<std::string> getQueryTerms(std::string query);
};

#endif // INDEX_H
