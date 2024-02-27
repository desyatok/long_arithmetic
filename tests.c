#include <stdlib.h>

#include "minunit.h"
#include "bignum_lib.h"

const static int NUM_OF_BN = 6;
static bignum_t **nums;
static bignum_t **inits;
static bignum_t **sums;
static bignum_t **subs;
static bignum_t **muls;
static bignum_t **divs;
static bignum_t **mods;
static char **strs;


static inline void inits_setup()
{
    inits = malloc(sizeof(bignum_t *) * NUM_OF_BN / 2);
    for (int i = 0; i < NUM_OF_BN / 2; i++)
    {
        inits[i] = malloc(sizeof(bignum_t));
    }
    inits[0]->size = 11;
    inits[0]->sign = 1;
    inits[0]->digits = malloc(inits[0]->size * sizeof(char) + 1);
    strcpy( inits[0]->digits, "78999646456");


    inits[1]->size = 18;
    inits[1]->sign = -1;
    inits[1]->digits = malloc(inits[1]->size * sizeof(char) + 1);
    strcpy( inits[1]->digits, "000022996867876867");

    inits[2]->size = 1;
    inits[2]->sign = 1;
    inits[2]->digits = malloc(inits[2]->size * sizeof(char) + 1);
    strcpy( inits[2]->digits, "0");
}

static inline void strs_setup()
{
    strs = malloc(sizeof(char *) * NUM_OF_BN);
    strs[0] = "65464699987";
    strs[1] = bn_to_str(nums[1]);
    strs[2] = "-768678768699220000";
    strs[3] = bn_to_str(nums[3]);
    strs[4] = "0";
    strs[5] = bn_to_str(nums[5]);
}

static inline void sums_setup()
{
    sums = malloc(sizeof(bignum_t *) * NUM_OF_BN);
    for (int i = 1; i < NUM_OF_BN; i += 2)
    {
        sums[i] = malloc(sizeof(bignum_t));
    }
    sums[0] = bn_add(nums[0],nums[1]);

    sums[1]->size = 32;
    sums[1]->sign = 1;
    sums[1]->digits = malloc(sums[1]->size * sizeof(char) + 1);
    strcpy( sums[1]->digits, "75654074341544444400676678788899");

    sums[2] = bn_add(nums[2],nums[3]);

    sums[3]->size = 18;
    sums[3]->sign = -1;
    sums[3]->digits = malloc(sums[3]->size * sizeof(char) + 1);
    strcpy( sums[3]->digits, "324346653667876867");

    sums[4] = bn_add(nums[4],nums[5]);

    sums[5]->size = 26;
    sums[5]->sign = -1;
    sums[5]->digits = malloc(sums[5]->size * sizeof(char) + 1);
    strcpy( sums[5]->digits, "07575679999999999999999999");

}

static inline void subs_setup()
{
    subs = malloc(sizeof(bignum_t *) * NUM_OF_BN);
    for (int i = 1; i < NUM_OF_BN; i += 2)
    {
        subs[i] = malloc(sizeof(bignum_t));
    }
    subs[0] = bn_sub(nums[0],nums[1]);

    subs[1]->size = 32;
    subs[1]->sign = 1;
    subs[1]->digits = malloc(subs[1]->size * sizeof(char) + 1);
    strcpy( subs[1]->digits, "38654671438344444400676678788899");

    subs[2] = bn_sub(nums[2],nums[3]);

    subs[3]->size = 18;
    subs[3]->sign = 1;
    subs[3]->digits = malloc(subs[3]->size * sizeof(char) + 1);
    strcpy( subs[3]->digits, "775697140177876867");

    subs[4] = bn_sub(nums[4],nums[5]);

    subs[5]->size = 26;
    subs[5]->sign = -1;
    subs[5]->digits = malloc(subs[5]->size * sizeof(char) + 1);
    strcpy( subs[5]->digits, "07575679999999999999999999");
}

