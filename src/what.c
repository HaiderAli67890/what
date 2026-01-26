#include <string.h>
#include "what.h"

int __encode_url(char *dest, size_t dest_size, const char *src)
{
    size_t di = 0;

    for (size_t si = 0; src[si] != '\0'; si++)
    {
        unsigned char c = (unsigned char)src[si];

        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~')
        {
            if (di + 1 >= dest_size)
                return -1;
            dest[di++] = c;
        }
        else
        {
            if (di + 3 >= dest_size)
                return -1;
            snprintf(&dest[di], 4, "%%%02X", c);
            di += 3;
        }
    }

    if (di >= dest_size)
        return -1;
    dest[di] = '\0';
    return 0;
}

int what_message(const char *number, const char *message)
{
    size_t messageLength = strlen(message) * 3 + 1;
    size_t numberLength = strlen(number) * 3 + 1;

    char *encodedMessage = malloc(messageLength);
    char *encodedNumber = malloc(numberLength);
    char url[1024];

    if (!encodedMessage || !encodedNumber)
    {
        free(encodedMessage);
        free(encodedNumber);
        return -1;
    }

    if (__encode_url(encodedMessage, messageLength, message) != 0 ||
        __encode_url(encodedNumber, numberLength, number) != 0)
    {
        free(encodedMessage);
        free(encodedNumber);
        return -1;
    }

    snprintf(
        url,
        sizeof(url),
        "https://web.whatsapp.com/send/?phone=%s&text=%s&type=phone_number&app_absent=0",
        encodedNumber,
        encodedMessage);

    free(encodedMessage);
    free(encodedNumber);

#ifdef _WIN32
    ShellExecuteA(NULL, "open", url, NULL, NULL, SW_SHOWNORMAL);
    Sleep(5000);

    INPUT inputs[2] = {0};
    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = VK_RETURN;

    inputs[1] = inputs[0];
    inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

    SendInput(2, inputs, sizeof(INPUT));

#elif __APPLE__
    char command[1100];
    snprintf(command, sizeof(command), "open \"%s\"", url);
    system(command);
#elif __linux__
    char command[1100];
    snprintf(command, sizeof(command), "xdg-open \"%s\"", url);
    system(command);
#endif

    return 0;
}
