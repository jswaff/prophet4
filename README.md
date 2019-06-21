# prophet4

Prophet4 is, or will be, a chess playing program written in C.  It is the successor to Prophet3, and as the name suggests, the third major rewrite of the Prophet chess engine.


## Design Goals


* Use pure C.  Prophet3 is "nearly C" anyway.  It is not an object oriented program. 
* Modularize the codebase.  Group source files into directories according to functionality.  E.g. movegen, eval, search, etc.
* Break the code down into more source files that are more focused in nature.
* Make better use of static functions.
* Make better use of the const qualifier.
* Improve the documentation.  Each function should have at least a brief description of its purpose, a listing of arguments and return value.
* Improve testing coverage.  In general Prophet3 is well tested, but there are some areas the coverage could improve.  
* Use a proper test harness, e.g. GoogleTest or the like.  The release binary should not contain the test code.  Prophet3 uses assertions exclusively, and all the test code is built into the binary (even though it can't be executed when compiled with the NDEBUG flag).
* Make use of memory leak detectors such as Valgrind on each release.
* Produce a static library containing the move generation, evaluation, and search related functions.  It will not include the opening book related code or the Xboard protocol related code.  The intent is to modularize the core functionality for inclusion in other projects.
* Retire SQLite.  It never felt like a relational database was a good fit for the opening book.  Replace with a Key-Value store type database, possibly LMDB.


## Status

6/16/19 - move generator complete.  Google Test is being used for the test code.  Many tests have been added to validate all the functionality added thus far, including a wide variety of perft type functions to test move generation in a number of edge cases.  Perft numbers all check out.  Move gen speed is comparable to Prophet3, which is to be expected.  Valgrind has not found any memory leaks.

The next step will be to add the scaffolding for the protocol handler decode-and-dispatch mechanism.  There will be one protocol handler that implements the XBoard protocol, and a smaller handler to add some custom commands.  Following that I will likely move on to the evaluation routines.
