/*
 *    Copyright (c) 2021 Project CHIP Authors
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

// This hack is needed because Beken SDK is not linking against libstdc++ correctly.
 extern "C" {
 void * __dso_handle = 0;
 }


 //Warkaround for ld error:undefined reference to '__sync_synchronize'
//refer to https://stackoverflow.com/questions/64658430/gnu-arm-embedded-toolchain-undefined-reference-to-sync-synchronize
extern "C" void __sync_synchronize() {}

extern "C" unsigned int __atomic_fetch_add_4(volatile void * ptr, unsigned int val, int memorder)
{
    return (*(unsigned int*)ptr + val);
}

extern "C" bool __atomic_compare_exchange_4(volatile void* pulDestination, void* ulComparand, unsigned int desired, bool weak, int success_memorder, int failure_memorder)
{
    bool ulReturnValue;
    if( *(unsigned int*)pulDestination == *(unsigned int*)ulComparand )
    {
        *(unsigned int*)pulDestination = desired;
         ulReturnValue = true;
    }
    else
    {
        *(unsigned int*)ulComparand = *(unsigned int*)pulDestination;
        ulReturnValue = false;
    }
    return ulReturnValue;
}

extern "C" unsigned int __atomic_fetch_sub_4(volatile void * ptr, unsigned int val, int memorder)
{
    return (*(unsigned int*)ptr + val);
}
extern "C" bool __atomic_compare_exchange_1(volatile void* pulDestination, void* ulComparand, unsigned char desired, bool weak, int success_memorder, int failure_memorder)
{
    bool ulReturnValue;
    if( *(unsigned char*)pulDestination == *(unsigned char*)ulComparand )
    {
        *(unsigned char*)pulDestination = desired;
         ulReturnValue = true;
    }
    else
    {
        *(unsigned char*)ulComparand = *(unsigned char*)pulDestination;
        ulReturnValue = false;
    }
    return ulReturnValue;
}

extern "C" unsigned int __atomic_fetch_and_4(volatile void *pulDestination, unsigned int ulValue, int memorder)
{
    unsigned int ulCurrent;

    ulCurrent = *(unsigned int*)pulDestination;
    *(unsigned int*)pulDestination &= ulValue;
    return ulCurrent;
}

extern "C" bool __sync_bool_compare_and_swap_4(volatile void* ptr, unsigned int oldval, unsigned int newval)
{
    if(*(unsigned int*)ptr == oldval)
    {
        *(unsigned int*)ptr = newval;
        return true;
    }
    else
    {
        return false;
    }
}

extern "C" bool __sync_bool_compare_and_swap_1(volatile void* ptr, unsigned char oldval, unsigned char newval)
{
    if (*(unsigned char*)ptr == oldval)
    {
       *(unsigned char*)ptr = newval;
        return true;
    }
    else
    {
        return false;
    }
}

/* stub for __libc_init_array */
extern "C" void _fini(void) { }
extern "C" void _init(void) {;}
