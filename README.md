# A2 Simulated File System [October 2024]

Welcome to the **A2 Simulated File System** project! This is a personal exploration into creating a simple simulated file system in C, where a regular file stands in for the hard drive, storing both file contents and metadata. This project simulates basic file system operations, experimenting with free block allocation and deallocation using well-known memory management algorithms.

## Overview

This simulated file system is a single-level system with no directories, just a collection of files. File data is stored in a contiguous block within a simulated hard drive, and the metadata—such as file names, offsets, and sizes—is managed in a fixed array at the start of the file.

### Key Concepts

- **File Metadata**: Stored in an array of `struct Fnode`, containing the file's name, starting byte offset, and length in bytes.
- **Free Space Management**: The free space in the data region is managed using a linked list of free blocks. 
- **Free Block Algorithms**: Implement both first-fit and best-fit algorithms to manage how files are stored and deleted.

## Features

1. **File Creation and Deletion**: Files are created in contiguous chunks, and their metadata is updated in the array. Deletion updates the free list, consolidating blocks if possible.
2. **Free List Management**: Maintain a linked list to track free blocks and experiment with algorithms to manage space efficiently, balancing speed and fragmentation.
3. **Transaction System**: Simulate a series of file operations using a transaction-based model, where different commands (create, delete, show free list, etc.) can be tested.
4. **Testing and Experimentation**: Write custom test cases to compare the performance and behavior of the first-fit and best-fit algorithms under various scenarios.

## How It Works

- **Initialization**: The `init_fs` function sets up the simulated file system, creating an initial free block.
- **File Operations**: Functions like `create_file` and `delete_file` manage file data and update the metadata and free list.
- **Free List Algorithms**: Implement and compare two strategies:
  - **First-Fit**: Finds the first block large enough for the file.
  - **Best-Fit**: Finds the smallest block that fits the file to minimize wasted space.

## Getting Started

1. **Setup**: Run `make` to compile the project and generate the executables `ffsim` (first-fit) and `bfsim` (best-fit).
2. **Run a Sample Test**: 
   ```bash
   ./ffsim testfiles/test_sample
   ```
3. **Transaction Files**: Use transaction files to apply sequences of file operations and observe how the system manages free space.

## Key Files

- **simfile.c**: Main entry point, handles setup and transaction processing.
- **transactions.c**: Reads and processes transaction files, applying operations on the file system.
- **file_ops.c**: Contains core functions for file creation, deletion, and metadata management.
- **free_list_common.c**: Common functions for managing the free list.
- **free_list_first_fit.c & free_list_best_fit.c**: Implementations of the first-fit and best-fit algorithms.

## Running Tests

Create your own transaction files to test different scenarios. Include edge cases and situations that highlight the strengths and weaknesses of each allocation algorithm. Example scenarios include file creation that leads to fragmentation, deletion that consolidates free blocks, and comparisons of the free list structure using different algorithms.

## What's Next?

This project isn't just about implementing a simulated file system—it's a playground for experimenting with data structures, memory management, and understanding the fundamentals of file system operations. Feel free to extend or modify the code, run your own experiments, and see how different approaches impact performance and fragmentation.

Enjoy tinkering and happy coding!
