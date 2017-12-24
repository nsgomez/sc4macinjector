/*
   Project: libinjector, the library injector for SimCity 4 Mac
   File: cIGZUnknown.h
 
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

static const uint32_t GZIID_cIGZUnknown = 1;

/**
 * @brief The fundamental COM object that all others inherit from
 *
 * Any COM object that interacts with the game or will be used by directors
 * should inherit from this object and implement refcounting as specified.
 */
class cIGZUnknown
{
	public:
		/**
		 * @brief Casts the object to the interface specified by riid
		 * @param riid The GUID for the interface type to cast to
		 * @param ppvObj A pointer to a void pointer to store the result in
		 * @return Whether the object could be successfully cast or not
		 */
		virtual bool QueryInterface(uint32_t riid, void** ppvObj) = 0;

		/**
		 * @brief Adds a reference to this object
		 * @return The new reference count for this object
		 */
		virtual uint32_t AddRef(void) = 0;

		/**
		 * @brief Removes a reference to this object
		 * @return The new reference count for this object
		 *
		 * If the reference count is zero, the object should delete itself and
		 * return zero unless it has pretty good reason not to, such as
		 * refcounting for the object being handled by some other service.
		 */
		virtual uint32_t Release(void) = 0;
};