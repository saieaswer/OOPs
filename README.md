# Banking System OOP Practice (C++)

## Overview

This project is a **C++ Object-Oriented Programming practice implementation** of a simple banking system.

The goal of the project is to understand how real-world systems can be modeled using **inheritance, polymorphism, and proper resource management in C++**.

The implementation focuses on learning core C++ concepts such as:

* inheritance
* abstract classes
* virtual functions
* polymorphism
* dynamic memory management
* Rule of Three / Rule of Five
* move semantics

This project is primarily written for **learning and interview preparation**.

---

# Architecture

The system models a simplified banking environment.

### Base Class

`BankAccount`

This class represents a generic bank account and contains the common properties and operations shared by all account types.

**Attributes**

* accountNumber
* accountHolderName
* accountType
* balance

**Common Operations**

* deposit()
* withdraw()
* displayBalance()
* showAccountDetails()

The class also manages **dynamic memory for accountType**, which requires proper copy and move semantics.

---

# Derived Classes

## SavingsAccount

Represents a savings account that earns interest.

Additional attribute:

* interestRate

Features:

* Withdrawal allowed only if sufficient balance exists
* Displays interest rate in account details

---

## CurrentAccount

Represents a current account that allows overdraft.

Additional attribute:

* overdraftLimit

Features:

* Allows negative balance within the overdraft limit
* Prevents withdrawals beyond the overdraft threshold

---

# Class Relationship

SavingsAccount **IS-A** BankAccount

CurrentAccount **IS-A** BankAccount

Each object maintains its **own independent balance**.

A user may own multiple accounts (for example, a savings account and a current account), represented as separate objects.

---

# OOP Concepts Practiced

## 1. Inheritance

Derived classes extend the functionality of the base class.

Example hierarchy:

BankAccount <- SavingsAccount

BankAccount <- CurrentAccount

Access rules for **public inheritance**

| Base Member | In Derived   |
| ----------- | ------------ |
| public      | public       |
| protected   | protected    |
| private     | inaccessible |

---

## 2. Abstract Classes

The base class defines a **pure virtual function**.

virtual void withdraw(float amount) = 0;

Because of this, `BankAccount` becomes an **abstract class**.

Important points:

* Objects of BankAccount cannot be created.
* Pointers and references to BankAccount are allowed.

Example:

BankAccount* acc;

But this is not allowed:

BankAccount acc; ❌

Derived classes must implement the pure virtual function.

---

## 3. Runtime Polymorphism

Virtual functions enable **dynamic dispatch**.

Example scenario:

BankAccount* acc = new SavingsAccount(...);
acc->showAccountDetails();

Even though the pointer type is `BankAccount*`, the function from `SavingsAccount` executes.

The decision happens **at runtime**.

---

## 4. Virtual Destructor

When a class contains virtual functions, its destructor should usually be **virtual**.

virtual ~BankAccount()

### Why this is important

Consider:

BankAccount* acc = new CurrentAccount(...);
delete acc;

Without a virtual destructor:

Only the **BankAccount destructor** runs.

The derived destructor does **not execute**, causing resource leaks.

### Correct behavior with virtual destructor

Destruction order:

CurrentAccount destructor
BankAccount destructor

This ensures all resources are released properly.

---

## 5. Rule of Three

If a class manages resources, it must implement:

* Destructor
* Copy Constructor
* Copy Assignment Operator

This project allocates memory dynamically for:

char* accountType

Therefore the `BankAccount` class implements the **Rule of Three**.

---

## 6. Deep Copy vs Shallow Copy

Default copy behavior performs **member-wise copying**.

This works for primitive types such as:

* int
* float

However, for pointers this creates a **shallow copy**.

*Example problem:*

object1.accountType → memory

object2.accountType → same memory

If one object deletes the memory, the other object becomes invalid.

To avoid this, a **deep copy** is implemented.

---

## 7. Move Semantics (Rule of Five)

Move semantics allow **resource ownership transfer instead of copying**.

Benefits:

* avoids unnecessary memory allocations
* improves performance

Operations related to move semantics:

* move constructor
* move assignment operator

---

## 8. Important Compiler Rule

C++ automatically generates move operations **only if none of these are user-defined**

* destructor
* copy constructor
* copy assignment operator

If any of these exist, the compiler assumes manual resource management and does **not generate move operations automatically**.

---

## 9. Const Correctness

Functions that do not modify object state should be marked `const`.

Example:

float displayBalance() const;

Benefits:

* prevents accidental modification
* allows calling the function on const objects

---

## 10. String Literal Safety

Functions receiving string literals should use:

const char*

Reason:

String literals are stored in **read-only memory** and must not be modified.

---

# Key Concepts Covered

This project demonstrates:

* Object-Oriented Programming
* inheritance
* polymorphism
* abstract classes
* virtual functions
* virtual destructors
* dynamic memory management
* deep vs shallow copy
* Rule of Three
* Rule of Five
* move semantics
* const correctness

---

# Purpose of This Project

This implementation was written to:

* strengthen understanding of C++ OOP design
* practice memory-safe class design
* explore polymorphism and inheritance
* prepare for C++ technical interviews
