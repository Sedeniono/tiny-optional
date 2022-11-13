#pragma once

// Tests for various payload types.
// Note: Implementations split into separate .cpp files because the object file became larger than 
// what mingw could handle.
void test_TinyOptionalPayload_Bool();
void test_TinyOptionalPayload_FloatingPoint();
void test_TinyOptionalPayload_IntegersAndEnums();
void test_TinyOptionalPayload_IsEmptyFlagInMember();
void test_TinyOptionalPayload_Pointers();
void test_TinyOptionalPayload_StdTypes();
void test_TinyOptionalPayload_NestedOptionals();
void test_TinyOptionalPayload_ConstAndVolatile();
void test_TinyOptionalPayload_Cpp20NTTP();
void test_TinyOptionalPayload_WindowsHandles();
void test_TinyOptionalPayload_OtherTypes();
