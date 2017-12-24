/*
   Project: libinjector, the library injector for SimCity 4 Mac
   File: cIGZCOMLibrary.h
 
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

class cIGZCOMDirector;
class cIGZString;

class cIGZCOMLibrary : public cIGZUnknown
{
	public:
		virtual bool GetPath(cIGZString& szCopyTo) = 0;
		virtual cIGZCOMDirector* GetDirector(void) = 0;

		virtual uintptr_t GetHandle(void) = 0;
		virtual bool IsLoaded(void) const = 0;
};