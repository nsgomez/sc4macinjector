/*
   Project: libinjector, the library injector for SimCity 4 Mac
   File: cIGZString.h
 
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
#include "cIGZUnknown.h"

/**
 * @brief An interface for string objects, similar to std::string
 */
class cIGZString : public cIGZUnknown
{
	public:
		virtual uint32_t FromChar(char const* pszSource) = 0;
		virtual uint32_t FromChar(char const* pszSource, uint32_t dwLength) = 0;
		virtual char const* ToChar(void) const = 0;
		virtual char const* Data(void) const = 0;

		virtual uint32_t Strlen(void) const = 0;
		virtual bool IsEqual(cIGZString const* szOther, bool bCaseSensitive) const = 0;
		virtual bool IsEqual(cIGZString const& szOther, bool bCaseSensitive) const = 0;
		virtual bool IsEqual(char const* pszOther, uint32_t dwLength, bool bCaseSensitive) const = 0;

		virtual int32_t CompareTo(cIGZString const& szOther, bool bCaseSensitive) const = 0;
		virtual int32_t CompareTo(char const* pszOther, uint32_t dwLength, bool bCaseSensitive) const = 0;

		virtual cIGZString& operator=(cIGZString const& szOther) = 0;
		
		virtual int32_t Copy(cIGZString const& szOther) = 0;
		virtual int32_t Resize(uint32_t dwNewSize) = 0;
		
		virtual cIGZString* Append(char const* pszOther, uint32_t dwLength) = 0;
		virtual cIGZString* Append(cIGZString const& szOther) = 0;
		virtual cIGZString* Insert(uint32_t dwPos, char const* pszOther, uint32_t dwLength) = 0;
		virtual cIGZString* Insert(uint32_t dwPos, cIGZString const& szOther) = 0;
		virtual cIGZString* Replace(uint32_t dwStartPos, char const* pszOther, uint32_t dwLength) = 0;
		virtual cIGZString* Replace(uint32_t dwStartPos, cIGZString const& szOther) = 0;
		virtual cIGZString* Erase(uint32_t dwStartPos, uint32_t dwEndPos) = 0;

		virtual int32_t Find(char const* pszOther, uint32_t dwPos, bool bCaseSensitive) const = 0;
		virtual int32_t Find(cIGZString const& szOther, uint32_t dwPos, bool bCaseSensitive) const = 0;
		
		virtual int32_t RFind(char const* pszOther, uint32_t dwPos, bool bCaseSensitive) const = 0;
		virtual int32_t RFind(cIGZString const& szOther, uint32_t dwPos, bool bCaseSensitive) const = 0;

		virtual cIGZString* Sprintf(char const* pszFormat, ...) = 0;
};