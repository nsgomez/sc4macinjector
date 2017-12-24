/*
   Project: libinjector, the library injector for SimCity 4 Mac
   File: injector.cpp
 
   Copyright (c) 2017 Nelson Gomez (simmaster07)
 
   Licensed under the MIT License. A copy of the License is available in
   LICENSE or at:
 
       http://opensource.org/licenses/MIT
 
   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.
*/

#include <dlfcn.h>
#include <stdio.h>
#include "cGZCOMLibrary.h"
#include "cRZString.h"
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
        
        fprintf(stderr,
                "Opening candidate library %s\n",
                self->msLibraryPath.str);
        
        // TODO: Replace string here with re-encoded path
        self->mHandle = dlopen(self->msLibraryPath.str, RTLD_NOW);
        
        if (!self->mHandle) {
            fprintf(stderr, "%s\n", dlerror());
            return false;
        }
        
        self->mbLoaded = true;
        
        typedef cIGZCOMDirector *(*FunctionTypeGD)();
        FunctionTypeGD pfn = NULL;
        
        pfn = (FunctionTypeGD)dlsym(self->mHandle, kCOMDirectorFunctionName);
        if (!pfn) {
            fprintf(stderr,
                    "cGZCOMLibrary::Load: The function '%s()' was not found in library: \"%s\"\n",
                    kCOMDirectorFunctionName,
                    self->msLibraryPath.str);
            
            cGZCOMLibrary__Free(self);
            return false;
        }
        
        cIGZCOMDirector* const pCOMDirector = pfn();
        if (!pCOMDirector) {
            fprintf(stderr,
                    "cGZCOMLibrary::Load: Failed to acquire GZCOM director from library: \"%s\"\n",
                    self->msLibraryPath.str);
            
            cGZCOMLibrary__Free(self);
            return false;
        }
        
        self->mpDirector = pCOMDirector;
        
        if (!pCOMDirector->InitializeCOM(GZCOM(), self->msLibraryPath)) {
            fprintf(stderr,
                    "cGZCOMLibrary::Load: GZCOM Director failed initialization in library: \"%s\"\n",
                    self->msLibraryPath.str);
            
            cGZCOMLibrary__Free(self);
            return false;
        }
    }
    
    return true;
}

__attribute__((constructor))
static void ctor(void)
{
    GZCOM = (cIGZCOM*(*)(void))rd_function_ptr_from_name(kszGZCOMFunc + 1, NULL);
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
