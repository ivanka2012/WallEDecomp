#ifndef ALLOC_H
#define ALLOC_H

#ifdef __cplusplus
#include <string.h>

//Placement new
//Implied to be an inline function
inline void* operator new(unsigned long size, void* ptr) {return ptr;}

/**
 * @brief C++ allocate a `size` memory block. Used in pair with `New_Z`
 * 
 * First verified to match: 2024-03-22 18:28:24
 * 
 * @param size 
 * @param comment 
 * @param filename 
 * @param line 
 * @return void* 
 */
void* operator new(unsigned long size, const char* comment, const char* filename, long line);

void* operator new[](unsigned long size, const char* comment, const char* filename, long line);

void operator delete(void* ptr);

void operator delete(void* ptr, const char* comment, const char* filename, long line);

void operator delete[](void* ptr);

void operator delete[](void* ptr, const char* comment, const char* filename, long line);

#endif

/**
 * @brief Zouna's free function
 * 
 * First verified to match: 2024-03-22 22:44:26
 * 
 * @param ptr 
 */
void Z_Free(void* ptr);
/**
 * @brief Zouna's alloc function
 * 
 * First verified to match: 2024-03-22 22:44:39
 * 
 * @param ptr 
 */
void* Z_Alloc(unsigned long size, const char* comment, const char* filename, long line, unsigned long align);
/**
 * @brief Zouna's realloc function
 * 
 * First verified to match:  2024-03-22 22:44:41
 * 
 * @param ptr 
 */
void* Z_Realloc(void* ptr, unsigned long size, const char* comment, const char* filename, long line);

#define Alloc_Z(size) Z_Alloc(size, "Anonymous Alloc", __FILE__, __LINE__, 4)
#define Realloc_Z(ptr, size) Z_Realloc(ptr, size, "Anonymous Alloc", __FILE__, __LINE__)
#define Free_Z(ptr) Z_Free(ptr)

#define New_Z new ("Anonymous New", __FILE__, __LINE__)
#define NewC_Z(comment) new(comment, __FILE__, __LINE__)
#define Delete_Z delete

#endif