
char* strrev(char* s);

// K&R implementation
void int_to_ascii(int n, char str[]) 
{
    int i, sign;
    if ((sign = n) < 0) n = -n;
    i = 0;
    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) str[i++] = '-';
    str[i] = '\0';

    strrev(str);
}

char* strrev(char* s)
{
    char  c;
    char* s0 = s - 1;
    char* s1 = s;

    while (*s1) ++s1;

    while (s1-- > ++s0)
    {
        c = *s0;
        *s0 = *s1;
        *s1 = c;
    }

    return s;
}