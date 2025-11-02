# LazyCach

LazyCach is a verry small header only collection of lazily evaluated caching containers.
Currently there are two different containers.

1. CachedEval
2. CachedFunc

## CachedEval

CachedEval wrapps a function call, which is is lazily performed and cached.
That means the function and the arguments are stored in CachedEval but the function call is only perfomed as soon as the result is needed.
This itself does not bring any benefits. However CachedEval does also store the result such that a seccond call will not call the function but retrieve the value form cache.

## CachedFunc

CachedFunc wrapps a function. This container does not store the functions argumenst, meaning you can call it with different arguments later on.
When you call CachedFunc with certain arguments for the first time, it will perform the function call, cache the value and returns it.
For each subsequent call with the same arguments, the cached value is returned.
In contrast to CachedEval, this container uses a std::map for the cache lookup.
Retreiving a cached value as well as inserting a new value has a complexity of O(n), where n is the number of values that are cached so far.
Consequently, the more calls with different arguments, are perfomed the slower CachedFunc gets.
