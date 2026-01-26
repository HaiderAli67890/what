/**
 * @file what.h
 * @brief WhatsApp messaging library for C
 *
 * A lightweight library that automates sending WhatsApp messages by opening
 * WhatsApp Web in the default browser and simulating user interactions.
 *
 * @warning This library should be used responsibly and only for legitimate purposes.
 *          Use at your own risk!
 *
 * Platform Support:
 * - Windows: Automatic message sending via keyboard input
 * - macOS: Uses `open` command to launch URLs
 * - Linux: Uses `xdg-open` command to launch URLs
 */

#ifndef WHAT_H
#define WHAT_H

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

#ifdef _WIN32
#include <Windows.h>
#endif

/**
 * @brief URL-encodes a string for safe transmission in HTTP requests
 *
 * Encodes special characters in a string using percent-encoding (RFC 3986).
 * Alphanumeric characters and the symbols '-', '_', '.', '~' are left unchanged.
 * All other characters are encoded as %XX where XX is the hexadecimal ASCII value.
 *
 * @param dest Destination buffer for the encoded string
 * @param dest_size Size of the destination buffer
 * @param src Source string to encode
 *
 * @return 0 on success, -1 if the destination buffer is too small for the encoded result
 *
 * @note This is an internal function (prefix '__') and should not be called directly
 *       by application code.
 */
int __encode_url(char *dest, size_t dest_size, const char *src);

/**
 * @brief Sends a WhatsApp message to the specified phone number
 *
 * Opens WhatsApp Web in the default browser, navigates to a chat with the given
 * phone number, and sends the specified message. On Windows, the message is sent
 * automatically. On macOS and Linux, the user must manually send after the URL opens.
 *
 * Prerequisites:
 * - WhatsApp Web must be accessible via the default browser
 * - User must be logged into WhatsApp Web
 * - On Windows: No additional user interaction needed after calling this function
 * - On macOS/Linux: Browser window will open; user must press Enter or click Send
 *
 * @param number International phone number with country code (e.g., "+27123456789")
 * @param message The message text to send (max 256 characters)
 *
 * @return 0 on success, -1 on error (e.g. buffer overflow during encoding, or memory allocation failure)
 *
 * @note The function blocks for 5 seconds on Windows to allow the page to load
 *       before sending input. Works most reliably if your browser is already open.
 *
 * Example:
 * @code
 * int result = what_message("+27123456789", "Hello, World!");
 * if (result != 0) {
 *     printf("Failed to send message\n");
 * }
 * @endcode
 */
int what_message(const char *number, const char *message);

#endif
