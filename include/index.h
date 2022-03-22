#ifndef INDEX_H
#define INDEX_H

#include <map>
#include <unordered_map>
#include <string>
#include <vector>
#include <tuple>
#include "document.h"

class Index
{
public:
	void indexDocuments(std::vector<Document> documents);
	std::vector<Document *> search(std::string query);

private:
	std::unordered_map<int, Document> documentIdMap;
	/// unordered_map<term, tuple<doc_id, position_in_doc>>
	std::unordered_map<std::string, std::vector<std::tuple<int, int>>> inverseIndex;
	void mergeInverseIndex(std::map<std::string, std::vector<std::tuple<int, int>>> newInverseIndex);
	std::vector<std::string> getQueryTerms(std::string query);
};

#endif // INDEX_H
