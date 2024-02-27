#ifndef BIGNUM_LIB_H
#define BIGNUM_LIB_H

typedef struct bignum
{
    char *digits;
    int size;
    int sign; // хранит "1", если число неотрицательное, иначе "-1"
} bignum_t;

void bn_print(const bignum_t *);

bignum_t *bn_init(const char *); /* принимает строку с big-endian числом,
                                    * возвращает структуру с little-endian
                                    * используется для конвертации строки в структуру */

bignum_t *bn_add(const bignum_t *, const bignum_t *);

bignum_t *bn_sub(const bignum_t *,const bignum_t *);

bignum_t *bn_mul(const bignum_t *, const bignum_t *);

bignum_t *bn_div(const bignum_t *, const bignum_t *);

bignum_t *bn_mod(const bignum_t *, const bignum_t *);

char *bn_to_str(const bignum_t *);

void bn_free(bignum_t *);

int bn_equal(const bignum_t *, const bignum_t *);

#endif //BIGNUM_LIB_H
