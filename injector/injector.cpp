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
#include "cGZCOMLibrary.h"
#include "incompat_msg.h"
#include "rd_route.h"

const char *kszLoadTargetFunc = "__ZN13cGZCOMLibrary4LoadEv";
const char *kszGZCOMFunc = "__Z5GZCOMv";

cIGZCOM *(*GZCOM)(void) = NULL;

const char kCOMDirectorFunctionName[] = "GZDllGetGZCOMDirector";

bool cGZCOMLibrary__Free(cGZCOMLibrary *self)
{
    if (self->mbLoaded) {
        if (self->mpDirector) {
            self->mpDirector = NULL;
        }
        
        dlclose(self->mHandle);
        
        self->mHandle = NULL;
        self->mbLoaded = false;
    }
    
    return true;
}

bool cGZCOMLibrary__Load(cGZCOMLibrary *self)
{
    fprintf(stderr, "Inside the replacement cGZCOMLibrary loader!\n");
    if (!self->mbLoaded) {
        // TODO: Convert string encoding of path
        
        // TODO: Replace NULL with path
        self->mHandle = dlopen(NULL, RTLD_NOW);
        
        if (!self->mHandle) {
            fprintf(stderr, "%s\n", dlerror());
            return false;
        }
        
        self->mbLoaded = true;
        
        typedef cIGZCOMDirector *(*FunctionTypeGD)();
        FunctionTypeGD pfn = NULL;
        
        pfn = (FunctionTypeGD)dlsym(self->mHandle, kCOMDirectorFunctionName);
        if (!pfn) {
            // TODO: Replace NULL with path
            fprintf(stderr, "cGZCOMLibrary::Load: The function '%s()' was not found in library: \"%s\"\n", kCOMDirectorFunctionName, NULL);
            
            cGZCOMLibrary__Free(self);
            return false;
        }
        
        cIGZCOMDirector* const pCOMDirector = pfn();
        if (!pCOMDirector) {
            // TODO: Replace NULL with path
            fprintf(stderr, "cGZCOMLibrary::Load: Failed to acquire GZCOM director from library: \"%s\"\n", NULL);
            
            cGZCOMLibrary__Free(self);
            return false;
        }
        
        self->mpDirector = pCOMDirector;
        
        // TODO: Replace NULL with GZCOM and path, respectively
        if (!pCOMDirector->InitializeCOM(GZCOM(), NULL)) {
            // TODO: Replace NULL with path
            fprintf(stderr, "cGZCOMLibrary::Load: GZCOM Director failed initialization in library: \"%s\"\n", NULL);
            
            cGZCOMLibrary__Free(self);
            return false;
        }
    }
    
    return true;
}

__attribute__((constructor))
static void ctor(void)
{
    GZCOM = (cIGZCOM*(*)(void))rd_function_ptr_from_name(kszGZCOMFunc, NULL);
    if (!GZCOM) {
        ShowErrorAlert("symbol GZCOM not found");
        return;
    }
    
    // rd_route ignores one leading underscore when searching for symbols,
    // so we'll also skip the first underscore in our symbol string.
    int ret = rd_route_byname(kszLoadTargetFunc + 1, NULL, (void *)cGZCOMLibrary__Load, NULL);
    if (ret != 0) {
        ShowErrorAlert("could not route cGZCOMLibrary::Load to trampoline");
        return;
    }
}
