# C++ Search Engine

## Why?

- Learn C++ (this was my first C++ project)
- Learn how search engines work

## Setup

### Prerequisites

- [CMake](https://gcc.gnu.org/)
- A C++ compiler (MSVC, GCC, MINGW, etc.)

### Building

```bash
git clone https://github.com/bensengupta/search
cd search
cmake .
# Run the executable: ./search <title file> <query>
./search titles_100k.txt France
```

`titles_100k.txt` is the first 100K Wikipedia page titles extracted from [enwiki-latest-all-titles-in-ns0.gz](https://dumps.wikimedia.org/enwiki/latest/).

## TODO

- [ ] Indexing documents should also remove previous documents with same ID from index
  - Removing documents by searching through entire index for ID
  - or pop old document with same ID from storage, find what words it contains and only search & remove in those indices

## References

- Heavily inspired by Victor Lavrenko's [Inverted Indexing lecture series](https://www.youtube.com/watch?v=QA_vuzx9mt4&list=PLBv09BD7ez_448q9kRfZRxYb3cbeEanRb)
- [Search Engine Indexing, Wikipedia](https://en.wikipedia.org/wiki/Search_engine_indexing)
