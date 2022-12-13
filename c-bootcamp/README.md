<center>CSC333 C Bootcamp assignments</center>

<!-- TOC -->

- [C BootCamp](#c-bootcamp)
  - [Description](#description)
  - [Task Overview](#task-overview)
  - [Targets](#targets)
- [Setup](#setup)
  - [* I am assuming a basic knowledge of the UNIX Command line.  If you are new to the command line, I'll be around to help you in class.  You may also find this Unix Command Line Cheat Sheet useful](#-i-am-assuming-a-basic-knowledge-of-the-unix-command-line--if-you-are-new-to-the-command-line-ill-be-around-to-help-you-in-class--you-may-also-find-this-unix-command-line-cheat-sheet-useful)
- [Getting Started](#getting-started)
  - [Cloning the repositories.](#cloning-the-repositories)
  - [Compiling and running the code](#compiling-and-running-the-code)
- [Assignment 1: Modifying factors (Try to do before Friday)](#assignment-1-modifying-factors-try-to-do-before-friday)
  - [Submit](#submit)
- [Assignment 2:](#assignment-2)
  - [Setup:](#setup-1)
  - [Description](#description-1)
  - [Submit](#submit-1)
- [Assignment 3: Linked Lists (Challenge)](#assignment-3-linked-lists-challenge)
  - [Setup](#setup-2)
  - [Description](#description-2)
  - [Submit](#submit-2)

<!-- /TOC -->
# C BootCamp

## Description

The goals of this in-class assignment are as follows:

* introduce you to git, gitlab, and how we'll be using it in this class
* introduce you to C programming, including editing, compiling and debugging code
* introduce you to writing Markdown documents

The assignments include:
* A fun little brute-force algorithm (although, as it turns out, much too simple) for factorization.
* A larger vector-multiplication algorithm, to get you used to operating on arrays of data.
* A linked list algorithm to get you *really* used to pointers

## Task Overview

(check these off as you complete them, but putting an x in the box)

- [X] Complete Setup (clone repos)
- [X] Assignment 1: Factorization
- [X] Assignment 2: Vectors and Pointers 
- [X] Assignment 3: Linked List

## Targets

- [ ] CL.1	Navigate the command line interface 
- [ ] CL.2	create/move/delete files and folders
- [ ] CL.3	SSH and SSH keys
	
- [ ] G.1	create/pull repository
- [ ] G.2	commit and push to a repository
- [ ] G.4	Markdown
	
- [ ] CP.1	C Programming (editing, compiling)
- [ ] CP.2	C Debugging (your code, other's code)
- [ ] CP.5	Memory Management (Allocation and Segmentation Faults)

# Setup

What you'll need for this assignment:

* a terminal app (Terminal on MacOS or puTTY on windows)
* git installed on your computer (via XTools on MacOS, or GitBash on Windows)
* ssh installed on your computer (pre-installed on MacOS and I think on Windows?)
* I am assuming a basic knowledge of the UNIX Command line.  If you are new to the command line, I'll be around to help you in class.  You may also find [this Unix Command Line Cheat Sheet useful](https://files.fosswire.com/2007/08/fwunixref.pdf)
---
# Getting Started

1. Log into slack
2. Log into cs-gitlab.union.edu.  If 
3. On the machine you're using (I'll call this your *development machine*):
   * create a CSC333 folder or directory in the location of your choice.
4. If you already have an ssh keypair generated on your development machine, skip this step.  Otherwise, generate one using the steps provided in my [tutorial](https://cs-gitlab.union.edu/rieffelj/tutorials/-/tree/main/ssh-keys)
5. Add you SSH public key to your gitlab profile (if it isn't there already)
under your profile icon (top right), select "Settings", then "SSH Keys"

---

## Cloning the repositories.

You'll be using two repositories in this course.
   * `csc333-labs-n-demos` (read only) - this is where I'll post lab assignments and starter code
   * `username-csc333` - your personal repository

 From your CSC33 Folder or directory on your development machine:

`git clone git@cs-gitlab.union.edu:rieffelj/csc333-labs-n-demos.git`

(if you're asked for a password, or get an error, then return to the step about SSH keys above.)

You'll see an `week-1-c-bootcamp` directory in there.  Next, clone your personal csc333-<username> project.  This should involve something like this:
 
`git clone git@cs-gitlab.union.edu:username/username-csc333-s21.git` (except with your username)

Next, perform the following steps:

```
cd username-csc333-s21
touch README.md
git add README.md
git commit -m "add README"
git push -u origin master
```

Great! Now move (via  `cp -R` or drag-and-drop) the `week-1-c-bootcamp` directory from the class repo into your personal repo, and add the files to your repository:

```
cd week-1-c-bootcamp
git add factors.c
```

---

## Compiling and running the code

We don't use no stinkin IDEs in this class.  We will be working from the command line!

Try compiling the code:

`gcc factors.c`

And running it:

`./a.out`

Neato!  You may, of course, want to give the executable a different name.  You can do this with the `-o` flag:

`gcc factors.c -o factors`

---
# Assignment 1: Modifying factors (Try to do before Friday) 


First,  modify the [Writeup Markdown](Writeup.md) in the repo to reflect your name.  

Now that that's out of the way, make the following changes to the code to turn it into a variation of a brute force prime-number tester.  This is a contrived problem just to give you a chance to sharpen your c programming skills and play with numbers big enough to produce longer-running programs.

1. Look at the code to understand what is happening
2. try picking other big numbers, and find their factor
3. change the code by:
   1. code should return count of all the divisors (don't break)
   2. print if the number is prime or not
   3. Take some timing, and make a note of them down in your Writeup.
4. Now improve the code by:
   1.  incrementing by 2 instead of 1
   2.  stopping as soon as you reach the square root of the number.
   3. Take some timing rudimentary timing, make a note in your Writeup
You may need to add the line `#include <math.h>` at the top of your program, and then you'll need to compile with the `-lm` flag

`gcc factors.c -o factors -lm`

## Submit

Commit and push to your repo:

*  Your `Writeup.md`,  containing
   * data from steps 3 and 4 above 
   * an explanation of why you might get different time values for the same number
*  Your `factors.c`

---
# Assignment 2: 

- [x] Step 1
- [x] Step 2
- [x] Step 3
- [x] Step 4
- [x] Step 5
- [x] Step 6
- [x] Step 7

## Setup:

* Be sure to add/commit/push your personal repo

## Description 

Now take a look at `vectors.c`, which provides some rudimentary functions to generate random vectors of a given size.    The program takes up to two arguments, the first is the size of the vector, and the second is the random seed (so you can test your code better with a fixed seed);

1. Read and understand how `argc` and `argv` work
2. Read and understand the structure of the normal and the pointer-based vector   functions.
3. Write and test a pointer-based version of `randomize_vector` named `randomize_vector_p`
4. What happens if you mess up the vector size argument and make it bigger than the actual size of the vector? Modify the calls to randomize and print to find out what happens in each case. Make a note in your writeup.
5. Write and test a vector addition function that, given two vectors of the same size, creates a new vector (via calloc) that is the index-wide sum of the two argument vectors.  This function *must* use pointers instead of array indexing.
6. Write and test a vector dot product function that, given two vectors, returns a double that is the vector dot product of the two vectors.
7. Add the timing code from `factors.c` to `vectors.c` and play around with the size of the vectors you're using in the code.  How big can you make them? Does the code ever get slow?  Make a note of your observations in your writeup.

## Submit 

Commit and push to your repo:
* Your updated `Writeup.md` containing:
   * your observations from above.
* Your `vectors.c`

---
# Assignment 3: Linked Lists (Challenge)

## Setup

* Be sure to add/commit/push your personal repo

## Description

The purpose of this assignment is to let you really flex your C pointer skills.  I don't know if you still suffer memories of the linked list lab in CSC270 or CSC120/150, but this will be much easier!

What I love most about linked lists is that they are *very* amenable to recursion, the way that lists in python are.

1. Start by looking at `linked-list.c`.  Work through the code for `insert` adding your own comments along
the way.

2. Next, write and test *recursive* function that, given a pointer to a linked list, prints every item in it, like this:

`1->5->7->10->12->NULL `

I have provided starter code.

(if you are struggling with the recursive implementation I will give you the algorithm in english)

Lines needed: approximately 8, most of which just contain `{`s.

3. Finally, write and test a *recursive* function called `insertRecursive()`.  It should take the same arguments as `insert`, but use recursion to insert a new node containing `N` into the proper place in the linked list.

## Submit 

Commit and push to your repo:
* Update the `README.md` of your personal repo so that it includes this project
  * you can look at the `README.md` in the class Repo for guidance
* Your updated `Writeup.md` containing a very bried description of your code
* Your `linked-list.c`



