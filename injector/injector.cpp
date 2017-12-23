/*
 *  injector.cpp
 *  injector
 *
 *  Created by Nelson Gomez on 12/23/17.
 *  Copyright © 2017 Nelson Gomez. All rights reserved.
 *
 */

#include <dlfcn.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include "cGZCOMLibrary.h"

const char *kszTargetFunc = "__ZN13cGZCOMLibrary4LoadEv";

bool cGZCOMLibrary__Load(cGZCOMLibrary *self)
{
    fprintf(stderr, "Inside the replacement cGZCOMLibrary loader!\n");
    return false;
}

/*
 * Courtesy of http://thomasfinch.me/blog/2015/07/24/Hooking-C-Functions-At-Runtime.html
 */
__attribute__((constructor))
static void ctor(void)
{
    fprintf(stderr, "Calling dylib constructor\n");
    
    void *handle = dlopen(NULL, RTLD_NOW);
    void *original = dlsym(handle, kszTargetFunc);
    void *replacement = (void *)cGZCOMLibrary__Load;
    size_t offset = (intptr_t)replacement - (intptr_t)original + 5 * sizeof(char);
    
    size_t pageSize = sysconf(_SC_PAGESIZE);
    uintptr_t start = (uintptr_t)original;
    uintptr_t end = start + 1;
    uintptr_t pageStart = start & ~pageSize;
    mprotect((void *)pageStart, end - pageStart, PROT_READ | PROT_WRITE | PROT_EXEC);
    
    int64_t instruction = 0xE9 | ((int32_t)offset) << 8;
    *(int64_t*)original = instruction;
}
