#ifndef QUERY_H
#define QUERY_H

#include <document.h>
#include <map>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

class QueryNodeResult {
public:
  bool endReached;
  int docId;
  int posStart;
  int posEnd;
  static QueryNodeResult EndNode();
  static QueryNodeResult Node(int docId, int posStart, int posEnd);

private:
  QueryNodeResult(bool endReached, int docId, int posStart, int posEnd);
};

class QueryNode {
public:
  /// Creates the query node on the heap and returns a pointer to it
  static QueryNode *create();
  /// Gets next element from node
  virtual QueryNodeResult next();
  /// Execute query with a given max hits and return a vector of document ids
  static std::vector<QueryNodeResult> executeQuery(QueryNode *node, int max);
  virtual ~QueryNode();
};

class QueryNodeTerm : public QueryNode {
public:
  static QueryNode *create(std::vector<std::tuple<int, int>> *index);
  QueryNodeResult next();

private:
  size_t i;
  QueryNodeTerm(std::vector<std::tuple<int, int>> *index);
  std::vector<std::tuple<int, int>> *index;
};

class QueryNodePhrase : public QueryNode {
public:
  static QueryNode *create(QueryNode *node1, QueryNode *node2);
  QueryNodeResult next();
  ~QueryNodePhrase();

private:
  QueryNode *node1;
  QueryNode *node2;
  QueryNodePhrase(QueryNode *node1, QueryNode *node2);
};

#endif // QUERY_H
