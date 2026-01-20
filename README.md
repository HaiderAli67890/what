# What

A lightweight C library for sending WhatsApp messages programmatically. This library automates opening WhatsApp Web and sending messages to specified phone numbers.

## ⚠️ Important Notes

- **Use at your own risk!** This library opens WhatsApp Web and automates user interactions.
- Requires WhatsApp Web to be accessible in your default web browser.
- Requires you to be logged into WhatsApp Web.
- Platform support: Windows, macOS, and Linux.

## Installation

### Prerequisites

- C compiler (GCC, Clang, or MSVC)
- CMake 3.16 or higher
- WhatsApp Web accessible via your default browser

## API Reference

### `what_message()`

Sends a message via WhatsApp to the specified phone number.

```c
int what_message(const char *number, const char *message);
```

**Parameters:**
- `number` (const char*) - International phone number of the recipient (with country code, e.g., "+27123456789")
- `message` (const char*) - The message text to send

**Returns:**
- `0` on success
- `-1` on error (typically buffer overflow during URL encoding)

**Example:**
```c
#include <what.h>

int main()
{
    what_message("+27123456789", "Hello, World!");
    return 0;
}
```

## Usage Example

```c
#include <what.h>
#include <stdio.h>

int main()
{
    // Send a simple message
    int result = what_message("+1234567890", "Hi there!");
    
    if (result != 0) {
        printf("Failed to send message\n");
        return 1;
    }
    
    printf("Message sent successfully\n");
    return 0;
}
```

## How It Works

1. URL-encodes the phone number and message text
2. Constructs a WhatsApp Web URL with the encoded parameters
3. Opens the URL in your default browser
4. On Windows: Automatically presses Enter to send (after a 5-second delay)
5. On macOS and Linux: Uses system commands to open the URL

## Limitations

- Message length is limited to 256 characters (can be modified in source)
- Phone number must be within 64 characters when encoded
- Total URL must not exceed 512 characters
- Requires manual interaction on non-Windows platforms
- No built-in error handling for network issues or WhatsApp Web unavailability

## Platform Support

| Platform | Status | Notes |
|----------|--------|-------|
| Windows  | ✅ Supported | Automatic message sending via keyboard input |
| macOS    | 🔃 Incomplete | Uses `open` command |
| Linux    | 🔃 Incomplete | Uses `xdg-open` command |

## License

Use at your own risk. See project files for additional licensing information.
