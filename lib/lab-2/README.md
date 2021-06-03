# Lab 2: Vectors using Dynamic Arrays

## `StringVector`

`StringVector` is a dynamic array of strings. While static arrays have a size determined at compile time, dynamic arrays
can have their size determined during runtime and can change in size during runtime. A vector is a dynamic array, and
has theoretically infinite size since the size can always be increased.

### private:

- `data` is the dynamic array of strings

- `dataSize` is the number of actual elements in the array

- `dataCapacity` is the allocated number of elements for the array

### public:

- `StringVector()` creates an empty array with a size and capacity of zero

- `StringVector(StringVector)` creates a hard copy of an array

- `~StringVector()` deletes the array from memory

- `at(unsigned)` gets value at an index

- `size()` gets the size of the array

- `empty()` determines if the array is empty

- `capacity()` gets the maximum size of the array

- `append(std::string)` adds a string to the end of the array

- `reserve(unsigned)` increases the capacity of the array

- `swap(unsigned, unsigned)` exchanges the order of two strings

- `sort()` rearranges the array in alphabetical order

- `operator=(StringVector)` overwrites the array with another array

- `operator[](unsigned)` alias of `at(unsigned)`