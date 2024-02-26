#include "bignum_lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(a, b) (a) > (b) ? (a) : (b)

const int BASE = 10;

void bn_print(const bignum_t *num)
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

void bn_free(bignum_t *num)
{
    if (num != NULL)
    {
        free(num->digits);
        free(num);
    }
}

void delete_leading_zeros(bignum_t *num)
{
    int size = num->size;
    while (num->size > 1 && num->digits[num->size - 1] == '0')
    {
        num->size--;
    }
    if (num->size != size)
    {
        num->digits = realloc(num->digits, num->size * sizeof(char));
    }
}

_Bool is_digit(const char c)
{
    return c >= '0' && c <= '9';
}

bignum_t *bn_init(const char *str)
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
            bn_free(num);
            return NULL;
        }
        num->digits[num->size - i - 1] = str[i];
    }

    delete_leading_zeros(num);
    if (num->sign == -1 && num->digits[num->size - 1] == '0') // -0
    {
        num->sign = 1;
    }

    return num;
}

char *bn_to_str(const bignum_t *num)
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

int compare(const bignum_t *num1, const bignum_t *num2)
{
    if (num1->size > num2->size)
    {
        return 1;
    }
    else if (num1->size < num2->size)
    {
        return -1;
    }

    for (int i = num1->size - 1; i >= 0; i--)
    {
        if (num1->digits[i] > num2->digits[i])
        {
            return 1;
        }
        else if (num1->digits[i] < num2->digits[i])
        {
            return -1;
        }
    }
    return 0;
}

bignum_t *add_ui(const bignum_t *num1, const bignum_t *num2)
{
    if (num1 == NULL || num2 == NULL) return NULL;

    bignum_t *result = malloc(sizeof(bignum_t));
    result->size = max(num1->size, num2->size);
    result->sign = num1->sign;
    result->digits = malloc(result->size);

    int carry = 0;

    for (size_t i = 0; i < result->size; i++)
    {
        result->digits[i] = carry + (i < num1->size ? num1->digits[i] - '0' : 0)
                            + (i < num2->size ? num2->digits[i] - '0' : 0) + '0';
        carry = result->digits[i] - '0' >= BASE;
        if (carry)
        {
            result->digits[i] -= BASE;
        }
    }

    if (carry)
    {
        result->size++;
        result->digits = realloc(result->digits, result->size);
        result->digits[result->size - 1] = carry + '0';
    }
    return result;
}

bignum_t *subtract_ui(const bignum_t *num1, const bignum_t *num2)
{
    bignum_t *result = malloc(sizeof(bignum_t));
    result->size = num1->size;
    result->digits = malloc(result->size * sizeof(char));

    int borrow = 0;

    for (size_t i = 0; i < result->size; i++)
    {

        result->digits[i] = (i < num1->size ? num1->digits[i] - '0' : 0)
                            - (i < num2->size ? num2->digits[i] - '0' : 0) + '0' - borrow;
        borrow = result->digits[i] - '0' < 0;
        if (borrow)
        {
            result->digits[i] += BASE;
        }
    }

    delete_leading_zeros(result);
    return result;
}

bignum_t *calc_sign_and_subtract(const bignum_t *num1, const bignum_t *num2)
{
    bignum_t *result;
    int cmp = compare(num1, num2);

    if (cmp > 0)
    {
        result = subtract_ui(num1, num2);
        result->sign = num1->sign * cmp;
    }
    else if (cmp < 0)
    {
        result = subtract_ui(num2, num1);
        result->sign = num1->sign * cmp;
    }
    else
    {
        result = malloc(sizeof(bignum_t));
        result->size = 1;
        result->sign = 1;
        result->digits = malloc(sizeof(char));
        result->digits[0] = '0';
    }
    return result;
}

bignum_t *bn_add(const bignum_t *num1, const bignum_t *num2)
{
    if (num1 == NULL || num2 == NULL) return NULL;
    if (num1->sign * num2->sign == 1)
    {
        return add_ui(num1, num2);
    }
    else
    {
        return calc_sign_and_subtract(num1, num2);
    }
}

bignum_t *bn_sub(const bignum_t *num1, const bignum_t *num2)
{
    if (num1 == NULL || num2 == NULL) return NULL;
    if (num1->sign * num2->sign == 1)
    {
        return calc_sign_and_subtract(num1, num2);
    }
    else
    {
        return add_ui(num1, num2);
    }
}

