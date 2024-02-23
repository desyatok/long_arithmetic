#ifndef BIGNUM_LIB_H
#define BIGNUM_LIB_H

typedef struct bignum
{
    char *digits;
    int size;
    int sign; // хранит "1", если число неотрицательное, иначе "-1"
} bignum_t;

void print_number(const bignum_t *);

bignum_t *num_init(const char *); /* принимает строку с big-endian числом,
                                    * возвращает структуру с little-endian
                                    * используется для конвертации строки в структуру */

bignum_t *add(const bignum_t *, const bignum_t *);

bignum_t *subtract(const bignum_t *,const bignum_t *);

bignum_t *multiply(const bignum_t *, const bignum_t *);

bignum_t *divide(const bignum_t *, const bignum_t *);

bignum_t *division_remainder(const bignum_t *, const bignum_t *);

char *number_to_string(const bignum_t *);

void free_num(bignum_t *);


#endif //BIGNUM_LIB_H
