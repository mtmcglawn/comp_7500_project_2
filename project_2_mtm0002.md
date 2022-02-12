# Project 2

Matthew Tyler McGlawn

02/11/2022

## 1. Design

The idea that I had for my design was to create a pwordcount Driver that would feed into the main functionality of the application.
By doing this, it will make testing much easier in the future.
This main pwordcount functionality is where most of the major error checking will occur, as well as input checking.
This will then call a function that creates the two processes - a child process and parent process.
Each process is separated out from this pipelining function to allow for easier testing.

## 2. Implementation

I originally wrote the entire program into 1 single "main" function.
From this, I would extract sections that I believed would make for good separate functions.
After I broke the single function into multiple functions I started adding a build system (including the build script).
After the initial build script was placed, I then started to place groups of functions together into their own separate files.
After the files were made, I started to make tests for each file.
I made these tests in such a way that you can run them independently within the directory of the file you want to test.

## 3. Difficulties

The main difficulty that I ran across was linking the files appropriately for the way I wanted the tests to run.
This was due to the layout of the directories as `cmake` can easily find dependencies within the same project or in subdirectories.

## 4. Sample Running

Sample Input:
```
$ ./pwordcount <file_name>
```

Sample Output:
```
Process 1 is readingfile "<file_name>" now...
Process 1 starts sending data to Process 2...
Process 2 finishes receiving data from Process 1...
Process 2 is counting words now..
Process 2 is sending the result back to Process 1..
Process 1: The total number of words is #.
```
