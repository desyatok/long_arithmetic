#include "bignum_lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(a, b) (a) > (b) ? (a) : (b)

const int BASE = 10;

void print_number(const bignum_t *num)
{
    if (num == NULL) return;
    if (num->sign == -1)
    {
        printf("-");
    }
    if (num->size > 0)
    {
        for (int i = num->size - 1; i >= 0; i--)
        {
            printf("%c", num->digits[i]);
        }
        printf("\n");
    }
}

void free_num(bignum_t *num)
{
    if (num != NULL)
    {
        free(num->digits);
        free(num);
    }
}

_Bool delete_leading_zeros(bignum_t *num)
{
    int leading_zeros = 0;

    do
    {
        leading_zeros++;
    }
    while (leading_zeros < num->size && num->digits[num->size - leading_zeros - 1] == '0');

    if (leading_zeros == num->size)
    {
        if (num->sign == -1)
        {
            printf("String contains incorrect num"); // "-0" не является числом
            return 0;
        }
        num->size = 1;
    }
    else
    {
        num->size -= leading_zeros;
    }

    num->digits = realloc(num->digits, num->size * sizeof(char));
    return 1;
}

_Bool is_digit(const char c)
{
    return c >= '0' && c <= '9';
}

bignum_t *num_init(const char *str)
{
    if (str == NULL)
    {
        printf("String is empty");
        return NULL;
    }
    
    bignum_t *num = malloc(sizeof(bignum_t));

    if (str[0] == '-')
    {
        num->sign = -1;
        str++;
    }
    else
    {
        num->sign = 1;
    }

    num->size = strlen(str);
    num->digits = malloc(num->size * sizeof(char));

    for (size_t i = 0; i < num->size; i++)
    {
        if (!is_digit(str[i]))
        {
            printf("String contains incorrect num");
            free_num(num);
            return NULL;
        }
        num->digits[num->size - i - 1] = str[i];
    }

    if (num->digits[num->size - 1] == '0' && num->size != 1)
    {
        if (!delete_leading_zeros(num))
        {
            free_num(num);
            return NULL;
        }
    }
    return num;
}

char *number_to_string(const bignum_t *num)
{
    if (num == NULL) return NULL;

    char *str;

    if (num->sign == -1)
    {
        str = malloc((num->size + 2) * sizeof(char));
        str[0] = '-';
        str++;
    }
    else
    {
        str = malloc((num->size + 1) * sizeof(char));
    }

    for (size_t i = 0; i < num->size; i++)
    {
        str[i] = num->digits[num->size - i - 1];
    }
    str[num->size] = '\0';

    if (num->sign == -1) str--;
    return str;
}