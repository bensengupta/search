#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <document.h>

class DataSource {
public:
  virtual std::vector<Document> getDocuments();
};

class FileDataSource : public DataSource {
public:
  explicit FileDataSource(std::string filename);
  std::vector<Document> getDocuments() override;

private:
  std::string filename;
};

#endif // DATASOURCE_H
