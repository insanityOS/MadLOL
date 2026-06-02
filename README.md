# Introduction

Awesome eXtreme Lightweight Outlining Library (AxLOL) is a library intended to support drawing frame buffers using
primitive elements. 

## Goals and Constraints
The primary constraints for this library are memory safety and minimized memory footprint. In these interests, the 
library does not use dynamic memory allocation internally.

### Memory Safety Features
* Given the error-prone nature of null-terminated strings, only fixed-width strings are permitted for printing.
    * Notably, nulls in strings are **IGNORED**. Users are expected to figure out the length of their strings before
      passing them.
* Frame buffers will drop any attempted pixel writes that are out of bounds with a warning provided in the status.
    * Attempting to write outside of the boundaries outright fails the operation immediately with an error status.

### Tooling
This library is developed and tested using Make as the build system with GCC as the compiler. However, as portability
is a secondary consideration, compiler-specific behavior is generally avoided where possible. Users are more than 
welcome to use or define their own build system.

# Why?
Why? You come here of your own volition, take a look at my _art_, and dare to ask me "why?"

By what right, by what imagined _privilege_ to you believe you have not only the right but the _capacity_ to know why I
have done this? You, who live a life I not only cannot but **choose** not to know about, crawl from whatever cesspool
that saw fit to curse me by issuing forth the likes of _you_ and bring yourself before the likes of **ME** to question
my ineffable motivations!?

## Main reason
I wanted to.

## Secondary reason
Because I can.

## Tertiary reason
It aligned with my goals.
