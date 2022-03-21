#include "../include/document.h"
#include "../include/index.h"
#include <iostream>

using namespace std;

// Heavily inspired by Victor Lavrenko's "Inverted Indexing" lecture series
// https://www.youtube.com/watch?v=QA_vuzx9mt4&list=PLBv09BD7ez_448q9kRfZRxYb3cbeEanRb

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		cerr << "Error: Please specify a search query (\"search <query>\")" << endl;
		return 1;
	}

	Index index;

	index.indexDocuments({
			Document(1, "He likes to wink, he likes to drink."),
			Document(2, "He likes to drink, and drink, and drink."),
			Document(3, "The thing he likes to drink is ink."),
	});

	index.indexDocuments({
			Document(4, "The ink he likes to drink is pink."),
			Document(5, "He likes to wink and drink pink ink."),
	});

	string query = argv[1];
	auto hits = index.search(query);
	cout << "Query: " << query << endl;

	for (auto hit : hits)
	{
		cout << "Hit: doc " << hit->id << endl;
	}

	return 0;
}