/*!
    @file
    @author     Albert Semenov
    @date       06/2009
*/
#ifndef __MYGUI_GENERIC_FACTORY_H__
#define __MYGUI_GENERIC_FACTORY_H__

#include "MyGUI_Prerequest.h"
#include "MyGUI_Types.h"
#include "MyGUI_Delegate.h"

namespace MyGUI
{

	template <typename Type>
	class GenericFactory
	{
	public:
		typedef delegates::CDelegate1<IObject*&> Delegate;
		static typename Delegate::IDelegate* getFactory()
		{
			return newDelegate(createFromFactory);
		}

	private:
		static void createFromFactory(IObject*& _instance)
		{
			_instance = new Type();
		}
	};

    /*template <typename T>
    struct CheckStaticConstructor
    {
		template <typename U, U> struct type_check { };
        template <typename _1> static char (& chk(type_check<void(*)(), _1::staticConstructor> *))[1];
        template <typename   > static char (& chk(...))[2];

		enum { Result = sizeof(chk<T>(0)) == sizeof(char[1]) };
    };

    template <typename T, bool Check = CheckStaticConstructor<T>::Result>
    struct RegisterType
    {
    };
 
    template <typename T>
    struct RegisterType<T, true>
    {
        static void CallStaticDestructor() { T::staticConstructor(); }
    };
 
    template <typename T>
    struct RegisterType<T, false>
    {
        static void CallStaticDestructor() { }
    };*/

	struct RegisterType
	{
		template <typename U, U> struct test_struct { };
		template<typename Type> static void CallStaticConstructor(test_struct<void(*)(), Type::staticConstructor>* a = 0)
		{
			Type::staticConstructor();
		}
		template<typename Type> static void CallStaticConstructor(...)
		{
		}
		template<typename Type> static void CallStaticDestructor(test_struct<void(*)(), Type::staticDestructor>* a = 0)
		{
			Type::staticDestructor();
		}
		template<typename Type> static void CallStaticDestructor(...)
		{
		}
	};

}

#endif // __MYGUI_GENERIC_FACTORY_H__
