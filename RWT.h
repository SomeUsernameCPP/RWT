#ifndef RWT_H
#define RWT_H
#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef __MINGW32__
#include <Windows.h> 
#else
#include <windows.h>
#endif
#include <iostream>
#include <memory>
#include <limits>
#include <cassert>
#include <string>
#include <type_traits>
#ifdef _MSC_VER
#pragma warning (disable: 4127)            
#pragma warning (disable: 4996)           
#if defined(_MSC_VER) && _MSC_VER >= 1922  
#pragma warning (disable: 5054)        
#endif
#endif
#if defined(__clang__)
#if __has_warning("-Wunknown-warning-option")
#pragma clang diagnostic ignored "-Wunknown-warning-option" 
#endif
#pragma clang diagnostic ignored "-Wunknown-pragmas"             
#pragma clang diagnostic ignored "-Wold-style-cast"                
#pragma clang diagnostic ignored "-Wfloat-equal"                
#pragma clang diagnostic ignored "-Wformat-nonliteral"            
#pragma clang diagnostic ignored "-Wexit-time-destructors"    
#pragma clang diagnostic ignored "-Wglobal-constructors"       
#pragma clang diagnostic ignored "-Wsign-conversion"             
#pragma clang diagnostic ignored "-Wformat-pedantic"            
#pragma clang diagnostic ignored "-Wint-to-void-pointer-cast"     
#pragma clang diagnostic ignored "-Wzero-as-null-pointer-constant" 
#pragma clang diagnostic ignored "-Wdouble-promotion"             
#pragma clang diagnostic ignored "-Wimplicit-int-float-conversion" 
#elif defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wpragmas"            
#pragma GCC diagnostic ignored "-Wunused-function"       
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"  
#pragma GCC diagnostic ignored "-Wformat"               
#pragma GCC diagnostic ignored "-Wdouble-promotion"      
#pragma GCC diagnostic ignored "-Wconversion"             
#pragma GCC diagnostic ignored "-Wformat-nonliteral"     
#pragma GCC diagnostic ignored "-Wstrict-overflow"         
#pragma GCC diagnostic ignored "-Wclass-memaccess"      
#endif
template <class T>
class RWT
{
protected:
public:
	RWT() = default;
	~RWT() = default;
	template <class T>
	struct rebind
	{
		using other = RWT<U>;
	};
	T* allocate(size_t objCount) { return static_cast<T*>(operator new(sizeof(T) * objCount)); }
	void deallocate(T* pointer) { operator delete(pointer); }
	size_t max_size() const { return std::numeric_limits<size_t>::max; }
	template <class U, class... Args>
	void construct(U* pointer, Args&& ...args) { new(pointer) U(std::forward<Args>(args)...); }
	template <class U>
	void destroy(U* pointer) { pointer->~U(); }
};
using RWTint = RWT<int>;
using RWTstring = RWT<std::string>;
using RWTdouble = RWT<double>;
using RWTfloat = RWT<float>;
using RWTintp = RWT<int*>;
using RWTstringp = RWT<std::string*>;
using RWTdoublep = RWT<double*>;
using RWTfloatp = RWT<float*>;
#endif 

