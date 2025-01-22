# Red-Black Tree and Binary Search Tree Implementation

## Overview

This project implements **Red-Black Trees (RBT)** and **Binary Search Trees (BST)** in C++ with a focus on efficient data operations. The project supports essential functionalities such as insertion, deletion, searching, and tree traversal while ensuring balanced tree properties for optimal performance.

## Features

### Binary Search Tree (BST)
- Insertion and deletion of nodes.
- Finding minimum and maximum values.
- Successor and predecessor retrieval.
- Inorder traversal of the tree.

### Red-Black Tree (RBT)
- Self-balancing tree structure.
- Insertion and deletion with rebalancing (fix-up operations).
- Left and right rotations.
- Sentinel node to manage boundaries.

### Object-Oriented Design
- Encapsulation using C++ classes.
- Inheritance from BST to RBT to extend functionality.
- Virtual functions for flexibility and abstraction.

## File Structure

bst.h - Binary Search Tree header. 
bst.cc - Binary Search Tree implementation. 
rbt.h - Red-Black Tree header. 
rbt.cc - Red-Black Tree implementation. 
db.h - Data management header. 
db.cc - Data management implementation. 
main.cc - Program entry point. 
Makefile - Build script. 
test_t7_s1 - Test file with 7 elements and seed 1. 
test_t12_s1 - Test file with 12 elements and seed 1. 
README.md - Project documentation. 


## Installation

### Prerequisites
- A C++ compiler that supports C++11 or later (e.g., `g++`).
- `make` build system.

### Compilation

To compile the project, run:
make

### Execution
To execute the program:
./rbtree <test_file>

Example usage:
./rbtree test_t7_s1

## Testing
The project includes two test files to validate the implementation:

test_t7_s1 – Inserts 7 elements into the red-black tree and verifies output.
test_t12_s1 – Inserts 12 elements into the red-black tree for larger test coverage.

### Running Tests
Run the provided test files with:
./rbtree test_t7_s1
./rbtree test_t12_s1

Expected outputs are provided for validation purposes.

## Usage Examples
Below is an example of how the program processes input files:
Input (test_t7_s1):
10 20 30 15 5 25 35

Output:
Inorder traversal: 5 10 15 20 25 30 35
Minimum value: 5
Maximum value: 35

## Key Concepts
### Red-Black Tree Properties:

Every node is either red or black.
The root is always black.
Red nodes cannot have red children.
Every path from a node to its descendant leaves has the same number of black nodes.

### Binary Search Tree Operations:

Each node has at most two children.
Left subtree contains smaller values; right subtree contains larger values.

## Memory Management 
The project ensures memory efficiency by properly allocating and deallocating resources.
Run the following command to check for memory leaks using valgrind:
valgrind --leak-check=full ./rbtree test_t7_s1

## Notes
The implementation adheres to standard tree algorithms with efficiency in mind.
File names should be provided dynamically as command-line arguments.

## License
This project is open-source and available for educational and practical use.
