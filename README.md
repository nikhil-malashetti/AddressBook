# 📘 Address Book Management System  

A **menu-driven C application** for managing and organizing contact information efficiently.  
This project demonstrates **structured programming concepts**, **modular design**, and **persistent data handling** using file I/O.  

---

## 🧠 Language | 💻 Platform | 📈 Status
**Language:** C Programming  
**Platform:** GCC / Linux Terminal  
**Status:** ✅ Working and Tested  

---

## 🚀 Features  

✅ **Create Contact** — Add new contacts with validation to ensure unique phone numbers and email addresses.  
🔍 **Search Contact** — Search by name, phone number, or email with case-insensitive and partial match support.  
✏ **Edit & Delete** — Modify or safely remove existing contact entries.  
📋 **List All Contacts** — Display all saved contacts in a structured table view.  
💾 **Persistent Storage** — Automatically saves all contact data to `contacts.csv` and loads it at startup.  
🧩 **Input Validation** — Validates email format and mobile number before saving.  

---

## 🛠 How to Compile and Run  

### 1️⃣ Open Terminal  
Navigate to the project directory containing all `.c` and `.h` files.  

### 2️⃣ Compile the Program  
```bash
gcc '*.c'
```  

### 3️⃣ Run the Executable  
```bash
./addressbook
```  

Once launched, the program menu will guide you through all available operations.   

---

## 📂 Project Structure  

| File Name | Description |
|------------|-------------|
| **main.c** | Contains the main menu loop and program control flow |
| **contact.c / contact.h** | Defines structures and core functions for creating, searching, editing, and deleting contacts |
| **file.c / file.h** | Handles file operations for saving/loading contact data from `contacts.csv` |
| **populate.c / populate.h** | Provides sample contacts for initial testing |
| **contacts.csv** | Stores all contact data persistently |
| **README.md** | Project documentation file |

---

## 🧱 Example Usage  

```  Address Book Menu:

1. Create Contact
2. Search Contact
3. Edit Contact
4. Delete Contact
5. List All Contacts
6. Save Contacts
7. Exit
Enter your choice: _
```

---

## 🧩 Concepts Demonstrated  

- Modular Programming in C  
- File Handling (`fopen`, `fprintf`, `fscanf`, etc.)  
- Data Management using Structures  
- String Manipulation and Validation  
- Menu-driven User Interface  
- Persistent Data Storage  

---

## 🔮 Future Enhancements  

- Contact grouping (Friends, Family, Work)  
- Add backup and restore functionality  
- JSON or Binary File support  
- Import/Export contacts feature  
- Graphical UI using GTK or Qt  

---

## 👨‍💻 Author  

**Nikhil Malashetti**  
📍 Belagavi, Karnataka, India  

⭐ **If you like this project, consider giving it a star on GitHub!**