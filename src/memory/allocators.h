#ifndef allocators_h__
#define allocators_h__

#include <assert.h>

//#pragma warning(push)
//#pragma warning(disable: 4101)

// disallow default memory allocation via new operator
void* operator new (size_t size)
{
    assert(0);
    return 0;
}

void* operator new[] (size_t size)
{
    assert(0);
    return 0;
}

//#pragma warning(pop)

class Allocator
{
    public:
    virtual void *allocate(size_t size, size_t align) = 0;
    virtual void deallocate(void *p) = 0;
    virtual size_t allocated_size(void *p) = 0;
};

#endif // allocators_h__