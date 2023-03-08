#include "string.h"

void itoa(int n, char *buffer)
{
	int i, sign;

	if ((sign = n) < 0) n = -n;
    i = 0;
    do {
        buffer[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) buffer[i++] = '-';
    buffer[i] = '\0';

}

void reverse(char *s) {
    int c, i, j;
    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

int strlen(const char *src)
{
	const char *tmp =src;

	while (*tmp++)
		;
	return tmp-src;
}

int strcmp(const char *src, const char *src2)
{
	unsigned char c1, c2;

	while (1) {
		c1 = *src++;
		c2 = *src2++;
		if (c1 != c2)
			return c1 < c2 ? -1 : 1;
		if (!c1)
			break;
	}
	return 0;
}
