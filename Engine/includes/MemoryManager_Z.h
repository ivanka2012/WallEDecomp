#pragma once
#include <Types_Z.h>

class Hi_MemoryManager_Z{

};

/**
 * I think that the following functions/classes were declared in LibMAC 
 */

class MemoryManager_Z : public Hi_MemoryManager_Z{
public:
    /**
     * @brief Allocate a `size` memory block with `align` alignment. 
     * Returns null on failure.
     * 
     * First verified to match: 2024-03-22 18:29:51
     * 
     * @param size 
     * @param comment 
     * @param filename Which file is this being allocated?
     * @param line What line of the file exactly?
     * @param align 
     * @return void* 
     */
    void* Alloc(U32 size, const Char* comment, const Char* filename, S32 line, U32 align);

    /**
     * @brief Reallocate a memory block to `size`.
     * Returns null on failure.
     * 
     * First verified to match: 2024-03-22 22:43:40
     * 
     * @param ptr 
     * @param size 
     * @param comment 
     * @param filename 
     * @param line 
     * @return void* 
     */
    void* Realloc(void* ptr, U32 size, const Char* comment, const Char* filename, S32 line);

    /**
     * @brief Free a memory block allocated by MemoryManager_Z. Works like C `free`.
     * 
     * First verified to match: 2024-03-22 22:42:53
     * 
     * @param ptr 
     */
    void Free(void* ptr);

};

extern MemoryManager_Z MemManager;