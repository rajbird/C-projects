/**
 * Rajbir Deol
 * 0918139
*/
#ifndef __RDEOL_HASH__
#define __RDEOL_HASH__

#define SIZE 4
#define KEY (*(long long*)
#define VALUE (char*)
#define ARR map->arr

typedef struct HashElement{
    struct Elements{
        void * key;
        void * value;
    }Item[SIZE];
    int index;
}Elem;

typedef struct HashTable{
    Elem ** arr;
    int len;
}HTable;

/**
 * Pre-conditions: Pass length of hash table
 * Post-conditions: return an empty, initialized hash table is created
 */
HTable * createTable(int len);

/**
 * Pre-conditions: Pass in valid key and hash table
 * Post-conditions: returns index where key should be stored in hash table
 */
int hashFunc(void * key, HTable * map);

/**
 * Pre-conditions: Pass is valid hash table, key and value
 * Post-conditions: Stores key and value in index returend from hash function
 */
void insertKey(HTable * map, void * key, void * value);

/**
 * Pre-conditions: Pass in valid hash table and key
 * Post-conditions: The key/value pair are no longer in aarray. The length of
 * aarray is decreased by one
 */
void removeKey(HTable * map, void * key); //Key has to exist

/**
 * Pre-conditions: Pass is valid hash table and key
 * Post-conditions: Returns value associated with key, aarray is unchanged
 */
void * findKey(HTable * map, void * key);

/**
 * Pre-conditions: Pass in valid hash table, key and new value 
 * Post-conditions: Changes value assoicated with key in hash table
 */
void update(HTable * map, void * key, void * newValue);

/**
 * Pre-conditions: Pass in valid associative array(aarray) elem and key
 * Post-conditions: returns position where key is stored in aarray
 */
int locate(Elem * arr, void * key);

/**
 * Pre-conditions: Pass is valid hash table, position of key in aarray and index
 * where key is stored in hash table
 * Post-conditions: Rearranges associative array elem, where key was located
 */
void fix(HTable * map, int pos, int code);

/**
 * Pre-conditions: Pass in an initialized hash table
 * Post-conditions: the table is destroyed along with references, but data is not destroyed
 */
void destroyTable(HTable * map);
#endif