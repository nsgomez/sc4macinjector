/*
   Project: libinjector, the library injector for SimCity 4 Mac
   File: cGZCOMLibrary.h
 
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

#pragma once
#include <stdint.h>
#include "cIGZCOMDirector.h"
#include "cIGZCOMLibrary.h"
#include "cRZString.h"

typedef void* GZLibraryHandle;
class cIGZString;

///////////////////////////////////////////////////////////////////////////////
// cGZCOMLibrary
//
// Encapsulates a library's properties, such as its name and whether or not
// it is currently loaded. This class is an opaque platform depenedent 
// implementation -- no platform dependencies are required outside of the GZCOM.cpp
// file. 
//
class cGZCOMLibrary : public cIGZCOMLibrary{
public:
   cGZCOMLibrary();
   cGZCOMLibrary(const cIGZString& sLibraryPath);
   virtual ~cGZCOMLibrary() {};

   //cIGZUnknown
   bool   QueryInterface(uint32_t riid, void** ppvObj);
   uint32_t AddRef();
   uint32_t Release();

   //cIGZCOMLibrary
   bool Load();
   bool Free();

   void GetPath(cIGZString& sPath) const;
   bool SetPath(const cIGZString& sPath);

   GZLibraryHandle GetHandle() const;
   void            SetHandle(GZLibraryHandle handle);

   cIGZCOMDirector* GetDirector() const;
   void             SetDirector(cIGZCOMDirector* pDirector);

   bool IsLoaded() const;
   void SetLoaded(bool bUse);

   bool operator<  (const cGZCOMLibrary& rhs) const;
   bool operator>  (const cGZCOMLibrary& rhs) const;
   bool operator== (const cGZCOMLibrary& rhs) const;

public:
   bool             mbLoaded;       // Is the library currently loaded.
   uint32_t         mnRefCount;     // RefCount.
   cIGZCOMDirector* mpDirector;     // The interface used by GZCOM to manipulate the dll.
   cRZString        msLibraryPath;  // Full path to library file (e.g. Win32 DLL).
   GZLibraryHandle  mHandle;        // Library (OS-level) handle.
};
