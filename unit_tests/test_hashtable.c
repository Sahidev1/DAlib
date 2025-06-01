#include "../structures/hashtable.h"
#include <assert.h>
#include <stdio.h>

typedef int test_key;
typedef float value;

#define LINECHECK() (printf("LINE %d PASSED\n", __LINE__));

hkey_t hashcode(void *key_ptr)
{
    test_key *kptr = key_ptr;
    return *kptr;
}

// test assuming max entries per key is 8

int main()
{

    hash_table table;
    const int INIT_CAPACITY = 1;
    //LINECHECK();
    HASH_TABLE_init(&table, INIT_CAPACITY, &hashcode);
    //LINECHECK();

    assert(table.entries == 0 && table.size == INIT_CAPACITY && table.hash_code == &hashcode);

    test_key keys[] = {3, 6, 1, 88, 14, 66, 674, 1235, 3948};
    value values[] = {1.23f, 1.11f, 5.451f, 7.111f, 245.12f, 23.11f, 2222.32f, 2.3453f, 0.123f};

    assert(sizeof(keys) / sizeof(test_key) == sizeof(values) / sizeof(value));

    int kv_count = sizeof(keys) / sizeof(test_key);

    //LINECHECK();


    int i;
    for (i = 0; i < INIT_CAPACITY; i++)
    {
        //printf("I: %d\n", i);
        int retcode = HASH_TABLE_put(&table, &keys[i], &values[i]);
        assert(retcode == 0);
        assert(table.entries == i + 1);
        assert(table.size == INIT_CAPACITY);
        assert(HASH_TABLE_get(&table, &keys[i]) == &values[i]);
        //printf("\tgott outsidsssssex: %p\n", HASH_TABLE_get(&table, &keys[0]));
    }
    //LINECHECK();


    while (i < kv_count)
    {
        int retcode = HASH_TABLE_put(&table, &keys[i], &values[i]);
        assert(retcode == 0);
        assert(table.entries == i + 1);
        assert(HASH_TABLE_get(&table, &keys[i]) == &values[i]);
        //printf("\tgott: %p\n", HASH_TABLE_get(&table, &keys[i]));
        //printf("\tgott outsidsssssex: %p\n", HASH_TABLE_get(&table, &keys[0]));
        //printf("index: %d\n", i);
        assert(HASH_TABLE_get(&table, &keys[0]) == &values[0]);

        i++;
    }

    //printf("\tgott outsidex: %p\n", HASH_TABLE_get(&table, &keys[0]));

    //LINECHECK();
    assert(table.entries == kv_count);

#ifndef TESTMODE
    assert(table.size == 2 * INIT_CAPACITY);
#endif

    for(int i = 0; i < kv_count; i++){
        int retcode = HASH_TABLE_contains(&table, &keys[i]);
        assert(table.last_checked.key_ptr == &keys[i]);
        //printf("index: %d, retcode: %d\n", i, retcode);
        assert(retcode != 0);
    }
    //printf("\tgott outside: %p\n", HASH_TABLE_get(&table, &keys[0]));

    value *tmp;
    for (int i = 0; i < kv_count; i++)
    {
        //printf("index: %d, \t\tgotten: %p\n", i, HASH_TABLE_get(&table, &keys[i]));
        tmp = HASH_TABLE_get(&table, &keys[i]);
        //LINECHECK();
        //printf("tmp: %p, actual: %p\n", HASH_TABLE_get(&table, &keys[i]), &values[i]);
        assert(tmp == &values[i]);
    }

    void** keyset = HASH_TABLE_keys(&table);
    int keys_test = 0;
    int testval = ((unsigned int)(~0x0))>>(8*sizeof(unsigned int) - kv_count);

    for(int i = 0; i < table.entries; i++){
        void* key = keyset[i];
        keys_test ^= 0x1<<(((int)(key - (void*)&keys[0])))/sizeof(test_key);
        
    }

    assert(keys_test == testval);


    for (int i = 0; i < kv_count; i++)
    {
        assert(HASH_TABLE_delete(&table, &keys[i]) == 0);
        assert(HASH_TABLE_contains(&table, &keys[i]) == 0);
    }

    assert(table.entries == 0);

    return 0;
}