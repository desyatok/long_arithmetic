#ifndef BIGNUM_LIB_H
#define BIGNUM_LIB_H

typedef struct bignum
{
    char *digits;
    int size;
    int sign; // хранит "1", если число неотрицательное, иначе "-1"
} bignum_t;

typedef bignum_t *bignum_ptr;

void print_number(bignum_ptr num);

bignum_ptr num_init(char *str); /* принимает строку с big-endian числом,
                                    * возвращает структуру с little-endian
                                    * используется для конвертации строки в структуру */

bignum_ptr add(bignum_ptr num1, bignum_ptr num2);

bignum_ptr subtract(bignum_ptr num1, bignum_ptr num2);

bignum_ptr multiply(bignum_ptr num1, bignum_ptr num2);

bignum_ptr divide(bignum_ptr num1, bignum_ptr num2);

bignum_ptr division_remainder(bignum_ptr num1, bignum_ptr num2);

char *number_to_string(bignum_ptr num);

void free_num(bignum_ptr num);


#endif //BIGNUM_LIB_H
