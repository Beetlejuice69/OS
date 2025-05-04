# VIT Pune - Operating System Project

## 📘 Overview

This project simulates a basic **Operating System** environment that manages job control using paging and memory management techniques. It is divided into **two phases**:

- **Phase 1**: Memory management, loading programs, and job control.
- **Phase 2**: Instruction execution with basic OS services like READ, WRITE, and TERMINATE.

Developed as part of the **Operating Systems Lab** curriculum at **VIT Pune**.

---

## 📂 Project Structure


---

## ⚙️ Phase 1: Program Loading & Memory Management

### ✅ Features Implemented:
- Accepts input via job control cards: `$AMJ`, `$DTA`, `$END`
- Allocates memory using paging (each page = 10 words)
- Creates and initializes a page table
- Loads the program and data into memory
- Handles multiple jobs from a single input stream

### 🔍 Key Concepts:
- **Paging:** Logical to physical memory mapping
- **Job Control:** Handling multiple programs using job IDs
- **Memory Initialization:** Memory is simulated using a 2D char array (`Memory[300][4]`)

---

## 🖥️ Phase 2: Instruction Execution & OS Services

### ✅ Features Implemented:
- Simulates basic instructions:
  - `GD` - Get Data (READ)
  - `PD` - Put Data (WRITE)
  - `H`  - Halt
- Handles **System Interrupts (SI)** and **Program Interrupts (PI)**
- Error Handling:
  - Operation Code Error
  - Operand Error
  - Time Limit Exceeded
  - Line Limit Exceeded
  - Invalid Page Fault
- Supports multiple jobs with context switching

### 🔍 OS Concepts Applied:
- **Instruction Register (IR)** simulation
- **Program Counter (IC)** management
- **Interrupt handling**
- **I/O simulation**

---
