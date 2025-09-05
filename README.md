# Multiprogramming Operating System (MOS) Simulation

This repository contains a simulation of a **Multiprogramming Operating System (MOS)** built in two phases.  
The project demonstrates how operating systems manage **job execution, memory, interrupts, and error handling**.

---

## 🚀 Features

### Phase 1
- Job loading and execution.
- Instruction cycle simulation (Load, Store, Compare, Branch).
- Service interrupts:
  - **Read (GD)**
  - **Write (PD)**
  - **Terminate (H)**
- Sequential job execution (no multiprogramming).

### Phase 2
- **Paging and memory management** with Page Table Register (PTR).
- **Process Control Block (PCB)** implementation.
- Error handling and interrupts:
  - **Program Interrupts (PI):** Operation error, Operand error, Page fault.
  - **Time Interrupts (TI):** Time-limit exceeded.
  - **Service Interrupts (SI):** Input, Output, Halt.
- Address mapping (Virtual to Real).
- Error codes & termination messages.

---

## 📂 Project Structure

📦 MOS-Project
┣ 📜 phase1/ # Phase 1 implementation
┣ 📜 phase2/ # Phase 2 implementation
┣ 📜 docs/ # Project documentation (Phase1 & Phase2 PDFs)
┣ 📜 README.md

---

## ⚙️ How to Run

1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/MOS-Project.git
   cd MOS-Project
2. Navigate to phase1/ or phase2/ and run the respective code.

3. Provide input files in the required format ($AMJ, $DTA, $END control cards).

4. Outputs will be generated in the designated output file.

---

## 🧾 Example Input Format

Given in input.txt file for phase 1 and input2.txt file for phase 2.
Ref; 
  $AMJ ...
  <Program Cards>
  $DTA
  <Data Cards>
  $END

---

## 📜 Error Codes

0 → No Error
1 → Out of Data
2 → Line Limit Exceeded
3 → Time Limit Exceeded
4 → Operation Code Error
5 → Operand Error
6 → Invalid Page Fault

---

## 🎯 Learning Outcomes

Understand the internal working of a simple Operating System.
Learn about interrupt handling, job scheduling, memory paging, and error management.
Develop structured thinking for system-level programming.
