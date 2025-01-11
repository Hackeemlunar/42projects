#include "libft.h"
#include "ft_printf.h"

int ft_printf(const char *format, ...)
{
    va_list args;
    char*   fstring[256];
    int     count;
    int     i;
    int     j;

    count = 0;
    i = 0;
    j = 0;
    va_start(args, format);
    while (format[i] != '\0')
    {
        if (format[i] == '%')
        {
            fstring[j] = process_specifiers(&format[i], va_arg(args, void*));
        }
        
    }
    va_end(args);
    return (count);
}

char* process_specifiers(const char* format, void* arg)
{
    
    
}

/*
**1. Initialization:**

*   **Start:** Begin processing the format string character by character.
*   **Initialize:** 
    *   `count` to 0 (to keep track of the number of characters printed).
    *   `flags` to 0 (to store flags like '-', '+', '0', '#', ' ').
    *   `width` to 0 (for field width).
    *   `precision` to -1 (to indicate no precision specified).
    *   `length_modifier` to 0 (to store length modifiers like 'h', 'l', 'll').

**2. Process Format String:**

*   **Iterate:** Loop through each character in the format string.
*   **Literal Characters:** If the current character is not '%':
    *   Print the character to the output.
    *   Increment `count` by 1.
    *   Continue to the next character.

*   **Format Specifier:** If the current character is '%':
    *   **Parse Flags:** 
        *   Check for and process flags like '-', '+', '0', '#', ' ' (e.g., left/right justification, sign handling, padding).
        *   Update the `flags` variable accordingly.
    *   **Parse Width:** 
        *   If a number follows the flags, extract it as the field width.
        *   Update the `width` variable.
    *   **Parse Precision:**
        *   If a '.' follows the width, extract the precision value.
        *   Update the `precision` variable.
    *   **Parse Length Modifier:**
        *   Check for length modifiers like 'h', 'l', 'll', 'L'.
        *   Update the `length_modifier` variable.
    *   **Determine Data Type:** 
        *   Based on the character after the potential length modifier (e.g., 'd', 'c', 's', 'f', 'x'), determine the data type to be printed (integer, character, string, float, hexadecimal, etc.).
    *   **Retrieve Argument:** 
        *   Use `va_arg` to retrieve the corresponding argument from the variable argument list based on the data type.
    *   **Format and Print:** 
        *   Format the argument according to the flags, width, precision, and length modifier.
        *   Print the formatted output to the console using `write`.
        *   Update `count` with the number of characters printed.

**3. Handle Data Types:**

*   **Integer:** 
    *   Convert the integer to a string (e.g., using a custom integer-to-string conversion function).
    *   Handle negative numbers, sign placement, and padding based on flags and width.
    *   Print the formatted integer string.
*   **Character:** 
    *   Print the character directly.
*   **String:** 
    *   Print the string, handling truncation if necessary based on precision.
    *   Apply width and justification as specified by flags.
*   **Floating-Point:** 
    *   Convert the floating-point number to a string (e.g., using `sprintf` or a custom implementation).
    *   Handle precision, scientific notation, and other floating-point formatting options.
*   **Other Data Types:** 
    *   Handle other data types like pointers, custom data structures, etc., as needed.

**4. Error Handling:**

*   **Invalid Format Specifiers:** 
    *   If an invalid format specifier is encountered (e.g., '%z'), print an error message or handle the situation appropriately.
*   **Argument Mismatch:** 
    *   If the number of arguments does not match the number of format specifiers, handle the error gracefully.
*   **Buffer Overflows:** 
    *   Implement checks to prevent buffer overflows during string formatting and printing.

**5. Cleanup:**

*   Call `va_end(args)` to clean up the variable argument list.
*   Return the total number of characters printed (`count`).

This algorithm provides a more comprehensive and robust approach to implementing a `printf`-like function, addressing the key aspects of flag parsing, data type handling, and error handling.

*/