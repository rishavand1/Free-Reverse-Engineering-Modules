# Topics

* CPU Basics
* Registers
* Memory Layout
* Stack vs Heap
* x86 vs x64

#### Lab

* Stack visualization
* Register observation

# Tools

* x64dbg

Here is the complete, professional Markdown template for **Module 2: Computer Architecture for Reverse Engineers**. You can copy and paste this directly into your GitHub repository's `README.md` or module file.

---

# Module 2: Computer Architecture for Reverse Engineers

This module covers how a computer operates under the hood. When reverse-engineering a program, understanding the backend execution cycle, memory layout, and data manipulation is crucial for tracking execution flow.

---

## 1. CPU Basics

The **Central Processing Unit (CPU)** is the brain of the computer. Its primary job is to execute instructions through a continuous cycle known as the **Instruction Cycle**.

### The Fetch-Decode-Execute Cycle

* **Fetch:** The CPU retrieves an instruction from the system memory (RAM).
* **Decode:** The Control Unit breaks down the instruction to understand what operation needs to be performed (e.g., addition, data transfer, jump).
* **Execute:** The CPU carries out the operation using its internal components, such as the Arithmetic Logic Unit (ALU).

> 💡 **Example:** If your high-level code contains `int x = 5 + 10;`, the CPU fetches the binary instructions for addition, loads the values `5` and `10`, uses the ALU to compute `15`, and writes the result back into memory.

---

## 2. Registers

Registers are **ultra-fast, internal storage locations** built directly into the CPU. Since reading from and writing to system RAM is relatively slow, the CPU utilizes registers to store temporary data, memory addresses, and the immediate results of calculations.

### Key x64 Registers for Reverse Engineering

* **RAX (Accumulator Register):** Used for arithmetic operations and heavily relied upon to store the **return value** of a function.
* **RSP (Stack Pointer):** Always points to the current **top of the Stack** (the lowest memory address of the current stack frame).
* **RBP (Base Pointer/Frame Pointer):** Points to the **base (starting point)** of the current function's stack frame, used to reference local variables and parameters.
* **RIP (Instruction Pointer):** Holds the memory address of the **next instruction** waiting to be executed. Controlling `RIP` means controlling the execution flow of the program.

---

## 3. Memory Layout

When an Operating System executes a program, it allocates a structured **Virtual Memory Space** for the process. This memory layout is organized into distinct segments:

```
+---------------------------+ Low Memory Addresses
| .text (Code Segment)      | -> Contains the actual executable machine code instructions
+---------------------------+
| .data / .rdata (Data Seg) | -> .data holds initialized global/static variables; .rdata holds constants
+---------------------------+
| Heap                      | -> Dynamically allocated memory space (grows upward)
+---------------------------+
|                           |
|  vvv  Free Memory  vvv    |
|                           |
+---------------------------+
| Stack                     | -> Stores local variables & function frames (grows downward)
+---------------------------+ High Memory Addresses

```

---

## 4. Stack vs. Heap

While both components exist within the system RAM to store application data, they function with completely different allocation rules and structural behaviors.

| Feature | Stack | Heap |
| --- | --- | --- |
| **Allocation** | Automatic (managed implicitly by the CPU and compiler). | Manual (managed explicitly by the programmer via `malloc`/`new` or `free`/`delete`). |
| **Structure** | LIFO (Last In, First Out) architecture. | Unstructured; a pool of free-floating memory blocks. |
| **Growth Direction** | Grows **downward** (from High to Low memory addresses). | Grows **upward** (from Low to High memory addresses). |
| **Access Speed** | Extremely fast due to dedicated CPU pointers (`RSP`/`RBP`). | Slower due to pointer overhead and allocation lookups. |
| **Common Use Cases** | Function parameters, local variables, return addresses. | Large dynamic structures, global buffers, objects with unpredictable lifespans. |

---

## 5. x86 vs. x64

These terms represent the architectural evolution of CPU capabilities, defining data bus widths and addressable memory constraints.

* **x86 (32-bit Architecture):** Uses 32-bit wide registers (prefixed with "E", e.g., `EAX`, `ESP`, `EIP`). It is mathematically capped at referencing a maximum of **4 GB of RAM**.
* **x64 (64-bit Architecture):** Extends registers to 64 bits (prefixed with "R", e.g., `RAX`, `RSP`, `RIP`). It can address up to **16 Exabytes of RAM** and introduces 8 additional general-purpose registers (`R8` through `R15`) to reduce memory access overhead.

---

---

# Lab Guide: Stack Visualization & Register Observation

This practical lab focuses on monitoring register shifts and stack alterations dynamically using the **x64dbg** debugger.

### Tools Required

* [x64dbg Debugger](https://x64dbg.com/)
* A native Windows binary target (e.g., `C:\Windows\System32\notepad.exe`)

---

### Step-by-Step Lab Execution

#### Step 1: Loading the Executable into the Debugger

1. Launch **x64dbg** (ensure you open `x64dbg.exe` for 64-bit applications).
2. Navigate to `File` -> `Open` and select `notepad.exe` from your target directory.
3. The debugger will halt execution automatically at the **System Breakpoint** or the application's **Entry Point** (the very first instruction).

#### Step 2: Observing the Register Pane

1. Look at the **Top-Right** quadrant of the user interface to locate the **Registers Pane**.
2. Identify `RIP` (Instruction Pointer). Notice how the address assigned to `RIP` perfectly matches the address highlighted in red within the main **Disassembly View** (CPU execution window).

#### Step 3: Analyzing the Stack Pane

1. Look at the **Bottom-Right** quadrant of the interface to locate the **Stack Pane**.
2. Note the columns present: **Address**, **Value**, and **Comment**.
3. Cross-reference the memory address currently held in the `RSP` register with the top row of the Stack window. They will point to the exact same location.

#### Step 4: Step Execution and State Tracking

1. Press **F8 (Step Over)** to execute a single assembly instruction.
2. Observe the changes:
* `RIP` updates immediately to point to the subsequent line of instruction.
* Any register modified by the executed instruction changes its color to **Red**, signifying an immediate state modification.


3. Continue stepping with **F8** until you hit instructions dealing explicitly with data pushing or popping:
* **`PUSH` Instruction:** Watch the value update on the Stack. Note that the address inside `RSP` decreases because the stack grows downward.
* **`POP` Instruction:** Watch the value clear from the stack frame view. Notice that the address inside `RSP` increases.



---

### Key Takeaways from this Lab

* **Registers** change values continuously as the application executes instructions.
* **RIP** tracks your exact debugging location line-by-line.
* **RSP (Stack Pointer)** drops in value when data is pushed and rises when data is popped, confirming that the stack grows downward in memory.
