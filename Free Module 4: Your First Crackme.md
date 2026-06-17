# Free Module 4: Your First Crack

## 🔐 Simple Password Checking Program (C Language)

### 📌 What this program does
This program:
1. Asks the user to enter a password.
2. Compares it with a fixed password `"1234"`.
3. Prints whether the password is correct or not.

#### Lets crack it 

I have attached the pass.exe with module 


##### This is the code of program pass.exe

To keep this module beginner-friendly, the source code for pass.exe is provided below. In a real-world scenario, source code is rarely available, and inspecting a compiled binary directly (such as running cat pass.exe) will only yield unreadable machine code and junk characters.

Otherwise you see this only after doing *cat pass.exe*

<img width="1252" height="455" alt="cat pass" src="https://github.com/user-attachments/assets/42b728ab-6b6a-4ab0-899f-80a7d1a92bee" />

To bypass that initial complexity and help you focus purely on the logic, i have provided the clean C source code below to guide your understanding.


```c
#include <stdio.h>
#include <string.h>

int main() {
    char password[50];

    printf("Enter Password: ");
    scanf("%49s", password);

    if (strcmp(password, "1234") == 0) {
        printf("You Pass\n");
    } else {
        printf("Try Next Time\n");
    }

    return 0;
}

```
#### Lets run it on Compiler with random password it will help to know how the program is working 

<img width="1166" height="697" alt="exe program" src="https://github.com/user-attachments/assets/f3538966-0981-45c7-84ce-0b741168890e" />

Password not matched return as Try Next Time !


### Now what to do ?

Check the .exe file in kali

***1. Initial Triage (file <path>)***

Using the file command first is the perfect starting step. It prevents you from wasting time. For 
example, it tells you:Architecture: Whether it's 32-bit ($x86$) or 64-bit ($x86\_64$), which tells you what size registers to look for in assembly.Format/OS: ELF (Linux) vs. PE (Windows), letting you know what system environment it expects.

Stripped vs. Not Stripped: If a file is "not stripped," it means debugging symbols are left intact—which is why you are easily able to see the function named main in Ghidra!

<img width="1257" height="167" alt="file pass" src="https://github.com/user-attachments/assets/034a1c3d-4d60-46f8-bc00-0cd79aa310e2" />

It shows x86 means 32-bit architecture is there so we will go with Ghidra Tool.

## Now it's time to do Reverse Engginering to know the password .

### Methodology

1. Import the file.exe to Ghidra .

<img width="793" height="562" alt="import" src="https://github.com/user-attachments/assets/d374c7fc-ebcf-462a-bf6f-6fd252f046cd" />

#### Next

<img width="791" height="596" alt="import2" src="https://github.com/user-attachments/assets/023070a6-28e9-4f38-9fae-dbad4708d108" />

#### Double click the file.exe

After this start Analyzing 

<img width="691" height="282" alt="analyze" src="https://github.com/user-attachments/assets/a13389e4-5b00-44c6-b539-169d11ba12b0" />

After Analyzing finished go to Main Function as mentioned in picture. 

<img width="175" height="211" alt="main" src="https://github.com/user-attachments/assets/d585a0f6-d802-47ff-93d9-5f1f899af0f0" />


Now you will find this code in the Right most of the Ghidra Tool .


### 🧾 The Code (Cleaned Up)
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

<img width="1915" height="701" alt="Mod4" src="https://github.com/user-attachments/assets/7169e29e-4e7d-4b9d-ae39-af58c890a2fc" />


### After doing all these things we have to now do some logical things in the main function to find out the password. 

### Let's Go!!!!!

#### Let's Understand what does this main function do ?

```c 
#include <stdio.h>   // Includes the Standard Input and Output library (used for printf and scanf)
#include <string.h>  // Includes the String library (used for the strcmp function)

int main(void)
{
    int iVar1;          // Declares an integer variable to store the result of the password comparison
    char local_48[64];  // Declares a character array (buffer) that can hold up to 64 characters of user input

    // Prints a message to the screen asking the user for a password
    printf("Enter Password: ");
    
    // Reads the user's input from the console and stores it in the 'local_48' buffer
    // Note: %s stops reading at whitespace and doesn't limit input size, making it vulnerable to buffer overflows
    scanf("%s", local_48);

    // Compares the user's input ('local_48') with the hardcoded string "1234"
    // strcmp returns 0 if both strings are an exact match
    iVar1 = strcmp(local_48, "1234");

    // Checks if the result of strcmp is 0 (meaning the correct password was entered)
    if (iVar1 == 0) {
        // If the password matches "1234", print "You Pass"
        puts("You Pass");
    } else {
        // If the password does not match, print "Try Next Time"
        puts("Try Next Time");
    }

    // Returns 0 to the operating system, indicating the program executed and finished successfully
    return 0;
}

```

Key Findings & Password Extraction

* Mechanism: The program utilizes the standard library function strcmp() to evaluate user input       against a hardcoded credential.

* Logic: The conditional check if (iVar1 == 0) triggers the successful path ("You Pass") exclusively   when the comparison evaluates to zero (a perfect match).

* Solution: The embedded reference string is "1234", making 1234 the valid password required to pass   the check.

## Congrats you have cracked it !!! 

Now check it after using the same password 

<img width="1167" height="605" alt="pass" src="https://github.com/user-attachments/assets/a0db6be3-534b-4396-ad9c-e719b23545d5" />


### Some important tips !!

🚀 Next-Level Tips for Your Methodology

As you move on to harder crackmes in your modules, the creators will try to break this specific workflow. Here is what to look out for and how to adapt:

* What if main disappears? If a binary is stripped, the symbols are erased, and you won't see a function named main.

The Fix: Look at the entry function in Ghidra. The entry function usually calls a function named __libc_start_main. One of the parameters passed into __libc_start_main is the actual address of the real main function.

* What if the password isn't in plain text? Hardcoded strings like "1234" are easy to spot. More advanced challenges will encrypt, obfuscate, or dynamically generate the password at runtime (e.g., using XOR operations or custom algorithms).

The Fix: Instead of just reading the string, you'll have to reverse-engineer the math or logic being applied to your input variable (local_48) inside the if statement.

* Incorporate strings before Ghidra:
Before even opening a heavy tool like Ghidra, try running strings <file path> in your terminal. If a password or a flag is simple and unencrypted, it will often pop right up in the terminal text output instantly, saving you the time of loading a full decompiler.

