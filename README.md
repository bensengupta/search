# C++ Search Engine

Small project to learn C++ and how search engines work.

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

### Development

```bash
# Build the executable with debug flags
make debug
./build/search titles_100k.txt France
```

## TODO

- [ ] Removing documents by id?
  - [ ] Indexing documents should also remove previous documents with same id from index
