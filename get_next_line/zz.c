#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <limits.h>

typedef struct s_context
{
    size_t buf_cap;
    size_t buf_pos;
    size_t buf_pos_prv;
    size_t nl_pos;
    size_t stash_len;
    size_t stash_st;
    char *stash;
    char *buffer;
} t_context;

int main(){
	static t_context ctx;

	printf("%ld", ctx.buf_cap);
	printf("%s", ctx.stash);
}