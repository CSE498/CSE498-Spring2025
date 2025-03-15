# Feedback on initial specifications

## `OutputLog` class

Good identification of challenges.  Don't worry about thread safety in your initial implementation (for any of the classes), but you are absolutely correct that if you decide to build a more advanced version of this class, that will be one of the challenges to contend with.

## `AuditedArray` class

One simple step on this implementation is that if you are outside of debug mode, you should make AuditedArray identical to std::array.  You do this with a simple using statement:

```
#ifdef NDEBUG
  template <typename T, size_t N>
  using AuditedArray = std::array<T,N>;

#else

  // ... Implementation of regular AuditedArray ...

#endif
```

When you build AuditedArray, feel free to have an `std::array` as a member variable.  Then you add member function to `AuditedArray` that just pass on through to `std::array` after doing any checks that they need to do.

One thing I should note - the regular `std::array` is what's known as an "aggregate class" which is a whole special type of structure in C++.  We'll talk about them, but this isn't something that you need to worry about for you implementation; I just don't want it to confuse you if you look up online how that class was created.  Also, the folks making `AuditedVector` can inherit from `std::vector`, but `std::array` won't allow that, unfortunately.


## `DataFileManager` class

I think the key specs here look solid.  As with many of these, I should have encouraged students to provide short examples of use cases to make sure I'm understanding the plans correctly, but the key ideas look good.  For example, does the constructor take a filename?  Does `addFunction` take a name for that column of data?  I'd probably do that, but it's not critical.

Here is how I might see this used:

```
int x = 5;
int y = 10;

DataFileManager dfm("out.csv");
dfm.addFunction( "X Value", [&x](){return x;} );
dfm.addFunction( "Y Value", [&y](){return y;} );

dfm.update();
x++;
dfm.update();
y++;
dfm.update();

```
This might output to the file out.csv:
```
"X Value","Y Value"
5,10
6,10
6,11
```

I'm not set on this being how it works, just putting forth my assumption from the combination of what I was originally thinking and read in your writeup.

## `Scheduler` class

This looks like a solid plan.  Good job with the error conditions and expected challenges in particular.

Regarding the functions, I think you may need to refine these details once you start working with them, but this seems like a fine launch point.

## `Serializer` class

The biggest warning here is that serializers have the potential to be HUGE.  For the moment, I'd say get it working with builtin types (`int`, `float`, `double`, `char`, `bool`, etc) and maybe a couple of standard library templates (like `vector`).  We can always expand it out later.

What would be nice is to have some simple way to build out to get the serialize to work with more classes, like a simple function that you just need to overload.
