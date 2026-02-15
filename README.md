
# OS_command – Custom Linux Process Viewer

##  Project Overview
`OS_command` is a C project that implements a custom command called **`my_ps`**.  
This command merges process information from two standard Linux commands:

- `ps aux` → Displays all processes with details like USER, PID, CPU, MEM, COMMAND.  
- `ps -eLf` → Displays thread-level details such as PID, LWP, NLWP.  

The merged output is written into **`merged.txt`** and displayed on the terminal, effectively behaving like a new process viewer.
---

##  Features
- Executes system commands using `system()`.
- Reads outputs from files (`x1.txt`, `x2.txt`) using `fopen()`, `fscanf()`.
- Merges process and thread information by PID.
- Writes combined data into `merged.txt` using `fprintf()`.
- Displays the merged file in the terminal.

---

## 🛠️ Prerequisites
- Linux environment with `ps` command available.
- Basic knowledge of:
  - File handling (`open()`, `close()`, `fscanf()`, `fprintf()`).
  - System calls (`system()`).
  - Process management concepts.

---

## How to Compile & Run
gcc main.c -o my_ps
./my_ps

---

## 📄 Example Output
```
USER   PID   COMMAND        LWP   NLWP
root   123   /usr/bin/bash  123   1
user1  456   /usr/bin/vim   789   3
```

---

## 📂 Repository Contents
- `main.c` → Source code for `my_OS_command`.  
- `main_Output.png` → Screenshot of sample output.  
- `README.md` → Project documentation.

---

👉 This README gives your repo a professional look and makes it easy for anyone (including your viva examiner) to understand the project quickly.

Would you like me to also add a **flow diagram (ASCII or markdown)** showing how `ps aux` + `ps -eLf` → merge → `merged.txt` → terminal, so your README looks even more impressive?
