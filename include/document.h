#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <map>
#include <string>
#include <vector>
#include <tuple>

class Document
{
public:
	int id;
	std::string text;
	Document(int id, std::string text);
	std::vector<std::string> getTerms();
};

#endif // DOCUMENT_H
