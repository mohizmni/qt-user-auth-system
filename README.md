# Qt Desktop User Authentication System

A native C++ desktop GUI application for user Registration and Authentication built with **Qt Widgets**. The system features client-side password hashing, custom input validators, dynamic multi-window navigation, and CSV-style file persistence.

---

## Key Features

- **Secure Registration:** Hashes user credentials on the client side using **SHA-256** (`QCryptographicHash`) before writing to storage.
- **Input Validation & Security:**
  - Password fields protected using `QLineEdit::Password` echo mode.
  - Integer validation (`QIntValidator`) enforced for age inputs.
- **Authentication Engine:** Read/parse authentication records line-by-line from storage to verify user credentials safely.
- **Multi-Window GUI:** Event-driven window creation using Qt's **Signals & Slots** architecture.

---

## Technical Stack

* **Language:** C++ (C++11 or higher)
* **GUI Framework:** Qt Framework (`QMainWindow`, `QVBoxLayout`, `QMessageBox`, `QComboBox`)
* **Security & Storage:** `QCryptographicHash`, `QFile`, `QTextStream`
* **Build System:** `qmake` (`signinLogin.pro`)

---

## How to Build & Run

### Using Qt Creator
1. Launch **Qt Creator**.
2. Open `signinLogin.pro`.
3. Select your installed Kit and press **`Ctrl + R`** (or click **Run**) to build and execute.
