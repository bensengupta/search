#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <document.h>

class DataSource {
public:
  virtual std::vector<Document> getDocuments();
};

class FileDataSource : public DataSource {
public:
  FileDataSource(std::string filename);
  std::vector<Document> getDocuments();

private:
  std::string filename;
};

#endif // DATASOURCE_H