bignum_t *bn_mul(const bignum_t *num1, const bignum_t *num2)
{
    if (num1 == NULL || num2 == NULL)
    {
        return NULL;
    }

    bignum_t *result = malloc(sizeof(bignum_t));
    result->sign = num1->sign * num2->sign;
    result->size = num1->size + num2->size;
    result->digits = malloc(result->size * sizeof(char));
    memset(result->digits,'0',result->size);

    int product, carry;

    for (size_t i = 0; i < num1->size; i++)
    {
        carry = 0;
        for (int j = 0; j < num2->size; j++)
        {
            product = (result->digits[i + j] - '0')
                                + (i < num1->size ? (num1->digits[i] - '0') * (num2->digits[j] - '0') : 0) + carry;
            result->digits[i + j] = product % BASE + '0';
            carry = product / BASE;
        }
        if (carry)
        {
            result->digits[i + num2->size] = carry + '0';
        }
    }

    delete_leading_zeros(result);
    return result;
}

bignum_t *duplicate(const bignum_t *num)
{
    if (num == NULL) return NULL;
    bignum_t *dup = malloc(sizeof(bignum_t));
    dup->size = num->size;
    dup->sign = num->sign;
    dup->digits = malloc(dup->size * sizeof(char));
    for (size_t i = 0; i < dup->size; i++)
    {
        dup->digits[i] = num->digits[i];
    }
    return dup;
}

bignum_t *divide_by_10(bignum_t *num) // работает как /= 10
{
    if (num == NULL) return NULL;
    if (num->size == 1) return num;
    char *divided = malloc((num->size - 1) * sizeof(char));
    for (int i = 1; i < num->size; i++)
    {
        divided[i - 1] = num->digits[i];
    }
    char *tmp = num->digits;
    num->size--;
    num->digits = divided;
    free(tmp);
    return num;
}

bignum_t *divide_aux(const bignum_t *num1, const bignum_t *num2, _Bool get_remainder)
{
    if (num1 == NULL || num2 == NULL || (num2->size == 1 && num2->digits[0] == '0'))
    {
        return NULL;
    }

    bignum_t *result = malloc(sizeof(bignum_t));
    result->size = num1->size;
    result->sign = num1->sign * num2->sign;
    result->digits = malloc(result->size * sizeof(char));
    memset(result->digits,'0',result->size);
    int result_size = 0;

    bignum_t *ten = bn_init("10");
    bignum_t *nil = bn_init("0");
    bignum_t *remainder = duplicate(num1);
    remainder->sign = 1;
    bignum_t *to_sub = duplicate(num2);

    while (to_sub->size < num1->size)
    {
        bignum_t *mul = bn_mul(to_sub, ten);
        to_sub->size = mul->size;
        to_sub->digits = realloc(to_sub->digits, to_sub->size * sizeof(char));
        for (int i = 0; i < to_sub->size; i++)
        {
            to_sub->digits[i] = mul->digits[i];
        }
        bn_free(mul);
    }

    for (int i = num1->size - 1; i >= 0 && to_sub->size >= num2->size; i--)
    {
        int digit = 0;
        while (compare(remainder, nil) >= 0)
        {
            if (compare(remainder, to_sub) < 0)
            {
                to_sub = divide_by_10(to_sub);
                break;
            }
            bignum_t *subtracted = subtract_ui(remainder, to_sub);
            for (int j = 0; j < remainder->size; j++)
            {
                remainder->digits[j] = j < subtracted->size ? subtracted->digits[j] : '0';
            }
            bn_free(subtracted);
            delete_leading_zeros(remainder);
            digit++;
        }
        result->digits[i] = digit + '0';
        result_size++;
    }

    while(result->size > result_size)
    {
        result = divide_by_10(result);
    }
    delete_leading_zeros(result);

    if (num1->sign == -1) // преобразование остатка и частного при действиях с отрицательными числами
    {
        bignum_t *neg_one = bn_init("-1");
        bignum_t *sum1 = bn_add(result, neg_one);
        char *tmp1 = result->digits;
        result->digits = sum1->digits;
        result->size = sum1->size;
        result->sign = sum1->sign;

        bignum_t *sum2;
        if (num2->sign == 1)
        {
            sum2 = bn_sub(remainder,num2);
        }
        else
        {
            sum2 = bn_add(remainder,num2);
        }
        char *tmp2 = remainder->digits;
        remainder->digits = sum2->digits;
        remainder->size = sum2->size;

        free(sum1);
        free(tmp1);
        bn_free(neg_one);
        free(sum2);
        free(tmp2);
    }

    bn_free(to_sub);
    bn_free(nil);
    bn_free(ten);

    if (get_remainder)
    {
        bn_free(result);
        return remainder;
    }
    bn_free(remainder);
    return result;
}

bignum_t *bn_div(const bignum_t *num1, const bignum_t *num2)
{
    return divide_aux(num1,num2,0);
}

bignum_t *bn_mod(const bignum_t *num1, const bignum_t *num2)
{
    return divide_aux(num1,num2,1);
}