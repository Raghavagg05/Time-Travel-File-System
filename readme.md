# Time-Travel File System (COL106 Long Assignment 1)

## Introduction
This project implements a simplified, in-memory version control system inspired by Git.  
It manages versioned files and has functionalities like snapshots, rollbacks, and system-wide analytics, built using **Trees, HashMaps, and Heaps**.

---

## Compilation & Execution

### On Linux / Mac
```bash
g++ -std=c++17 main.cpp -o file_system
./file_system
```

### On Windows (PowerShell / CMD)
```powershell
g++ -std=c++17 main.cpp -o file_system.exe
.ile_system.exe
```

### Using provided script (Linux/Mac)
```bash
chmod +x run.sh
./run.sh
```
---

## Usage
On running the program, the program allows you to enter commands interactively, or redirect from a file.  

---

## Supported Commands
Following is the list of commands which the program allows:
### 1. File Operations
- **CREATE `<filename>`**  - Creates a new file with version 0 (initial snapshot).  

- **READ `<filename>`**  - Prints the content of the asked file's  active version.  

- **INSERT `<filename>` `<content>`**  - If the active version of the file is a snapshot, creates a new version with the given content. If not snapshoted, adds the given content to the active version.  

- **UPDATE `<filename>` `<content>`** - Replaces the entire content of the active version with the given content if it is not snapshoted. Otherwise creates a new version with the given content.  

- **SNAPSHOT `<filename>` `<message>`** - Marks the active version as a snapshot with the given message. Content of the active version now becomes immutable.  

- **ROLLBACK `<filename>` `[versionID]`**- if version_id is given sets active version to that version otherwise rolls back to the parent of the active version. 

- **HISTORY `<filename>`** - Prints all snapshots for the file in reverse chronological order.  

### 2. System-Wide Analytics
- **RECENT_FILES** - Shows the most recently modified `n` files.  

- **BIGGEST_TREES** - Shows the files with the largest number of versions (top `n`).  

### 3. Exit Program
- **EXIT** - Ends the program.  

## Error handling
### File Management errors
- **Duplicate file handling** - CREATE throws error if file with given name already exists.
- **Non-existing file handling** - All file operations (READ, INSERT, UPDATE, SNAPSHOT, ROLLBACK, HISTORY) throw error("no such file exists!") when performed on files that don't exist.

### Version control errors
- **Double Snapshot handling** - SNAPSHOT throws error in case given version is already marked as snapshot.
- **Invalid version rollback** - ROLLBACK throws error if the given version_id is negative or greater than or equal to the total_versions.
- **Parent rollback error handling** - ROLLBACK throws error if no version given and the active version's parent does not exist. 

### Invalid argumemts in system wide analytics
- RECENT_FILES throws error if number given by user is greater than number of files present.
- BIGGEST_TREES throws error if number given by user is greater than number of files present.
---
