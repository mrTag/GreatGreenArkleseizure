#ifndef allocators_h__
#define allocators_h__

class Allocator
{
    public:
    virtual void *allocate(size_t size, size_t align) = 0;
    virtual void deallocate(void *p) = 0;
    virtual size_t allocated_size(void *p) = 0;
};

#endif // allocators_h__