# Employee Management System in C

A simple console-based application for managing employee records, written in C.  
The program uses binary file operations and a menu-driven interface to perform typical CRUD operations and generate reports.

## 📋 Features

- Add new employees and save them in a binary file (`angajati.dat`)
- View all registered employees
- Search for an employee by code
- Update an employee’s information
- Apply a 10% salary raise to employees under a certain threshold
- Delete an employee by code
- Reset the entire database
- Generate reports:
  - All employees
  - Employees with salary above a threshold
- Display first matching employee with salary above a given value

## ⚙️ Technologies Used

- C programming language
- File handling in binary mode (`fread`, `fwrite`, `fopen`, `fclose`)
- Structured data (`struct`)
- Command-line interface

## 🧠 Key Concepts Practiced

- Procedural programming
- File I/O and data persistence
- Input validation and error handling
- Control structures (loops, conditionals, switch-case) 
- Buffer cleanup and safe string input with `fgets`

## 📌 How to Compile and Run 

```bash
gcc -o employee_app ProiectAtp_Comentarii.cpp
./employee_app
