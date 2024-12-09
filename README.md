# Brainfuck-ish interpreter

Not exactly brainfuck, but more my vision on it. Not really optimized, just a funny hello-world project of mine to try out C.

https://brainfuck.org/

## Documentation
(mainly identical to brainfuck)

| Operation | Description |
|-----------|----------------|
| `<` | Shift pointer to the left |
| `>` | Shift pointer to the right |
| `+` | Increment value in the current cell |
| `-` | Decrement value in the current cell |
| `.` | Output value in the current cell |
| `,` | Input value to the current cell |
| `[` | Go to the next instruction if value in the current cell is not 0, otherwise exit the loop (jump to end) |
| `]` | Go to the next instruction if value in the current cell is 0, otherwise continue the loop (jump to start) |
| `~` | (only as the first character) Shift all input and output values by +32, so that printable characters start at 0  |
| `"` | Start/end commentary section |

other characters are skipped

Interpreter first tries to verify code to disallow running it if it has bad braces hierarchy or it had issues opening file. If so, it will print out error message and show the source code as it read it.