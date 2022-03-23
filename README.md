# C++ Search Engine

## Why?

- Learn C++ (this was my first C++ project)
- Learn how search engines work

## Setup

### Prerequisites

- [GNU GCC](https://gcc.gnu.org/)
- [GNU Make](https://gnu.org/software/make)

### Building

```bash
git clone https://github.com/bensengupta/search
cd search
make
# Run the executable: ./build/search <title file> <query>
./build/search titles_100k.txt France
```

`titles_100k.txt` is the first 100K wikipedia page titles extracted from [enwiki-latest-all-titles.gz](https://dumps.wikimedia.org/enwiki/latest/),
with underscores replaced by spaces.

## TODO

- [ ] Indexing documents should also remove previous documents with same id from index
  - Removing documents by searching through entire index for id
  - or pop old document with same id from storage, find what words it contains and only search & remove in those indices

## References

- Heavily inspired by Victor Lavrenko's [Inverted Indexing lecture series](https://www.youtube.com/watch?v=QA_vuzx9mt4&list=PLBv09BD7ez_448q9kRfZRxYb3cbeEanRb)
- [Search Engine Indexing, Wikipedia](https://en.wikipedia.org/wiki/Search_engine_indexing)
