import os

# List of functions categorized by section
functions = {
    "Part 1 - Libc functions": [
        ("int ft_isalpha(int c);", "ft_isalpha.c"),
        ("int ft_isdigit(int c);", "ft_isdigit.c"),
        ("int ft_isalnum(int c);", "ft_isalnum.c"),
        ("int ft_isascii(int c);", "ft_isascii.c"),
        ("int ft_isprint(int c);", "ft_isprint.c"),
        ("size_t ft_strlen(const char *s);", "ft_strlen.c"),
        ("void *ft_memset(void *b, int c, size_t len);", "ft_memset.c"),
        ("void ft_bzero(void *s, size_t n);", "ft_bzero.c"),
        ("void *ft_memcpy(void *dst, const void *src, size_t n);", "ft_memcpy.c"),
        ("void *ft_memmove(void *dst, const void *src, size_t len);", "ft_memmove.c"),
        ("size_t ft_strlcpy(char *dst, const char *src, size_t dstsize);", "ft_strlcpy.c"),
        ("size_t ft_strlcat(char *dst, const char *src, size_t dstsize);", "ft_strlcat.c"),
        ("int ft_toupper(int c);", "ft_toupper.c"),
        ("int ft_tolower(int c);", "ft_tolower.c"),
        ("char *ft_strchr(const char *s, int c);", "ft_strchr.c"),
        ("char *ft_strrchr(const char *s, int c);", "ft_strrchr.c"),
        ("int ft_strncmp(const char *s1, const char *s2, size_t n);", "ft_strncmp.c"),
        ("void *ft_memchr(const void *s, int c, size_t n);", "ft_memchr.c"),
        ("int ft_memcmp(const void *s1, const void *s2, size_t n);", "ft_memcmp.c"),
        ("char *ft_strnstr(const char *haystack, const char *needle, size_t len);", "ft_strnstr.c"),
        ("int ft_atoi(const char *str);", "ft_atoi.c"),
        ("void *ft_calloc(size_t count, size_t size);", "ft_calloc.c"),
        ("char *ft_strdup(const char *s1);", "ft_strdup.c")
    ],
    "Part 2 - Additional functions": [
        ("char *ft_substr(char const *s, unsigned int start, size_t len);", "ft_substr.c"),
        ("char *ft_strjoin(char const *s1, char const *s2);", "ft_strjoin.c"),
        ("char *ft_strtrim(char const *s1, char const *set);", "ft_strtrim.c"),
        ("char **ft_split(char const *s, char c);", "ft_split.c"),
        ("char *ft_itoa(int n);", "ft_itoa.c"),
        ("char *ft_strmapi(char const *s, char (*f)(unsigned int, char));", "ft_strmapi.c"),
        ("void ft_striteri(char *s, void (*f)(unsigned int, char *));", "ft_striteri.c"),
        ("void ft_putchar_fd(char c, int fd);", "ft_putchar_fd.c"),
        ("void ft_putstr_fd(char *s, int fd);", "ft_putstr_fd.c"),
        ("void ft_putendl_fd(char *s, int fd);", "ft_putendl_fd.c"),
        ("void ft_putnbr_fd(int n, int fd);", "ft_putnbr_fd.c")
    ],
    "Bonus part (linked list functions)": [
        ("t_list *ft_lstnew(void *content);", "ft_lstnew.c"),
        ("void ft_lstadd_front(t_list **lst, t_list *new);", "ft_lstadd_front.c"),
        ("int ft_lstsize(t_list *lst);", "ft_lstsize.c"),
        ("t_list *ft_lstlast(t_list *lst);", "ft_lstlast.c"),
        ("void ft_lstadd_back(t_list **lst, t_list *new);", "ft_lstadd_back.c"),
        ("void ft_lstdelone(t_list *lst, void (*del)(void *));", "ft_lstdelone.c"),
        ("void ft_lstclear(t_list **lst, void (*del)(void *));", "ft_lstclear.c"),
        ("void ft_lstiter(t_list *lst, void (*f)(void *));", "ft_lstiter.c"),
        ("t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));", "ft_lstmap.c")
    ]
}

# Template for the C file content
file_template = '''#include <stdio.h>
#include <stdlib.h>
#include <string.h>

%s

int main(void)
{
    // Example test for %s
    return 0;
}
'''

# Function to generate C file for each function
def generate_c_file(function_signature, filename):
    # Extract function name (e.g., ft_isalpha)
    func_name = function_signature.split()[1].split('(')[0]
    
    # Create the function's .c file
    content = file_template % (function_signature, func_name)
    
    # Write content to the C file
    with open(filename, 'w') as file:
        file.write(content)
    print(f"Generated: {filename}")

# Function to generate all C files based on the functions list
def generate_all_c_files():
    for category, funcs in functions.items():
        for signature, filename in funcs:
            generate_c_file(signature, filename)

# Create directory for each category (optional)
def create_directories():
    for category in functions:
        if not os.path.exists(category):
            os.makedirs(category)
        os.chdir(category)
        generate_all_c_files()
        os.chdir('..')

# Run the script to generate all C files
create_directories()

