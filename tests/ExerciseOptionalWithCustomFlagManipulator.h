#pragma once

#include "tiny/optional_flag_manipulator_fwd.h"

#include <new>


void test_TinyOptionalWithRegisteredCustomFlagManipulator();


//==============================================================
// ClassInHeader: Type used in tests. Especially: The full "tiny/optional.h" header is not included.
// Additionally, the class is templated, so optional_flag_manipulator needs to have a template argument, too.
//==============================================================

template <class T>
struct ClassInHeader
{
  bool isEmpty = false;
  T * ptr = nullptr;

  friend bool operator==(ClassInHeader const & lhs, ClassInHeader const & rhs)
  {
    return lhs.isEmpty == rhs.isEmpty && lhs.ptr == rhs.ptr;
  }
};


template <class T>
struct tiny::optional_flag_manipulator<ClassInHeader<T>>
{
  static bool is_empty(ClassInHeader<T> const & payload) noexcept
  {
    return payload.isEmpty;
  }

  static void init_empty_flag(ClassInHeader<T> & uninitializedPayloadMemory) noexcept
  {
    ::new (&uninitializedPayloadMemory) ClassInHeader<T>();
    uninitializedPayloadMemory.isEmpty = true;
  }

  static void invalidate_empty_flag(ClassInHeader<T> & emptyPayload) noexcept
  {
    emptyPayload.~ClassInHeader();
  }
};
