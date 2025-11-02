#  Qt Cash Register (Point of Sale Demo)

This project is a simple cash register simulator built using Qt Widgets (C++).  
It reads product data from a JSON file, calculates totals, and processes payments using a numeric on-screen calculator.

---

## Description

The application simulates a small point-of-sale interface:

- Reads a list of products from a JSON file.
- Displays the total bill amount.
- Accepts payment input from a numeric keypad or keyboard.
- Calculates and displays change.
- Uses color highlighting and button locking to guide the cashier.

---

## Installation and Dependencies

### Requirements
- Qt 6.0.0 or newer
- C++11 or later
- qmake or CMake build system

### Build with qmake
```bash
git clone https://github.com/YourUsername/QtCashRegister.git
cd QtCashRegister
qmake
make
./QtCashRegister
```

### Build with CMake
```bash
cmake -B build .
cmake --build build
./build/QtCashRegister
```

---

## Input Data (JSON file)

The program expects a file named `data.json`.  
Place it in the same directory as the application executable, or next to `main.cpp` when running from Qt Creator.

### Example content:
```json
[
  { "name": "Помада матова", "quantity": 2, "price": 199.50, "total": 399.00 },
  { "name": "Шампунь", "quantity": 1, "price": 150.00, "total": 150.00 },
  { "name": "Крем для рук", "quantity": 3, "price": 85.00, "total": 255.00 },
  { "name": "Парфуми", "quantity": 1, "price": 1200.00, "total": 1200.00 },
  { "name": "Маска для волосся", "quantity": 2, "price": 180.00, "total": 360.00 }
]
```

The program automatically calculates the total amount from the `total` fields and displays it in the Bill Amount field.

---

## Interface Overview

### Main Fields
| Field | Description |
|--------|-------------|
| Bill Amount | The total amount of all items (read-only). |
| Cash | A duplicate of the bill amount (read-only). |
| Customer Amount | Value entered manually or via calculator; accepts only numbers with up to two decimal places. |
| Change | The calculated difference between the customer payment and bill amount. |

---

## Buttons

| Button | Function |
|---------|-----------|
| Pay (Оплатити) | Enabled only when the payment is sufficient. Displays a message confirming the payment and showing the change. |
| Cancel (Відмова) | Clears all input fields and resets the calculator. |
| Calculator | Allows entering numeric values; the “.” button is used for decimals. |

---

## Error Checking, Highlighting, and Locking

- Input validation prevents any non-numeric values or more than two digits after the decimal point.
- Color feedback:
  - Green: payment is greater than the bill (positive change).
  - Red: payment is less than the bill (insufficient funds).
  - No color: empty or exact payment.
- The Pay button is automatically disabled when the payment is insufficient or the field is empty.

---

## Project Structure

```
QtCashRegister/
├── main.cpp
├── calculator.h
├── calculator.cpp
├── widget.h
├── widget.cpp
├── data.json
├── QtCashRegister.pro
└── README.md
```

---
