#pragma once

#include "tiny/optional_flag_manipulator_fwd.h"

#include <new>


void test_TinyOptionalWithRegisteredCustomFlagManipulator();


//==============================================================
// ClassInHeader: Type used in tests. Especially: The full "tiny/optional.h" header is not included.
//==============================================================

struct ClassInHeader
{
  bool isEmpty = false;
  friend bool operator==(ClassInHeader const & lhs, ClassInHeader const & rhs)
  {
    return lhs.isEmpty == rhs.isEmpty;
  }
};


template <>
struct tiny::optional_flag_manipulator<ClassInHeader>
{
  static bool IsEmpty(ClassInHeader const & payload) noexcept
  {
    return payload.isEmpty;
  }

  static void InitializeIsEmptyFlag(ClassInHeader & uninitializedPayloadMemory) noexcept
  {
    ::new (&uninitializedPayloadMemory) ClassInHeader();
    uninitializedPayloadMemory.isEmpty = true;
  }

  static void PrepareIsEmptyFlagForPayload(ClassInHeader & emptyPayload) noexcept
  {
    emptyPayload.~ClassInHeader();
  }
};
