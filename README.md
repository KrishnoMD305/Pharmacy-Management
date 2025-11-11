# 🏥 Pharmacy Management System

A comprehensive command-line based Pharmacy Management System developed in C++ for academic purposes. This system provides complete pharmacy operations management including inventory control, sales processing, customer management, and reporting features.

## 📋 Table of Contents

- [Project Overview](#project-overview)
- [Features](#features)
- [System Requirements](#system-requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Core Components](#core-components)
- [File Storage](#file-storage)
- [Login Credentials](#login-credentials)
- [Contributors](#contributors)
- [Academic Information](#academic-information)
- [License](#license)

## 🎯 Project Overview

This Pharmacy Management System is designed to streamline pharmacy operations by providing two distinct user roles: **Admin** and **Pharmacist**. The system handles medicine inventory management, customer records, sales transactions, expiry tracking, and generates comprehensive reports.

**Developed for:** Academic Project - 1st Year, 2nd Semester  
**Language:** C++  
**Type:** Console-based Application

## ✨ Features

### Admin Features
- 📦 **Medicine Management**
  - Add new medicines to inventory
  - Remove medicines from inventory
  - Update medicine details (name, company, price, quantity, expiry date)
  - Restock medicines (using operator overloading)
  
- 📊 **Inventory Operations**
  - View complete medicine inventory
  - Sort medicines by price (ascending/descending)
  - Check expiry and low stock alerts
  - Track expired medicines
  
- 📈 **Reports & Analytics**
  - View sales reports
  - Generate revenue summaries
  - Customer loyalty ranking
  - Total invoices and sales tracking

### Pharmacist Features
- 💊 **Sales Operations**
  - Process medicine sales
  - Generate invoices with automatic calculations
  - Apply customer loyalty discounts
  - Handle existing and new customers
  
- 🔍 **Search Functionality**
  - Search medicines by name
  - Search medicines by company
  
- ⚕️ **Inventory Access**
  - View medicine inventory
  - Check medicine expiry dates
  - Verify stock availability

### Customer Management
- 🎁 **Loyalty Program**
  - Automatic purchase tracking
  - Discount eligibility (5% after 5 purchases, 10% after 10 purchases)
  - Customer ranking by purchase count
  
## 💻 System Requirements

- **Compiler:** C++11 or higher
- **Operating System:** Windows, Linux, or macOS
- **Libraries Used:**
  - `<iostream>` - Input/output operations
  - `<string>` - String manipulation
  - `<algorithm>` - Sorting and searching
  - `<ctime>` - Date and time operations
  - `<sstream>` - String stream processing
  - `<iomanip>` - Formatting output
  - `<vector>` - Dynamic arrays
  - `<fstream>` - File operations

## 🚀 Installation

1. **Clone or Download the Project**
   ```bash
   git clone <https://github.com/KrishnoMD305/Pharmacy-Management.git>
   cd pharmacy-management-system
   ```

2. **Compile the Code**
   ```bash
   g++ -std=c++11 main.cpp -o main
   ```

3. **Run the Application**
   ```bash
   ./pharmacy_system
   ```

## 📖 Usage

### Starting the System

Upon running the application, you'll see the main menu:

```
╔════════════════════════════════════╗
║  PHARMACY MANAGEMENT SYSTEM        ║
╚════════════════════════════════════╝
1. Admin Login
2. Pharmacist Login
3. Exit
```

### Admin Login

**Login Credentials:**
- **Admin ID:** `23070`
- **Password:** `CSE_23`

**Admin Menu Options:**
1. Add Medicine
2. Remove Medicine
3. Update Medicine
4. View Inventory
5. View Reports
6. Check Expiry & Low Stock Alerts
7. Sort Medicines by Price
8. Restock Medicine
9. View Customer Loyalty Ranking
10. Logout

### Pharmacist Login

**Login Credentials:**
- **Pharmacist ID:** `2307090`
- **Password:** `Ritovash Chanda`

**Pharmacist Menu Options:**
1. Sell Medicine
2. Search Medicine
3. View Inventory
4. Check Expiry
5. Logout

### Selling Medicine (Pharmacist)

1. Choose whether the customer is existing or new
2. For existing customers, enter phone number
3. For new customers, provide name and phone number
4. Enter Medicine ID to sell
5. Specify quantity
6. System automatically:
   - Checks expiry dates
   - Validates stock availability
   - Applies loyalty discounts
   - Generates and prints invoice
   - Updates inventory

## 🏗️ Project Structure

### Class Hierarchy

```
User (Base Class)
├── Admin (Derived)
└── Pharmacist (Derived)

Medicine (Standalone)
Customer (Standalone)
Invoice (Standalone)
PharmacySystem (Main Controller)
```

### Core Classes

#### 1. **Medicine Class**
- Attributes: ID, name, company, price, quantity, expiry date
- Methods: stock management, expiry checking, serialization
- Operator Overloading: `<`, `>`, `+`, `==`

#### 2. **Customer Class**
- Attributes: ID, name, phone, purchase count
- Methods: discount calculation, loyalty tracking
- Operator Overloading: `++`, `<`

#### 3. **Invoice Class**
- Attributes: invoice ID, customer name, date, items, amounts
- Methods: bill generation, discount application, file saving

#### 4. **User Class (Base)**
- Attributes: ID, name, contact, login status
- Methods: login, logout

#### 5. **Admin Class (Inherited from User)**
- Full inventory management capabilities
- Reporting and analytics features
- Customer loyalty management

#### 6. **Pharmacist Class (Inherited from User)**
- Sales processing
- Inventory viewing
- Medicine searching

#### 7. **PharmacySystem Class**
- Main controller class
- Manages all user interactions
- Handles file operations
- Coordinates between all components

## 📁 File Storage

The system uses text files for persistent data storage:

### Files Created

1. **medicines.txt**
   - Stores medicine inventory
   - Format: `ID,Name,Company,Price,Quantity,ExpiryDate`
   - Updated after: add, remove, update, restock, sell operations

2. **customers.txt**
   - Stores customer information
   - Format: `ID,Name,Phone,PurchaseCount`
   - Updated after: new customer registration, purchases

3. **invoices.txt**
   - Stores all sales invoices
   - Format: `InvoiceID,CustomerName,Date,TotalAmount,DiscountAmount,FinalAmount`
   - Appended after each sale

4. **invoice_counter.txt**
   - Tracks the next invoice number
   - Ensures sequential invoice numbering

### Data Persistence

- All data is automatically saved to files
- Data is loaded when the system starts
- CSV-style serialization for easy parsing

## 🔑 Login Credentials

### Admin Access
```
ID: 23070
Password: CSE_23
```

### Pharmacist Access
```
ID: 2307090
Password: Ritovash Chanda
```

## 👥 Contributors

This project was collaboratively developed by:

| Name | Roll Number |
|------|-------------|
| Krishno Mondol | 2307085 |
| Atif Absar | 2307087 |
| Agomon Das Dhrubo | 2307088 |
| Rehenuma Rashid Lameya | 2307089 |
| Ritovash Chanda | 2307090 |
| Arnob Dam | 2307091 |

## 🎓 Academic Information

- **Institution:** Khulna University of Engineering & Technology
- **Program:** Computer Science and Engineering
- **Course:** Object-Oriented Programming (CSE 1205)
- **Year:** 1st Year, 2nd Semester
- **Academic Year:** 2025

## 🛠️ Key Programming Concepts Used

- **Object-Oriented Programming (OOP)**
  - Classes and Objects
  - Inheritance (User → Admin, Pharmacist)
  - Encapsulation
  - Polymorphism
  
- **Operator Overloading**
  - Comparison operators (`<`, `>`, `==`)
  - Arithmetic operators (`+`)
  - Increment operator (`++`)
  
- **File Handling**
  - Reading from files (`ifstream`)
  - Writing to files (`ofstream`)
  - Data serialization/deserialization
  
- **STL (Standard Template Library)**
  - Vectors for dynamic arrays
  - Algorithms (sort, remove_if)
  - String streams for parsing
  
- **Date and Time Manipulation**
  - Current date extraction
  - Date comparison for expiry checking

## 🔍 Special Features

### 1. Automatic Expiry Detection
- Compares current date with medicine expiry dates
- Prevents sale of expired medicines
- Generates expiry alerts

### 2. Low Stock Alerts
- Identifies medicines with quantity < 10
- Helps in timely restocking

### 3. Customer Loyalty Program
- Automatic discount calculation
- Progressive discount tiers (5% and 10%)
- Purchase history tracking

### 4. Invoice Generation
- Professional formatted invoices
- Automatic calculations
- Discount application
- Persistent storage

### 5. Data Validation
- Checks for duplicate medicine IDs
- Validates stock availability
- Ensures data integrity

## 📊 Sample Output Examples

### Invoice Sample
```
╔════════════════════════════════════════════════════════════╗
║              PHARMACY MANAGEMENT SYSTEM                    ║
║                    INVOICE                                 ║
╚════════════════════════════════════════════════════════════╝

Invoice ID: 1001
Date: 11/11/2025
Customer: John Doe

------------------------------------------------------------
Medicine            Price     Quantity   Subtotal
------------------------------------------------------------
Paracetamol         5.50      2          11.00
Aspirin             3.25      3          9.75
------------------------------------------------------------
                                Total: $20.75
                                Discount: -$1.04
                                Final Amount: $19.71
============================================================

      Thank you for your purchase!
============================================================
```

## 🐛 Known Limitations

- Console-based interface (no GUI)
- Simple authentication (brute force checking)
- Single admin and pharmacist account
- Date format must be DD/MM/YYYY

## 🔮 Future Enhancements

- GUI implementation using Qt or similar framework
- Database integration (MySQL/PostgreSQL)
- Enhanced security with password hashing
- Multi-user support
- Barcode scanning integration
- Advanced reporting with charts
- Email invoice functionality
- Backup and restore features

## 📝 License

This project is developed for academic purposes. All rights reserved by the contributors.

## 🤝 Acknowledgments

We would like to thank our course instructor and the Computer Science and Engineering department for their guidance and support throughout this project.

---

**For queries or suggestions, please contact any of the contributors listed above.**