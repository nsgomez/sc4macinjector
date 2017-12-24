/*
   Project: libinjector, the library injector for SimCity 4 Mac
   File: cRZString.h
 
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
#include <string>
#include "cIGZString.h"

class cRZString : public cIGZString
{
public:
    virtual bool QueryInterface(uint32_t riid, void** ppvObj);
    virtual uint32_t AddRef(void);
    virtual uint32_t Release(void);
    
    virtual uint32_t FromChar(char const* pszSource);
    virtual uint32_t FromChar(char const* pszSource, uint32_t dwLength);
    virtual char const* ToChar(void) const;
    virtual char const* Data(void) const;
    
    virtual uint32_t Strlen(void) const;
    virtual bool IsEqual(cIGZString const* szOther, bool bCaseSensitive) const;
    virtual bool IsEqual(cIGZString const& szOther, bool bCaseSensitive) const;
    virtual bool IsEqual(char const* pszOther, uint32_t dwLength, bool bCaseSensitive) const;
    
    virtual int32_t CompareTo(cIGZString const& szOther, bool bCaseSensitive) const;
    virtual int32_t CompareTo(char const* pszOther, uint32_t dwLength, bool bCaseSensitive) const;
    
    virtual cIGZString& operator=(cIGZString const& szOther);
    
    virtual int32_t Copy(cIGZString const& szOther);
    virtual int32_t Resize(uint32_t dwNewSize);
    
    virtual cIGZString* Append(char const* pszOther, uint32_t dwLength);
    virtual cIGZString* Append(cIGZString const& szOther);
    virtual cIGZString* Insert(uint32_t dwPos, char const* pszOther, uint32_t dwLength);
    virtual cIGZString* Insert(uint32_t dwPos, cIGZString const& szOther);
    virtual cIGZString* Replace(uint32_t dwStartPos, char const* pszOther, uint32_t dwLength);
    virtual cIGZString* Replace(uint32_t dwStartPos, cIGZString const& szOther);
    virtual cIGZString* Erase(uint32_t dwStartPos, uint32_t dwEndPos);
    
    virtual int32_t Find(char const* pszOther, uint32_t dwPos, bool bCaseSensitive) const;
    virtual int32_t Find(cIGZString const& szOther, uint32_t dwPos, bool bCaseSensitive) const;
    
    virtual int32_t RFind(char const* pszOther, uint32_t dwPos, bool bCaseSensitive) const;
    virtual int32_t RFind(cIGZString const& szOther, uint32_t dwPos, bool bCaseSensitive) const;
    
    virtual cIGZString* Sprintf(char const* pszFormat, ...);
    
public:
    const char *str;
    //std::string str;
    int32_t refcount;
};