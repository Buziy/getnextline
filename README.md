*This project has been created as part of the 42 curriculum by busyigit.*

# get_next_line

## Description

**get_next_line** strips file reading down to its simplest contract: call the function, get a line. Behind that simplicity lies a carefully managed pipeline — a file descriptor feeding a fixed-size buffer, a buffer feeding a static accumulator, and that accumulator yielding exactly one line per call before preserving the remainder for the next invocation.

The function returns each line with its trailing newline character (`\n`) intact. The one exception is the final line of a file that ends without a newline — it comes back exactly as written. Once the file is exhausted or something goes wrong, the function returns `NULL` and steps aside.

**Goal:** Implement `get_next_line()` in C, a function that reads and returns one line at a time from any file descriptor, handling memory correctly and behaving predictably across all edge cases.

**Bonus:** Handle multiple file descriptors simultaneously using a single static variable.

---

## Algorithm — Design & Justification

### The Static Buffer Accumulator Pattern

The core challenge of `get_next_line` is that a single `read()` syscall rarely aligns with line boundaries. A buffer of `BUFFER_SIZE` bytes may land mid-line, span multiple lines, or end exactly at a `\n`. The function must bridge this mismatch between raw reads and logical lines.

The chosen approach uses a **static string accumulator per file descriptor**:

1. **Read in chunks** — `read()` fills a temporary heap buffer of `BUFFER_SIZE` bytes on each call.
2. **Accumulate** — the chunk is appended to a static string (`stash`) that persists between calls.
3. **Search for `\n`** — once the stash contains a newline (or EOF is reached), extract everything up to and including `\n` as the return value.
4. **Preserve the remainder** — everything after the `\n` is saved back into the stash for the next call.
5. **Clean up on EOF** — when `read()` returns 0 and no newline is found, return whatever remains in the stash, then free it.

**Why this approach over alternatives:**

| Approach | Problem |
|---|---|
| Re-reading from offset 0 each call | Inefficient; requires `lseek`, breaks pipes and stdin |
| Single large static array | Fixed max-line length; undefined behavior on overflow |
| Recursive reads without stash | Stack growth proportional to file size |
| **Static accumulator (chosen)** | O(1) memory overhead per extra char; works on any fd |

The static accumulator is the only design that satisfies all constraints simultaneously: no seek dependency, no fixed line-length cap, and correct behavior on pipes, standard input, and regular files.

### Bonus: Multiple File Descriptors

For the bonus, the static variable becomes an array indexed by file descriptor (`stash[OPEN_MAX]`), allowing independent accumulators per fd. This makes concurrent reads across different files fully isolated without any additional bookkeeping structure.

---

## Instructions

### Files

| File | Role |
|---|---|
| `get_next_line.c` | Core logic — read loop, stash management, line extraction |
| `get_next_line_utils.c` | Helper functions (ft_strlen, ft_strjoin, ft_strchr, etc.) |
| `get_next_line.h` | Header — prototype and BUFFER_SIZE macro |
| `get_next_line_bonus.c` | Bonus — multi-fd version |
| `get_next_line_utils_bonus.c` | Bonus helpers |
| `get_next_line_bonus.h` | Bonus header |

### Compilation

The `BUFFER_SIZE` used by `read()` is defined at compile time. You can override it with the `-D` flag:

```bash
# Default buffer size (defined in header)
cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c -o gnl

# Custom buffer size
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -o gnl

# Bonus (multiple file descriptors)
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c -o gnl_bonus
```

### Usage

`get_next_line` is a library function, not a standalone program. To use it in your own code:

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd;
    char    *line;

    fd = open("file.txt", O_RDONLY);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

Compile together with the gnl source files:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=32 main.c get_next_line.c get_next_line_utils.c
./a.out
```

### Edge Cases to Test

- Empty file
- File with no trailing newline on the last line
- Single character per line
- `BUFFER_SIZE` of 1, 2, 10000
- Reading from `stdin` (fd = 0)
- Invalid file descriptor
- Bonus: alternating reads between two open file descriptors

---

## Resources

### Documentation & References

- [read(2) — Linux man page](https://man7.org/linux/man-pages/man2/read.2.html) — the syscall at the heart of the implementation
- [open(2) — Linux man page](https://man7.org/linux/man-pages/man2/open.2.html) — file descriptor management
- [malloc / free — cppreference](https://en.cppreference.com/w/c/memory/malloc) — dynamic memory allocation
- [Static variables in C — GeeksforGeeks](https://www.geeksforgeeks.org/static-variables-in-c/) — persistence across function calls explained
- *The C Programming Language* — Kernighan & Ritchie, Chapter 7 (I/O)

### AI Usage

AI (Claude, Anthropic) was used during this project for the following tasks:

- **README drafting** — generating and refining the structure and wording of this document
- **Edge case brainstorming** — prompting for a comprehensive list of edge cases to test against
- **Algorithm explanation** — clarifying how the static accumulator pattern compares to alternatives

AI was **not** used to write, debug, or review any `.c` or `.h` source files. All implementation decisions and code were produced independently.

