#include <document.h>
#include <utility>

using namespace std;

Document::Document(int id, string text) {
  this->id = id;
  this->text = std::move(text);
}

vector<string> Document::getTerms(const string &delims, const string &charsToSkip) {
  vector<string> terms{};

  string currentWord;

  for (char c : text) {
    bool shouldSkip = false;

    for (char cStrip : charsToSkip) {
      // Skip chars
      if (c == cStrip) {
        shouldSkip = true;
        break;
      }
    }

    if (shouldSkip)
      continue;

    for (char delim : delims) {
      if (c == delim) {
        // Push word and reset current word
        terms.push_back(currentWord);
        currentWord = "";
        shouldSkip = true;
        break;
      }
    }

    if (shouldSkip)
      continue;

    currentWord += c;
  }

  // Push last word
  if (!currentWord.empty()) {
    terms.push_back(currentWord);
  }

  return terms;
}
