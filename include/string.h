/*
 * Public API.
 *
 * Copyright (c) 2019-2021, Arm Limited.
 * SPDX-License-Identifier: MIT
 */

#include <stddef.h>

void* memcpy(void*, const void*, size_t);
void* memmove(void*, const void*, size_t);
void* memset(void*, int, size_t);
void* memchr(const void*, int, size_t);
void* memrchr(const void*, int, size_t);
int memcmp(const void*, const void*, size_t);
char* strcpy(char*, const char*);
int strcmp(const char*, const char*);
char* strchr(const char*, int);
char* strrchr(const char*, int);
char* strchrnul(const char*, int);
size_t strlen(const char*);
size_t strnlen(const char*, size_t);
int strncmp(const char*, const char*, size_t);
