## Description

The Simple Virtual Machine (SVM) is a basic implementation of a virtual machine designed to execute a set of predefined assembly-like commands. This project simulates a lightweight CPU that can perform operations such as storing values in registers, adding values, jumping to specific lines based on conditions, and printing register values. The architecture consists of a set of registers and commands that manipulate data within these registers, making it an excellent educational tool for understanding how low-level programming and virtual machines operate.

### Features

- **Register Management**: Supports multiple registers for storing integer values.
- **Basic Arithmetic Operations**: Allows addition of register values.
- **Conditional and Unconditional Jumps**: Implements jump commands for control flow.
- **Input/Output Operations**: Prints the contents of registers to the console.
- **Simple Command Structure**: Easy-to-understand commands that resemble assembly language.

## Getting Started

### Prerequisites

To compile and run this project, you need:

- A C compiler (e.g., GCC)
- Basic understanding of C programming

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/simple-virtual-machine.git
   cd simple-virtual-machine
   ```

2. Compile the source code:
   ```bash
   gcc -o svm main.c
   ```

3. Run the virtual machine with a command file:
   ```bash
   ./svm commands.txt
   ```

### Usage

Create a text file (e.g., `commands.txt`) with the following commands to execute:

```
put 5, r1
put 3, r2
add r1, r2
prn r2
jmpe r1, r2, 10
jmpu 5
halt
```

- **put**: Store a value in a register.
- **add**: Add values of two registers.
- **prn**: Print the value of a register.
- **jmpe**: Conditional jump if two registers are equal.
- **jmpu**: Unconditional jump to a specified line.
- **halt**: Terminate the program.

### Example Commands File

Here’s a simple example of a command file (`commands.txt`):

```
put 10, r1
put 20, r2
add r1, r2
prn r2
jmpe r1, r2, 8
jmpu 5
halt
```

## Contributing

Contributions are welcome! If you have suggestions for improvements or new features, please fork the repository and submit a pull request.
