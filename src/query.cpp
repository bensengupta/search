#include "../include/query.h"
#include <iostream>

using namespace std;

/**
 * QueryNodeResult methods
 */

QueryNodeResult::QueryNodeResult(bool endReached, int docId, int posStart,
                                 int posEnd) {
  this->endReached = endReached;
  this->docId = docId;
  this->posStart = posStart;
  this->posEnd = posEnd;
}

QueryNodeResult QueryNodeResult::EndNode() {
  return QueryNodeResult(true, -1, -1, -1);
}

QueryNodeResult QueryNodeResult::Node(int docId, int posStart, int posEnd) {
  return QueryNodeResult(false, docId, posStart, posEnd);
}

/**
 * QueryNode methods
 */

QueryNode *QueryNode::create() { return new QueryNode(); }

QueryNodeResult QueryNode::next() { return QueryNodeResult::EndNode(); }

vector<int> QueryNode::executeQuery(QueryNode *node, int max) {
  vector<int> docIds{};

  QueryNodeResult res = node->next();

  int i = 0;
  while (!res.endReached && i <= max) {
    docIds.push_back(res.docId);
    res = node->next();
    i++;
  }

  return docIds;
}

QueryNode::~QueryNode() {}

void QueryNode::freeQuery(QueryNode *node) {
  if (node != NULL)
    delete node;
}

/**
 * QueryNodeTerm methods
 */

QueryNodeTerm::QueryNodeTerm(vector<tuple<int, int>> *index) {
  i = 0;
  this->index = index;
}

QueryNode *QueryNodeTerm::create(vector<tuple<int, int>> *index) {
  return new QueryNodeTerm(index);
}

QueryNodeResult QueryNodeTerm::next() {
  if (index == NULL) {
    return QueryNodeResult::EndNode();
  }
  if (i >= index->size()) {
    return QueryNodeResult::EndNode();
  }
  auto const [docId, pos] = (*index)[i++];
  return QueryNodeResult::Node(docId, pos, pos);
}

/**
 * QueryNodePhrase methods
 */

QueryNodePhrase::QueryNodePhrase(QueryNode *node1, QueryNode *node2) {
  this->node1 = node1;
  this->node2 = node2;
}

QueryNode *QueryNodePhrase::create(QueryNode *node1, QueryNode *node2) {
  return new QueryNodePhrase(node1, node2);
}

QueryNodeResult QueryNodePhrase::next() {
  QueryNodeResult res1 = node1->next();
  QueryNodeResult res2 = node2->next();

  while (!res1.endReached && !res2.endReached) {
    // Phrase found
    if (res1.docId == res2.docId && res1.posEnd + 1 == res2.posStart) {
      return QueryNodeResult::Node(res1.docId, res1.posStart, res2.posEnd);
    }

    // Get next value
    if (res1.docId == res2.docId) {
      if (res1.posStart >= res2.posStart) {
        res2 = node2->next();
      } else {
        res1 = node1->next();
      }
    } else if (res1.docId > res2.docId) {
      res2 = node2->next();
    } else {
      res1 = node1->next();
    }
  }

  return QueryNodeResult::EndNode();
}

QueryNodePhrase::~QueryNodePhrase() {
  delete node1;
  delete node2;
}
