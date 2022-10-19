#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <map>
#include <string>
#include <tuple>
#include <vector>

class Document {
public:
  int id;
  std::string text;
  Document(int id, std::string text);
  std::vector<std::string> getTerms(const std::string &delims,
                                    const std::string &charsToSkip);
};

#endif // DOCUMENT_H
