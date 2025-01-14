/*   Copyright 2013 Juan Rada-Vilela

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

/* 
 * File:   fuzzylite.h
 * Author: jcrada
 *
 * Created on 1 February 2013, 10:47 AM
 */

#ifndef FL_FUZZYLITE_H
#define	FL_FUZZYLITE_H


#include <iostream>
#include <sstream>
#include <limits>

#ifndef FL_VERSION
#define FL_VERSION "?"
#endif

#ifndef FL_DATE
#define FL_DATE "?"
#endif

#ifndef FL_BUILD_PATH
#define FL_BUILD_PATH ""
#endif

namespace fl {
#ifdef FL_USE_FLOAT
    typedef float scalar;
#else
    typedef double scalar;
#endif

    static const scalar nan = std::numeric_limits<scalar>::quiet_NaN();
    static const scalar inf = std::numeric_limits<scalar>::infinity();
}

#define FL__FILE__ std::string(__FILE__).substr(std::string(FL_BUILD_PATH).size())

#define FL_LOG_PREFIX FL__FILE__ << " [" << __LINE__ << "]:"

#define FL_AT FL__FILE__, __LINE__, __FUNCTION__

#ifndef FL_DECIMALS
#define FL_DECIMALS 3//for formatting strings
#endif

#ifndef FL_DIVISIONS
#define FL_DIVISIONS 200 //for defuzzifiers
#endif

#ifndef FL_PRECISION
#define FL_PRECISION 1e-5
#endif

#ifdef FL_NO_LOG
#define FL_LOG(message)
#define FL_LOGP(message)
#else
#define FL_LOG(message) std::cout << FL_LOG_PREFIX << message << std::endl
#define FL_LOGP(message) std::cout << message << std::endl
#endif

#ifndef FL_DEBUG
#define FL_DEBUG false
#endif

#define FL_BEGIN_DEBUG_BLOCK if (FL_DEBUG == 1){
#define FL_END_DEBUG_BLOCK }


#define FL_DBG(message) FL_BEGIN_DEBUG_BLOCK \
        std::cout << FL__FILE__ << "::" << __FUNCTION__ << "[" << __LINE__ << "]:" \
                << message << std::endl;\
        FL_END_DEBUG_BLOCK


//class FL_EXPORT is require to build DLLs in Windows.
#ifdef FL_WINDOWS
#define FL_EXPORT __declspec(dllexport)
#else
#define FL_EXPORT 
#endif

#ifdef FL_WINDOWS
#include <ciso646> //alternative operator spellings:
//#define and &&
//#define or ||
//#define not !
//#define bitand &
//#define bitor |

//TODO: add these functions in Infix.cpp
//#define acosh(x)
//#define asinh(x)
//#define atanh(x)
//#define log1p

//C++ exception specification ignored except to indicate a function is not __declspec(nothrow)
//http://msdn.microsoft.com/en-us/library/sa28fef8%28v=vs.80%29.aspx
//to ignore warnings dealing with exceptions in Windows:
#pragma warning(disable:4290) 

//Windows NMake complains I should have pointers in all headers instead of 
//stack allocated objects. For example, std::string* instead of std::string.
#pragma warning(disable:4251)

//Ignore conditional expression constant of FL_DBG and alike
#pragma warning(disable:4127)
#else 
#endif

namespace fl {

    class FL_EXPORT fuzzylite {
    public:
        static std::string name();
        static std::string fullname();
        static std::string shortVersion();
        static std::string longVersion();
        static std::string author();

        static std::string date();
        static std::string platform();
        static std::string configuration();

        static std::string floatingPoint();

        static int decimals();
        static scalar precision();
        static int defaultDivisions();

        static bool logEnabled();
    };
}


#endif	/* FL_FUZZYLITE_H */

