# get_next_line

> A robust implementation of a line-by-line file reader in C — designed to handle any file descriptor efficiently, one line at a time.

---

## 📚 Project Overview

`get_next_line` is a core project in the 42 coding curriculum that challenges you to create a function which reads a file (or input stream) **one line at a time** — regardless of line length, buffer size, or file descriptor complexity.

The function prototype is:

```c
char *get_next_line(int fd);
```

It must return:
- A **line** from the given file descriptor
- `NULL` when EOF is reached or in case of an error

It must **not leak memory**, handle **multiple file descriptors simultaneously**, and **efficiently manage buffer reads** — especially when using a very small `BUFFER_SIZE`.

---

## ✅ Key Features

- 📦 Reads from any file descriptor (`stdin`, regular files, pipes…)
- 🧠 Internal static buffer to manage leftover data
- 🪓 Handles lines of any length — regardless of `BUFFER_SIZE`
- 🧵 Supports **multiple simultaneous fds**
- 🧼 100% memory leak–free (validated with Valgrind)
- 🧪 Tested with edge cases: empty files, no newline, long lines, multiple newlines, etc.

---

## 🔧 Files

| File | Purpose |
|------|---------|
| `get_next_line.c` | Core logic of the function |
| `get_next_line_utils.c` | Utility functions for string manipulation and memory handling |
| `get_next_line.h` | Header with prototypes and definitions |
| `main.c` *(optional)* | Simple test file for demonstration |
| `Makefile` | Standardized build and clean commands |

---

## 🧪 Usage

### 1. Clone the repo

```bash
git clone https://github.com/HoferJPaul/get_next_line.git
cd get_next_line
```

### 2. Build

```bash
make
```

### 3. Example test

```c
int main(void)
{
    int fd = open("file.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)))
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return 0;
}
```

Compile and run:

```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=32 get_next_line.c get_next_line_utils.c main.c -o gnl
./gnl
```

---

## 📁 BUFFER_SIZE Notes

You can test with different buffer sizes by adding:

```bash
-D BUFFER_SIZE=1     # extreme case
-D BUFFER_SIZE=42    # 42-friendly case
-D BUFFER_SIZE=10000 # large buffer
```

Changing `BUFFER_SIZE` simulates low-level constraints like system buffers or socket reads.

---

## 🧠 How It Works (Simplified)

1. Read chunks of data into a buffer
2. Append each chunk to a static string until a newline is found
3. Return the line (up to and including the newline)
4. Store any leftover data for the next call
5. Repeat until EOF or error

---

## ⚠️ Constraints (per 42 specs)

- No `malloc()` leaks allowed
- No global variables
- Only allowed functions: `read`, `free`, `malloc`, `NULL`, basic string functions
- Must compile with any `BUFFER_SIZE > 0`