static inline void muls_setup()
{
    muls = malloc(sizeof(bignum_t *) * NUM_OF_BN);
    for (int i = 1; i < NUM_OF_BN; i += 2)
    {
        muls[i] = malloc(sizeof(bignum_t));
    }
    muls[0] = bn_mul(nums[0],nums[1]);

    muls[1]->size = 43;
    muls[1]->sign = 1;
    muls[1]->digits = malloc(muls[1]->size * sizeof(char) + 1);
    strcpy( muls[1]->digits, "0926058737476130796073475758064276159819356");

    muls[2] = bn_mul(nums[2],nums[3]);

    muls[3]->size = 28;
    muls[3]->sign = -1;
    muls[3]->digits = malloc(muls[3]->size * sizeof(char) + 1);
    strcpy( muls[3]->digits, "0000499610353991978788860081");

    muls[4] = bn_mul(nums[4],nums[5]);

    muls[5]->size = 1;
    muls[5]->sign = 1;
    muls[5]->digits = malloc(muls[5]->size * sizeof(char) + 1);
    strcpy( muls[5]->digits, "0");
}

void test_setup(void)
{
    nums = malloc(sizeof(bignum_t *) * NUM_OF_BN);
    nums[0] = bn_init("99888787667600444444448882345670");
    nums[1] = bn_init("0065464699987");

    nums[2] = bn_init("0002342576577");
    nums[3] = bn_init("-768678768699220000");

    nums[4] = bn_init("-99999999999999999997657570");
    nums[5] = bn_init("0");

    inits_setup();
    strs_setup();
    sums_setup();
    subs_setup();
    muls_setup();
}

void test_teardown(void) {
    for (int i = 0; i < NUM_OF_BN; i++)
    {
        bn_free(nums[i]);
    }
    free(nums);

    for (int i = 0; i < NUM_OF_BN; i++)
    {
        bn_free(sums[i]);
    }
    free(sums);

    for (int i = 0; i < NUM_OF_BN; i++)
    {
        bn_free(subs[i]);
    }
    free(subs);

    for (int i = 0; i < NUM_OF_BN; i++)
    {
        bn_free(muls[i]);
    }
    free(muls);

    for (int i = 1; i < NUM_OF_BN; i += 2)
    {
        free(strs[i]);
    }
    free(strs);

    for (int i = 0; i < NUM_OF_BN / 2; i++)
    {
        bn_free(inits[i]);
    }
    free(inits);
}

MU_TEST(test_init1)
{
    mu_check(bn_equal(inits[0], nums[1]));
}

MU_TEST(test_init2)
{
    mu_check(bn_equal(inits[1], nums[3]));
}

MU_TEST(test_init3)
{
    mu_check(bn_equal(inits[2], nums[5]));
}

MU_TEST(test_to_str1)
{
    mu_check(!strcmp(strs[0],strs[1]));
}

MU_TEST(test_to_str2)
{
    mu_check(!strcmp(strs[2],strs[3]));
}

MU_TEST(test_to_str3)
{
    mu_check(!strcmp(strs[4],strs[5]));
}

MU_TEST(test_add1)
{
    mu_check(bn_equal(sums[0], sums[1]));
}

MU_TEST(test_add2)
{
    mu_check(bn_equal(sums[2], sums[3]));
}

MU_TEST(test_add3)
{
    mu_check(bn_equal(sums[4], sums[5]));
}

MU_TEST(test_sub1)
{
    mu_check(bn_equal(subs[0], subs[1]));
}
MU_TEST(test_sub2)
{
    mu_check(bn_equal(subs[2], subs[3]));
}
MU_TEST(test_sub3)
{
    mu_check(bn_equal(subs[4], subs[5]));
}

MU_TEST(test_mul1)
{
    mu_check(bn_equal(muls[0], muls[1]));
}
MU_TEST(test_mul2)
{
    mu_check(bn_equal(muls[2], muls[3]));
}
MU_TEST(test_mul3)
{
    mu_check(bn_equal(muls[4], muls[5]));
}


MU_TEST_SUITE(test_suite) {
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);

    MU_RUN_TEST(test_init1);
    MU_RUN_TEST(test_init2);
    MU_RUN_TEST(test_init3);

    MU_RUN_TEST(test_to_str1);
    MU_RUN_TEST(test_to_str2);
    MU_RUN_TEST(test_to_str3);

    MU_RUN_TEST(test_add1);
    MU_RUN_TEST(test_add2);
    MU_RUN_TEST(test_add3);

    MU_RUN_TEST(test_sub1);
    MU_RUN_TEST(test_sub2);
    MU_RUN_TEST(test_sub3);

    MU_RUN_TEST(test_mul1);
    MU_RUN_TEST(test_mul2);
    MU_RUN_TEST(test_mul3);
}

int main(int argc, char *argv[]) {
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return MU_EXIT_CODE;
}