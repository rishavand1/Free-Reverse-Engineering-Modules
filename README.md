
# 🚀 Free Reverse Engineering Modules

Welcome to the ultimate beginner's companion guide for reverse engineering. This repository contains a structured, 4-module curriculum designed to take you from foundational computer architecture concepts to analyzing your first compiled program using modern reverse engineering tools.

---

## 🗺️ Module Study Pathway

To get the most out of this course, follow the modules sequentially. Each module builds the theoretical foundation required to complete the final practical challenge.

### 🛑 Step 1: Learn the Foundations
* **[Module 1: Introduction to Reverse Engineering](https://github.com/rishavand1/Free-Reverse-Engineering-Modules/blob/main/Free%20Module%201:%20Introduction%20to%20Reverse%20Engineering.md)**
    * *What you'll learn:* Fundamental concepts, the difference between forward and reverse engineering, and setting up your mindset.
* **[Module 2: Computer Architecture for Reverse Engineers](https://github.com/rishavand1/Free-Reverse-Engineering-Modules/blob/main/Free%20Module%202:%20Computer%20Architecture%20for%20Reverse%20Engineers.md)**
    * *What you'll learn:* How CPUs process data, memory layout (Stack vs. Heap), and how computers run programs behind the scenes.

### ⚙️ Step 2: Bridge Code to Hardware
* **[Module 3: Assembly Language Basics](https://github.com/rishavand1/Free-Reverse-Engineering-Modules/blob/main/Free%20Module%203:%20Assembly%20Language%20Basics.md)**
    * *What you'll learn:* Low-level instructions ($x86$/$x64$), CPU registers, and reading assembly code before it gets decompiled.

### 💻 Step 3: The Practical Challenge
* **[Module 4: Your First Crackme](https://github.com/rishavand1/Free-Reverse-Engineering-Modules/blob/main/Free%20Module%204:%20Your%20First%20Crackme.md)**
    * *What you'll learn:* Putting everything together to analyze a real binary, reverse-engineer its internal logic, and extract hidden credentials.


## 🛠️ The Practical Blueprint: `pass.exe`

In a real-world scenario, software is closed-source. Inspecting a compiled binary directly using standard text commands (such as running `cat pass.exe` in a terminal) will only yield unreadable machine code, compilation artifacts, and junk data. 

To keep this introductory lab accessible, we have provided the original, clean C source code (`main.c`) below to serve as your map and blueprint. It allows you to visualize how high-level code maps directly to compiled logic:

```c
#include <stdio.h>
#include <string.h>

int main(void)
{
    int iVar1;
    char local_48[64];

    printf("Enter Password: ");
    scanf("%s", local_48);

    iVar1 = strcmp(local_48, "1234");

    if (iVar1 == 0) {
        puts("You Pass");
    } else {
        puts("Try Next Time");
    }

    return 0;
}

```

---

## 📋 Step-by-Step Practical Methodology

When you are ready to tackle the lab in **Module 4**, use the following industry-standard static analysis workflow:

### 1️⃣ Phase 1: Initial Triage (`file` command)

Before loading the file into complex tools, gather metadata from your command line:

```bash
file pass.exe

```

> **Insight:** This reveals the file's architecture (32-bit vs 64-bit), target OS environment, and whether the binary is **stripped** or **not stripped** (leaving debugging symbols intact).

### 2️⃣ Phase 2: Static Analysis in Ghidra

1. Open **Ghidra** and create a new project.
2. Import `pass.exe` into the project and open it with the CodeBrowser tool.
3. Select **Yes** when prompted to run **Auto-Analysis**.
4. In the **Symbol Tree** panel on the left, expand the **Functions** folder.
5. Locate and click on `main` to populate the Decompiler window.

### 3️⃣ Phase 3: Auditing Decompiled Validation Logic

Once inside the `main` module, reverse-engineer how the authentication behaves:

* **The Mechanism:** The program passes your input buffer (`local_48`) into `strcmp()` alongside a hardcoded reference string.
* **The Logic:** The condition `if (iVar1 == 0)` evaluates true only when `strcmp` returns `0`. In C logic, `strcmp` returns `0` exclusively during an exact, identical string match.
* **The Extraction:** Because your input must match the hardcoded string exactly to trigger the `"You Pass"` execution path, the valid password required to crack this challenge is definitively **`1234`**.

---

## 🚀 Moving Forward

Once you master this baseline, upcoming modules will introduce common binary defenses:

1. **Stripped Binaries:** Where function names like `main` are removed, forcing you to trace logic from the raw `entry` point.
2. **String Obfuscation:** Where passwords are encrypted or XORed in memory to bypass basic string extraction methods.

Happy Reversing!

```

```
