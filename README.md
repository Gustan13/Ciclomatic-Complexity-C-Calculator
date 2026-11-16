# Ciclomatic Complexity C Calculator

A simple command line tool that calculates the ciclomatic complexity of C functions.

## Why this software exists

This software exists as an exercise for practicing general software engineering in the context
of software quality. This software is also the solution of a problem present in the fourth
version of Pressman's Software Engineering a Practitioner's Approach.

## How to Build

This program has no prerequisites besides make and gcc. Simply run make inside the project's
directory and run ccalc.

## Current Limitations

### Version 1.0

In this version, the software can't compute the complexity of individual functions, rather the complexity of the file as a whole. This happens due to the lack of a proper parser, which will be added in future versions.
