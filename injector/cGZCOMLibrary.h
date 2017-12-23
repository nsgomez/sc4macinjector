#pragma once
#include <stdint.h>
#include "cIGZCOMDirector.h"
#include "cIGZCOMLibrary.h"

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

protected:
   bool             mbLoaded;       // Is the library currently loaded.
   uint32_t         mnRefCount;     // RefCount.
   cIGZCOMDirector* mpDirector;     // The interface used by GZCOM to manipulate the dll.
   //cRZString        msLibraryPath;  // Full path to library file (e.g. Win32 DLL).
   GZLibraryHandle  mHandle;        // Library (OS-level) handle.
};
