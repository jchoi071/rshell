# rshell

rshell is a simple shell created as a project for the University of California, Riverside's CS100 class. It will be updated with new features and fixes as new assignments are given.

Written with vim in C++ on UCR's hammer server

Usage: ./rshell commands

### Known Bugs
- Many, many memory leaks.
- Occasionally, the shell may display memory-related errors. Commands read from the command line do not cause these errors, while commands read from bash scrop here-documents often cause these errors.
- The exit command occasionally does not work after invalid commands are used. The number of times exit must be entered exactly matches the number of invalid commands.

### License
----

GPL v3.0
