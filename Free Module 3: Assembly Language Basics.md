# Topics

* MOV
* PUSH
* POP
* CALL
* RET
* CMP
* JMP

# Lab

* Small assembly programs analyze karna
* Mini Challenge
* Password check function reverse karna

Here is the complete, professional Markdown template for **Module 3: Assembly Language Basics**. You can copy and paste this directly into your GitHub repository's `README.md` or a dedicated module file.

---

# Module 3: Assembly Language Basics

This module bridges the gap between high-level code and machine execution. To reverse engineer effectively, you must understand how fundamental CPU instructions manipulate data and steer execution flow.

---

## 1. Core Assembly Instructions

### MOV (Move Data)

The `MOV` instruction copies data from a source location to a destination location.

* **Syntax:** `MOV Destination, Source`
* **Example:** `MOV RAX, 0x5`
* *What it does:* Copies the hexadecimal value `5` directly into the `RAX` register. The previous value in `RAX` is overwritten.



### PUSH (Push onto Stack)

The `PUSH` instruction places a value onto the top of the stack. It automatically decreases the Stack Pointer (`RSP`) to account for the new data.

* **Syntax:** `PUSH Source`
* **Example:** `PUSH RAX`
* *What it does:* Takes whatever value is currently stored inside `RAX` and copies it onto the top of the stack.



### POP (Pop from Stack)

The `POP` instruction removes the top value from the stack and stores it inside a designated destination (register or memory slot). It automatically increases the Stack Pointer (`RSP`).

* **Syntax:** `POP Destination`
* **Example:** `POP RBX`
* *What it does:* Retrieves the value sitting at the top of the stack, loads it into `RBX`, and cleans that slot from the stack.



### CALL (Call Procedure)

The `CALL` instruction redirects code execution to a separate function or procedure. Before jumping, it automatically pushes the address of the next instruction (the return address) onto the stack so the program knows where to return when the function finishes.

* **Syntax:** `CALL FunctionAddress`
* **Example:** `CALL 0x00401050`
* *What it does:* Saves the current location's return address onto the stack and jumps execution to the function located at `0x00401050`.



### RET (Return from Procedure)

The `RET` instruction terminates a function execution. It pops the return address off the top of the stack and jumps back to that address, resuming execution immediately after the original `CALL` instruction.

* **Syntax:** `RET`
* **Example:** Used at the end of functions to hand execution flow back to the parent routine.

### CMP (Compare)

The `CMP` instruction compares two operands by subtracting the second operand from the first. Crucially, it **does not alter** the values of the operands; it only updates the CPU's **Flags Register** (e.g., Zero Flag, Sign Flag) based on the mathematical result.

* **Syntax:** `CMP Destination, Source`
* **Example:** `CMP RAX, 0x10`
* *What it does:* Subtracts `10` from `RAX`. If `RAX` contains `10`, the result is `0`, and the CPU sets the **Zero Flag (ZF = 1)**.



### JMP (Unconditional Jump)

The `JMP` instruction alters execution flow by forcefully changing the Instruction Pointer (`RIP`) to a new target address. It does not look at any condition flags.

* **Syntax:** `JMP TargetAddress`
* **Example:** `JMP 0x00401200`
* *What it does:* Instantly moves the execution line to `0x00401200`.



---

---

# Lab Guide: Small Assembly Program Analysis

In this lab, we will open a binary in **x64dbg** to track how these basic assembly instructions look and behave inside a real debugger environment.

### Prerequisites

* **x64dbg** , **Ghidra** installed.
* Any basic native executable compiled from C/C++ or assembly.

---

### Step-by-Step Lab Execution

#### Step 1: Locating Data Movements

1. Load your executable into **x64dbg** or **Ghidra**
2. Scroll through the Disassembly window until you find an instruction starting with `MOV`.
3. Highlight the instruction line. Note the register names mentioned in the operands.
4. Press **F8** to execute that single `MOV` line and watch the target register turn **Red** in the Registers pane, displaying its brand new value.

#### Step 2: Tracking Stack Operations (`PUSH`/`POP`)

1. Search your code pane for sequential stack adjustments (commonly found at the start and end of functions).
2. When you point `RIP` at a `PUSH RCX` instruction, take a close look at the current address value shown inside the `RSP` register.
3. Press **F8** once to execute the `PUSH`.
4. Notice that:
* The value inside `RSP` decreased (by 8 bytes for a 64-bit application).
* The value from `RCX` is now visible at the very top line of your Stack Pane.


5. Step forward until you hit a corresponding `POP` instruction and watch the values restore while `RSP` increases back to its original state.

---

---

# Mini Challenge: Reversing a Password Check Function

### Scenario

Imagine you are reverse-engineering an unknown program that prompts the user for an authorization key. Below is the simplified assembly code representing the core validation check function:

```assembly
00401A00 | MOV RAX, RCX           ; RCX holds the address of the user's entered password.
00401A03 | MOV RBX, 0x00403020    ; 0x00403020 points to the hardcoded correct password string: "Secret123"
00401A08 | CALL str_compare       ; Internal function that compares strings RAX and RBX
00401A0D | CMP RAX, 0x0           ; If strings match, str_compare returns 0 into RAX
00401A10 | JE success_route       ; Jump to success routine if Zero Flag is set (RAX == 0)
00401A12 | JMP failure_route       ; Otherwise, jump straight to access denied message

```

### Analysis Walkthrough

1. **Identifying Variables:** At memory offsets `00401A00` and `00401A03`, the code uses `MOV` instructions to set up a comparison. It passes the user's input string pointer and a static pointer pointing to a protected memory location.
2. **Locating the Secret Key:** By inspecting the memory address `00403020` in the debugger's **Dump View** (Right-click the address -> *Follow in Dump*), a reverse engineer can easily extract the hardcoded string `"Secret123"`.
3. **Control Flow Redirection:** The `CMP RAX, 0x0` operation verifies if the validation function succeeded. The instruction `JE success_route` (*Jump if Equal*) relies directly on the result of that comparison.

### How to Bypass this Validation Check (Two Methods)

If you wanted to patch this binary to accept any random string as a correct password, you could modify the instructions inside **x64dbg**:

* **Method A (Modifying the Flag Dependency):** You can alter the conditional jump `JE success_route` to an unconditional jump `JMP success_route`. This forces the application to grant entry completely bypassing the string match verification outcome.
* **Method B (Inverting the Logic):** You can patch `JE` (*Jump if Equal*) to `JNE` (*Jump if Not Equal*). This forces the application to treat incorrect password strings as successful entries, allowing you to pass by typing literally anything *except* the real password.
