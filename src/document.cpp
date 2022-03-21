#include "../include/document.h"

using namespace std;

Document::Document(int id, string text)
{
	this->id = id;
	this->text = text;
}

vector<string> Document::getTerms()
{
	string searchString = text;
	vector<string> terms{};

	string spaceDelimiter = " ";

	size_t pos = 0;
	while ((pos = searchString.find(spaceDelimiter)) != string::npos)
	{
		terms.push_back(searchString.substr(0, pos));
		searchString.erase(0, pos + spaceDelimiter.length());
	}
	terms.push_back(searchString.substr(0, pos));

	return terms;
}