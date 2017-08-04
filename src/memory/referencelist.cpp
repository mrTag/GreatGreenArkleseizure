// Implementation of grwoing and shrinking list of pointers to objects of type T.
// New references can be added and removed at the end of the list.
// Additionally, references can be removed at a given index.
// In this case the list takes the last element and moves it into the newly created gap.
// The referencelist allocator reserves a piece of memory (reflist space) for all lists and divides it into uniform chunks.
// If a new list is created, the allocator reserves a new chunk for it.
// If a list grows past it's chunk an adjacent chunk is added to the lists reservation.
// If there is no free adjacent chunk, two (or more) chunks somwhere else inside the reflist space are allocated and the list is being memcopied into them.