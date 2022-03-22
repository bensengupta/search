# C++ Search Engine

Small project to learn C++ and how search engines work.

## Setup

### Prerequisites

- Requires [GNU GCC](https://gcc.gnu.org/)

### Building

```
# Build the executable
make
# Run the executable
./build/search <query>
```

TODO:

- [ ] Removing documents by id?
  - [ ] Indexing documents should also remove previous documents with same id from index
- [ ] Scoring function https://youtu.be/DQ4u1t_Unpo?t=404
      Kinda like this: `float Index::score(vector<int> positions)`
      Term 1 found at pos 8, term 2 & 3 not found `score({ 8, -1, -1 })`
