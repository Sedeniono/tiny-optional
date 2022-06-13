#pragma once

#include <cassert>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <functional> // Required for std::hash
#include <initializer_list>
#include <limits>
#include <memory>
#include <optional> // Required for std::nullopt etc.
#include <type_traits>
#include <utility>

#if (!defined(__cplusplus) || __cplusplus < 201703L) && (!defined(_MSVC_LANG) || _MSVC_LANG < 201703L)
  #error "The library requires at least C++17"
#endif



namespace tiny
{
// Special type and value to indicate that the user did not specify a certain template parameter type/value.
enum UseDefaultType
{
  UseDefaultValue
};
} // namespace tiny


namespace tiny
{
namespace impl
{

  //====================================================================================
  // Utilities for the implementation
  //====================================================================================

  // Marked as [[maybe_unused]] since clang till version 8 emits a warning that
  // this variable is supposedly unused.
  template <class... T>
  [[maybe_unused]] constexpr bool always_false = false;


  // std::remove_cvref is only available since C++20.
  template <class T>
  using my_remove_cvref_t = std::remove_cv_t<std::remove_reference_t<T>>;


  // Similar to std::conditional, but instead of resulting in a type it results in a value.
  // I would like to use ?: instead, but ?: requires 'compatible' types in the two branches.
  template <bool B, auto val1, auto val2>
  struct value_conditional
  {
    static constexpr auto value = val1;
  };

  template <auto val1, auto val2>
  struct value_conditional<false, val1, val2>
  {
    static constexpr auto value = val2;
  };


  // Helpers for the std::hash specializations.
  // Cannot use std::enable_if_t<..., optional> directly because it results in a compiler error 'the template
  // parameter not used or deducible in partial specialization'.
  template <class Type, class>
  using ConditionalIdentity = Type;

  // clang-format off
  template <class Type, class TypeToCheckForHashable>
  using EnableHashHelper = ConditionalIdentity<
    Type,
    std::enable_if_t< 
      std::is_default_constructible_v<std::hash<std::remove_const_t<TypeToCheckForHashable>>> 
    >
  >;
  // clang-format on


  // Helper to implement the comparison operators.
  // The operators accepting any type U should not be selected if U is a TinyOptionalImpl or a derived class.
  template <class U>
  constexpr std::enable_if_t<U::is_tiny_optional, bool> EnableComparisonWithValue(U const *)
  {
    return false;
  }

  template <class>
  constexpr bool EnableComparisonWithValue(...)
  {
    return true;
  }


  // Extracts the class and target variable of a given member pointer.
  // https://stackoverflow.com/a/41475087
  template <auto memberPointer>
  struct MemberPointerFragments;

  template <typename ClassType_, typename VariableType_, VariableType_ ClassType_::*memberPointer>
  struct MemberPointerFragments<memberPointer>
  {
    using ClassType = ClassType_;
    using VariableType = VariableType_;
  };


  // Returns true if the numerical value of the integral 'value' fits into the literal 'TargetT'.
  // Similar to std::in_range but works also for char, etc.
  // Also, std::in_range is not available in C++17.
  template <class TargetT, class SourceT>
  static constexpr bool IsIntegralInRange(SourceT value) noexcept
  {
    static_assert(std::is_integral_v<TargetT>);
    static_assert(std::is_integral_v<SourceT>);

    if constexpr (std::is_signed_v<TargetT> == std::is_signed_v<SourceT>) {
      using CommonT = std::common_type_t<TargetT, SourceT>;
      return static_cast<CommonT>(std::numeric_limits<TargetT>::lowest()) <= static_cast<CommonT>(value)
             && static_cast<CommonT>(value) <= static_cast<CommonT>(std::numeric_limits<TargetT>::max());
    }
    else if constexpr (std::is_signed_v<SourceT>) {
      // Source = signed, target = unsigned
      return value >= 0 && IsIntegralInRange<TargetT>(static_cast<std::make_unsigned_t<SourceT>>(value));
    }
    else {
      constexpr TargetT targetMax = std::numeric_limits<TargetT>::max();

      // Source = unsigned, target = signed
      static_assert(std::is_signed_v<TargetT>);
      static_assert(targetMax > 0);

      using TargetUnsignedT = std::make_unsigned_t<TargetT>;
      using CommonUnsignedT = std::common_type_t<SourceT, TargetUnsignedT>;
      return static_cast<CommonUnsignedT>(value) <= static_cast<CommonUnsignedT>(targetMax);
    }
  }


  // When optional is not doing anything special, i.e. in cases where it behaves just like std::optional, it uses
  // this wrapper to store the 'IsEmpty'-Flag outside of the payload.
  template <class PayloadType>
  struct SeparateFlagWrapper
  {
    std::remove_const_t<PayloadType> payload;
    bool isEmptyFlag;
  };


//====================================================================================
// IsTypeWithUnusedBits and EmptyValueExploitingUnusedBits
//====================================================================================

// So far the implementation defined exploits are only implemented and tested for x64 and x86.
// https://stackoverflow.com/a/66249936
#if !(                                                                                                                 \
    (defined(__x86_64__) || defined(_M_X64)) /* Is it x64?*/                                                           \
    || (defined(i386) || defined(__i386__) || defined(__i386) || defined(_M_IX86))) /*Is it x86?*/
  #error "Exploiting of unused bits is not implemented for the target architecture."
#endif


  // optional is storing the 'IsEmpty'-flag within the payload itself automatically for certain types.
  // These types are identified by this constant.
  // Each of these types must have a corresponding EmptyValueExploitingUnusedBits specialization.
  // clang-format off
  template <class T>
  struct IsTypeWithUnusedBits
    : std::integral_constant<bool, 
        (std::is_floating_point_v<T> || std::is_same_v<std::remove_const_t<T>, bool> || std::is_pointer_v<T>) 
        && !std::is_same_v<std::remove_const_t<T>, long double>
      >
  {
  };
  // clang-format on


  // The specializations of EmptyValueExploitingUnusedBits define the bit pattern to use to indicate an empty value when
  // the 'IsEmpty'-flag is stored inplace for various standard types, as indicated by IsTypeWithUnusedBits.
  // By construction, we exploit implementation-defined behavior here, and use type punning.
  // Thus, the EmptyValueExploitingUnusedBits::value is not required to be of the same type as the
  // IsEmpty-flag-variable.
  template <typename T>
  struct EmptyValueExploitingUnusedBits
  {
    static_assert(
        always_false<T>,
        "Instantiation of EmptyValueExploitingUnusedBits with unknown type. Either an explicit specialization of "
        "EmptyValueExploitingUnusedBits is missing, or it should not have been instantiated in the first place. Bug.");
  };


  template <>
  struct EmptyValueExploitingUnusedBits<bool>
  {
    // We could use any value besides 0x00 and 0x01.
    // If a bool contains any other numerical value than 0 or 1, the bool can be true and false 'at the same time', i.e.
    // weird stuff can happen. See https://stackoverflow.com/q/56369080. In the code here we never use the bool as a
    // bool when its value is not 0 or 1.
    static constexpr std::uint8_t value = 0xfe;
    static_assert(sizeof(value) <= sizeof(bool));
  };


  template <>
  struct EmptyValueExploitingUnusedBits<double>
  {
    // Compare https://cwiki.apache.org/confluence/display/stdcxx/FloatingPoint
    // We use a NaN value that is not used by default as signaling or quiet NaN on any platform.
    // A quiet NaN is used to prevent accidental generation of a floating point exception when loaded into a register.
    static constexpr std::uint64_t value = 0x7ff8fedcba987654;
    static_assert(sizeof(value) == sizeof(double));
    static_assert(std::numeric_limits<double>::is_iec559);
  };


  template <>
  struct EmptyValueExploitingUnusedBits<float>
  {
    // Compare https://cwiki.apache.org/confluence/display/stdcxx/FloatingPoint
    // and https://www.doc.ic.ac.uk/~eedwards/compsys/float/nan.html

    // We use a quiet NaN value that is not used by default as signaling or quiet NaN on any platform.
    // A quiet NaN is used to prevent accidental generation of a floating point exception when loaded into a register.
    static constexpr std::uint32_t value = 0x7fedcba9;
    static_assert(sizeof(value) == sizeof(float));
    static_assert(std::numeric_limits<float>::is_iec559);
  };



  // Ordinary pointer or function pointer (but not a member pointer or member function pointer; those are rather
  // special, so we do not support to place the flag inplace for them).
  template <class T>
  struct EmptyValueExploitingUnusedBits<T *>
  {
    // Something like optional<T*> is rather unusal, because the usual thing would be to use a raw pointer instead
    // and indicate a missing value via nullptr. However, we support it especially because it allows compressed
    // optionals of structs/classes that contain a pointer. I.e. the 'IsEmpty'-flag can then be stored in a
    // member variable which is a pointer.
    //
    // We do not want to 'swallow' the nullptr value. Hence, instead we use the highest possible address.
    // In practice there should never be anything stored there.
    static constexpr std::uintptr_t value = UINTPTR_MAX;
    static_assert(sizeof(value) == sizeof(T *));
  };


  //====================================================================================
  // StoredTypeDecomposition
  //====================================================================================

  /*
   * The StoredTypeDecomposition concept defines how the data stored in the optional is
   * decomposed into payload and 'IsEmpty'-flag. It consist of:
   *
   * - The payload type, i.e. the type that the user actually wanted to store in the optional.
   *
   * - The StoredType indicates the type that the optional is actually storing internally. So
   *   this is bascially the type containing both the PayloadType and the IsEmptyFlagType.
   *   Note that they might be identical.
   *
   * - The type of the IsEmptyFlagType, i.e. the type of the variable storing the IsEmpty-flag.
   *   This is not explicity defined via a 'using' but by the return value of GetIsEmptyFlag().
   *
   * - GetIsEmptyFlag(): Given the StoredType, returns a mutable reference to the IsEmpty-flag.
   *
   * - GetPayload(): Given the StoredType, returns a mutable reference to the payload.
   */


  // Decomposition used when the optional is behaving as a std::optional, i.e. stores the
  // 'IsEmpty'-flag in a separate bool variable. This is realized using the SeparateFlagWrapper.
  template <class PayloadType_>
  struct DecompositionForSeparateFlag
  {
    using PayloadType = PayloadType_;
    using StoredType = SeparateFlagWrapper<PayloadType>;

    [[nodiscard]] static constexpr auto & GetIsEmptyFlag(StoredType & v) noexcept
    {
      return v.isEmptyFlag;
    }

    [[nodiscard]] static constexpr PayloadType & GetPayload(StoredType & v) noexcept
    {
      return v.payload;
    }
  };


  // Decomposition used when the stored type is both the payload and the 'IsEmpty'-flag at the same time.
  // The 'IsEmpty'-value can be stored by exploiting unused bit patterns or by 'swallowing' some
  // user specified value from the variable's value range.
  template <class StoredType_>
  struct InplaceStoredTypeDecomposition
  {
    using StoredType = StoredType_;
    using PayloadType = StoredType;

    [[nodiscard]] static constexpr StoredType & GetIsEmptyFlag(StoredType & v) noexcept
    {
      return v;
    }

    [[nodiscard]] static constexpr PayloadType & GetPayload(StoredType & v) noexcept
    {
      return v;
    }
  };


  // Decomposition used when the StoredType and the PayloadType are the same and identify a class/struct,
  // where the 'IsEmpty'-flag is stored inplace of one of the member variables of that class/struct.
  // This member variable is identified by the member pointer 'memPtrToIsEmptyFlag'.
  // The actual 'IsEmpty'-value can be stored by exploiting unused bit patterns or by 'swallowing' some
  // user specified value from the variable's value range.
  template <class StoredType_, auto memPtrToIsEmptyFlag>
  struct InplaceDecompositionViaMemPtr
  {
    static_assert(std::is_member_object_pointer_v<decltype(memPtrToIsEmptyFlag)>);
    static_assert(memPtrToIsEmptyFlag != nullptr);

    using StoredType = StoredType_;
    using PayloadType = StoredType;

    [[nodiscard]] static constexpr auto & GetIsEmptyFlag(StoredType & v) noexcept
    {
      return v.*memPtrToIsEmptyFlag;
    }

    [[nodiscard]] static constexpr PayloadType & GetPayload(StoredType & v) noexcept
    {
      return v;
    }
  };


  //====================================================================================
  // FlagManipulator
  //====================================================================================

  /**
   * The FlagManipulator concept provides functions to initialize, destroy and query
   * a given 'IsEmpty'-flag. Functions:
   *
   * - InitializeIsEmptyFlag(): This function receives the address of the already allocated
   *   memory that should contain the 'IsEmpty'-flag. The function must initialize this memory
   *   such that the flag indicates an empty state.
   *
   * - PrepareIsEmptyFlagForPayload(): This function receives the flag (which currently indicates
   *   the empty state, i.e. IsEmpty() returns true for it). The function is called just before
   *   the payload is constructed. It then must deconstruct the value such that after the payload
   *   has been constructed the 'IsEmpty'-flag must indicate that some value is set.
   *   Note: It must NOT free the memory!
   *
   * - IsEmpty(): This function receives a const-ref to the flag and must return 'true' if it
   *   indicates that the optional contains no value, and 'false' if it indicates that some
   *   value is set.
   */


  // Used when the optional is behaving as a std::optional, i.e. when the 'IsEmpty' flag is
  // stored in a separate bool variable (typicall via SeparateFlagWrapper).
  struct OrdinaryBoolFlagManipulator
  {
    [[nodiscard]] static bool IsEmpty(bool isEmptyFlag) noexcept
    {
      return isEmptyFlag;
    }

    static void InitializeIsEmptyFlag(bool & uninitializedIsEmptyFlagMemory) noexcept
    {
      uninitializedIsEmptyFlagMemory = true;
    }

    static void PrepareIsEmptyFlagForPayload(bool & isEmptyFlag) noexcept
    {
      isEmptyFlag = false;
    }
  };


  // Used when we exploit that the payload (or a member variable within the payload) has unused bit patterns.
  // In this case we use type punning and set the flag's bits directly to IsEmptyValue::value, which is typically
  // given by EmptyValueExploitingUnusedBits.
  // Note that FlagType and the type of the given IsEmptyValue::value can have different types. They are compared
  // and copied 'raw' (in the sense of std::memcmp and std::memcpy).
  template <class FlagType, class IsEmptyValue>
  struct MemcpyAndCmpFlagManipulator
  {
  private:
    static constexpr auto valueToIndicateEmpty = IsEmptyValue::value;
    static_assert(sizeof(valueToIndicateEmpty) <= sizeof(FlagType));
    static_assert(std::is_trivially_copyable_v<FlagType>);

  public:
    [[nodiscard]] static bool IsEmpty(FlagType const & isEmptyFlag) noexcept
    {
      return std::memcmp(&isEmptyFlag, &valueToIndicateEmpty, sizeof(valueToIndicateEmpty)) == 0;
    }

    static void InitializeIsEmptyFlag(FlagType & uninitializedIsEmptyFlagMemory) noexcept
    {
      std::memcpy(&uninitializedIsEmptyFlagMemory, &valueToIndicateEmpty, sizeof(valueToIndicateEmpty));
    }

    static void PrepareIsEmptyFlagForPayload(FlagType & /*isEmptyFlag*/) noexcept
    {
      // Nothing to do: The memory gets overwritten by the payload. It then automatically indicates that a value is set
      // (because we used an IsEmpty-value that is never used by a valid constructed payload).
    }
  };


  // Used when the user specified a specific value to 'swallow' and use to indicate the empty state.
  // For example, if the payload is an integer, the user might specify to use MAX_INT to indicate
  // the empty state. In principle we could use MemcpyAndCmpFlagManipulator for this, too. However,
  // ordinary assignment and comparison operators are absolutely sufficient in this case, so no
  // need to use hacky memcpy and memcmp operations.
  template <class FlagType, class IsEmptyValue>
  struct AssignmentFlagManipulator
  {
  private:
    // The empty value given by the user (IsEmptyValue) might have a different type than the flag variable.
    // This can happen very easily if the user e.g. specify the literal 42 as empty value (which is an 'int'),
    // but the optional stores an 'unsigned int'. It would be annoying for the user to always specify the
    // literals with the 'correct' postfix (e.g. 42u). Thus, we cast the value here. But before this we
    // check that the literal is not changed in the process. For example, specifying -1 for an optional
    // storing an 'unsigned' results in a compiler error.
    [[nodiscard]] static constexpr FlagType ConvertEmptyValueToFlagType() noexcept
    {
      using ValueType = std::remove_cv_t<decltype(IsEmptyValue::value)>;

      if constexpr (std::is_same_v<FlagType, bool> || std::is_same_v<ValueType, bool>) {
        static_assert(
            std::is_same_v<FlagType, ValueType>,
            "Either the variable used by the optional as IsEmpty flag or the specified compile-time constant "
            "for the empty value is a bool, but not both. If one is a bool, both should be a bool.");
        return IsEmptyValue::value;
      }
      else if constexpr (std::is_integral_v<FlagType> && std::is_integral_v<ValueType>) {
        // The static_cast prevents compiler warnings.
        // That we do not change the numeric value is ensured by the static_assert.
        static_assert(
            IsIntegralInRange<FlagType>(IsEmptyValue::value),
            "The specified compile-time constant for the empty value is outside of the range supported "
            "by the type of the variable used by the optional as IsEmpty-flag. Just as an example: "
            "'optional<unsigned, -1>' triggers this because the value -1 cannot be held by an 'unsigned'.");
        return static_cast<FlagType>(IsEmptyValue::value);
      }
      else if constexpr (std::is_floating_point_v<FlagType> || std::is_floating_point_v<ValueType>) {
        // Compile-time floating point values are fiddly, so for safety we require the types to be the same in this
        // case.
        static_assert(
            std::is_same_v<FlagType, ValueType>,
            "The IsEmpty-flag or the specified literal which indicates the empty state is a floating point type. "
            "Please ensure that they both have the exact same type. For example, if the IsEmpty-flag is a float, "
            "ensure that the IsEmpty-value is also a float and not e.g. a double.");
        return IsEmptyValue::value;
      }
      else {
        // If you get a compiler error here, then the specified compile-time constant for the empty value has a type
        // that is not compatible with the type used by the optional as IsEmpty-flag.
        return IsEmptyValue::value;
      }
    }

    static constexpr FlagType valueToIndicateEmpty = ConvertEmptyValueToFlagType();

  public:
    [[nodiscard]] static bool IsEmpty(FlagType const & isEmptyFlag) noexcept
    {
      return isEmptyFlag == valueToIndicateEmpty;
    }

    static void InitializeIsEmptyFlag(FlagType & uninitializedIsEmptyFlagMemory) noexcept
    {
      uninitializedIsEmptyFlagMemory = valueToIndicateEmpty;
    }

    static void PrepareIsEmptyFlagForPayload(FlagType & /*isEmptyFlag*/) noexcept
    {
      // Nothing to do: The memory gets overwritten by the payload. It then automatically indicates that a value is set
      // (because we used an IsEmpty-value that is never used by a valid constructed payload).
    }
  };


  //====================================================================================
  // StorageBase
  //====================================================================================

  // This is the lowest base for TinyOptionalImpl and contains the actual data and some basic manipulation functions.
  // The stuff cannot be part TinyOptionalImpl: To properly implement the constructors of TinyOptionalImpl, we need
  // to derive from various intermediate classes that implement the proper versions of the constructors depending on the
  // payload type. But all of these intermediate classes need to access the storage. Hence, all of them need to derive
  // from some common base class that contains the storage, which is this class here.
  template <class StoredTypeDecomposition, class FlagManipulator>
  struct StorageBase
  {
    using StoredType = typename StoredTypeDecomposition::StoredType;
    using PayloadType = typename StoredTypeDecomposition::PayloadType;
    using FlagType = std::decay_t<decltype(StoredTypeDecomposition::GetIsEmptyFlag(std::declval<StoredType &>()))>;

    static_assert(
        noexcept(StoredTypeDecomposition::GetIsEmptyFlag(std::declval<StoredType &>())),
        "StoredTypeDecomposition::GetIsEmptyFlag() must be noexcept");
    static_assert(
        noexcept(StoredTypeDecomposition::GetPayload(std::declval<StoredType &>())),
        "StoredTypeDecomposition::GetPayload() must be noexcept");

    static_assert(
        noexcept(FlagManipulator::IsEmpty(std::declval<FlagType>())),
        "FlagManipulator::IsEmpty() must be noexcept");
    // Especially InitializeIsEmptyFlag() must be noexcept because otherwise an optional could be
    // left in a weird uninitialized state. I.e. setting the IsEmpty-flag must always be possible.
    // Also, various noexcept specifications of member functions would be more complex.
    static_assert(
        noexcept(FlagManipulator::InitializeIsEmptyFlag(std::declval<FlagType &>())),
        "FlagManipulator::InitializeIsEmptyFlag() must be noexcept");
    static_assert(
        noexcept(FlagManipulator::PrepareIsEmptyFlagForPayload(std::declval<FlagType &>())),
        "FlagManipulator::PrepareIsEmptyFlagForPayload() must be noexcept");

    static_assert(
        !std::is_same_v<std::remove_cv_t<PayloadType>, std::nullopt_t>,
        "Placing a std::nullopt_t in an optional is not allowed by the C++ standard.");
    static_assert(
        !std::is_same_v<std::remove_cv_t<PayloadType>, std::in_place_t>,
        "Placing a std::in_place_t in an optional is not allowed by the C++ standard.");
    static_assert(
        std::is_object_v<PayloadType> && std::is_destructible_v<PayloadType> && !std::is_array_v<PayloadType>,
        "The payload type must meet the C++ requirement 'Destructible'.");

    StorageBase() noexcept
    {
      FlagManipulator::InitializeIsEmptyFlag(GetIsEmptyFlag());
      assert(!has_value());
    }

    template <class... ArgsT>
    explicit StorageBase(std::in_place_t, ArgsT &&... args)
    {
      // Initialize the IsEmpty flag first since PrepareIsEmptyFlagForPayload() might depend on it.
      FlagManipulator::InitializeIsEmptyFlag(GetIsEmptyFlag());
      ConstructPayload(std::forward<ArgsT>(args)...);
    }

    // TODO: The standard wants a trivial destructor if possible.
    ~StorageBase()
    {
      if (has_value()) {
        DestroyPayload();
      }
    }

    // The proper implemention of the following are defined in the derived classes.
    // It cannot be done here because depending on the payload they need to be different, and in C++17
    // there is no way to have multiple versions of each depending on the payload type.
    StorageBase(StorageBase const &) = delete;
    StorageBase(StorageBase &&) = delete;
    StorageBase & operator=(StorageBase const &) = delete;
    StorageBase & operator=(StorageBase &&) = delete;

    bool has_value() const noexcept
    {
      return !FlagManipulator::IsEmpty(GetIsEmptyFlag());
    }

    FlagType & GetIsEmptyFlag() noexcept
    {
      return StoredTypeDecomposition::GetIsEmptyFlag(this->mStorage);
    }

    FlagType const & GetIsEmptyFlag() const noexcept
    {
      return const_cast<StorageBase &>(*this).GetIsEmptyFlag();
    }

    PayloadType & GetPayload() noexcept
    {
      return StoredTypeDecomposition::GetPayload(this->mStorage);
    }

    PayloadType const & GetPayload() const noexcept
    {
      return const_cast<StorageBase &>(*this).GetPayload();
    }

    void DestroyPayload() noexcept
    {
      GetPayload().~PayloadType();
    }


    struct InitializeIsEmptyFlagScope
    {
      explicit InitializeIsEmptyFlagScope(StorageBase & opt) noexcept
        : mOptional(opt)
      {
      }

      ~InitializeIsEmptyFlagScope()
      {
        if (!doNotInitialize) {
          FlagManipulator::InitializeIsEmptyFlag(mOptional.GetIsEmptyFlag());
        }
      }

      StorageBase & mOptional;
      bool doNotInitialize = false;
    };


    template <class... ArgsT>
    void ConstructPayload(ArgsT &&... args) noexcept(std::is_nothrow_constructible_v<PayloadType, ArgsT...>)
    {
      // We first need to call the prepare function because it might free memory etc.
      // But that means, if the placement new throws, we need to initialize the
      // empty flag again afterwards. This is done by means of InitializeIsEmptyFlagScope.

      assert(!has_value());
      FlagManipulator::PrepareIsEmptyFlagForPayload(GetIsEmptyFlag());

      if constexpr (std::is_nothrow_constructible_v<PayloadType, ArgsT...>) {
        // Don't burden the optimizer with optimizing away the InitializeIsEmptyFlagScope if the scope is unnecessary in
        // the first place (i.e. if the construction cannot throw).
        ::new (std::addressof(GetPayload())) PayloadType(std::forward<ArgsT>(args)...);
      }
      else {
        InitializeIsEmptyFlagScope initScope{*this};
        ::new (std::addressof(GetPayload())) PayloadType(std::forward<ArgsT>(args)...);
        initScope.doNotInitialize = true;
      }

      // For example: A tiny optional storing an int and the special value MAX_INT indicates an empty optional.
      // If you then try to put MAX_INT directly into the optional, this assert gets triggered.
      // You must use reset() instead. Otherwise, we could run into inconsistencies with FlagManipulator.
      assert(
          has_value()
          && "Maybe the special flag value used to indicate an empty optional was assigned. Use reset() instead.");
    }


    template <class T>
    void AssignValue(T && v)
    {
      if (has_value()) {
        GetPayload() = std::forward<T>(v);
      }
      else {
        ConstructPayload(std::forward<T>(v));
      }

      // For example: A tiny optional storing an int and the special value MAX_INT indicates an empty optional.
      // If you then try to put MAX_INT directly into the optional, this assert gets triggered.
      // You must use reset() instead. Otherwise, we could run into inconsistencies with FlagManipulator.
      assert(
          has_value()
          && "Maybe the special flag value used to indicate an empty optional was assigned. Use reset() instead.");
    }


    void reset() noexcept
    {
      if (has_value()) {
        this->DestroyPayload();
        FlagManipulator::InitializeIsEmptyFlag(GetIsEmptyFlag());
        assert(!has_value());
      }
    }


    // Union to prevent automatic initialization of mStorage. I.e. this only allocates the memory without
    // calling the constructor of StoredType.
    // TODO for constexpr: Dummy member. Compare https://stackoverflow.com/a/57497579
    union
    {
      std::remove_const_t<StoredType> mStorage;
    };
  };


  //====================================================================================
  // MoveConstructionBase
  //====================================================================================

  // If the payload is not move constructible then the move constructor of TinyOptionalImpl must not participate in
  // overload resolution, meaning that the copy constructor should be called instead. Without C++20 concepts, there is
  // no way to let the move constructor participate conditionally in overload resolution if it gets defined directly in
  // TinyOptionalImpl. Therefore, TinyOptionalImpl simply defaults the move constructor and inherits from
  // MoveConstructionBase. Using template specialization, MoveConstructionBase either implements the move constructor or
  // deletes it, depending on whether the payload is move constructible or not. The defaulted move constructor of
  // TinyOptionalImpl will then automatically participate in overload resolution or not.

  // First version of MoveConstructionBase if the payload is move constructible.
  template <
      class StoredTypeDecomposition,
      class FlagManipulator,
      bool = std::is_move_constructible_v<typename StoredTypeDecomposition::PayloadType>>
  struct MoveConstructionBase : StorageBase<StoredTypeDecomposition, FlagManipulator>
  {
    using Base = StorageBase<StoredTypeDecomposition, FlagManipulator>;

    using Base::Base;
    using PayloadType = typename Base::PayloadType;

    MoveConstructionBase() = default;
    MoveConstructionBase(MoveConstructionBase const &) = default;

    // TODO: It is a trivial constructor if std::is_trivially_move_constructible_v<T> is true
    MoveConstructionBase(MoveConstructionBase && rhs) noexcept(std::is_nothrow_move_constructible_v<PayloadType>)
      // Call Base's default constructor since the whole purpose of the present class is to implement
      // the proper copy constructor (so the base class does not have a proper one).
      : Base()
    {
      if (rhs.has_value()) {
        this->ConstructPayload(std::move(rhs.GetPayload()));
      }
      else {
        assert(!this->has_value());
      }
    }
  };


  // Version with deleted move constructor.
  template <class StoredTypeDecomposition, class FlagManipulator>
  struct MoveConstructionBase<StoredTypeDecomposition, FlagManipulator, false>
    : StorageBase<StoredTypeDecomposition, FlagManipulator>
  {
    using Base = StorageBase<StoredTypeDecomposition, FlagManipulator>;
    using Base::Base;

    MoveConstructionBase() = default;
    MoveConstructionBase(MoveConstructionBase const &) = default;
    MoveConstructionBase(MoveConstructionBase &&) = delete;
  };


  //====================================================================================
  // CopyConstructionBase
  //====================================================================================

  // According to the standard, the copy constructor of optional should be defined as deleted if the
  // payload is not copy constructible. Similar to MoveConstructionBase, we need to use a dedicated base class to
  // actually implement the conditional deletion.

  // First version of CopyConstructionBase if the payload is copy constructible.
  template <
      class StoredTypeDecomposition,
      class FlagManipulator,
      bool = std::is_copy_constructible_v<typename StoredTypeDecomposition::PayloadType>>
  struct CopyConstructionBase : MoveConstructionBase<StoredTypeDecomposition, FlagManipulator>
  {
    using Base = MoveConstructionBase<StoredTypeDecomposition, FlagManipulator>;

    using PayloadType = typename Base::PayloadType;
    using Base::Base;

    CopyConstructionBase() = default;
    CopyConstructionBase(CopyConstructionBase &&) = default;

    // TODO: It is a trivial constructor if std::is_trivially_copy_constructible_v<T> is true.
    CopyConstructionBase(CopyConstructionBase const & rhs)
      // Call Base's default constructor since the whole purpose of the present class is to implement
      // the proper copy constructor (so the base class does not have a proper one).
      : Base()
    {
      if (rhs.has_value()) {
        this->ConstructPayload(rhs.GetPayload());
      }
      else {
        assert(!this->has_value());
      }
    }
  };


  // Version with deleted copy constructor.
  template <class StoredTypeDecomposition, class FlagManipulator>
  struct CopyConstructionBase<StoredTypeDecomposition, FlagManipulator, false>
    : MoveConstructionBase<StoredTypeDecomposition, FlagManipulator>
  {
    using Base = MoveConstructionBase<StoredTypeDecomposition, FlagManipulator>;
    using Base::Base;

    CopyConstructionBase() = default;
    CopyConstructionBase(CopyConstructionBase const &) = delete;
    CopyConstructionBase(CopyConstructionBase &&) = default;
  };


  //====================================================================================
  // MoveAssignmentBase
  //====================================================================================

  // According to the standard, the move assignment operator of optional should be defined as deleted if the
  // payload is not move constructible and move assignable. Similar to MoveConstructionBase, we need to use a dedicated
  // base class to actually implement the conditional deletion.

  // First version of MoveAssignmentBase if the payload is both move constructible and move assignable.
  template <
      class StoredTypeDecomposition,
      class FlagManipulator,
      bool = std::is_move_constructible_v<typename StoredTypeDecomposition::PayloadType> &&
          std::is_move_assignable_v<typename StoredTypeDecomposition::PayloadType>>
  struct MoveAssignmentBase : CopyConstructionBase<StoredTypeDecomposition, FlagManipulator>
  {
    using Base = CopyConstructionBase<StoredTypeDecomposition, FlagManipulator>;

    using Base::Base;
    using PayloadType = typename Base::PayloadType;

    MoveAssignmentBase() = default;
    MoveAssignmentBase(MoveAssignmentBase const &) = default;
    MoveAssignmentBase(MoveAssignmentBase &&) = default;
    MoveAssignmentBase & operator=(MoveAssignmentBase const &) = default;

    // TODO: It should be trivial if certain conditions are met.
    MoveAssignmentBase & operator=(MoveAssignmentBase && rhs) noexcept(
        std::is_nothrow_move_assignable_v<PayloadType> && std::is_nothrow_move_constructible_v<PayloadType>)
    {
      if (rhs.has_value()) {
        this->AssignValue(std::move(rhs.GetPayload()));
      }
      else {
        this->reset();
      }

      assert(this->has_value() == rhs.has_value());
      return *this;
    }
  };


  // Version with deleted move assignment operator.
  template <class StoredTypeDecomposition, class FlagManipulator>
  struct MoveAssignmentBase<StoredTypeDecomposition, FlagManipulator, false>
    : CopyConstructionBase<StoredTypeDecomposition, FlagManipulator>
  {
    using Base = CopyConstructionBase<StoredTypeDecomposition, FlagManipulator>;
    using Base::Base;

    MoveAssignmentBase() = default;
    MoveAssignmentBase(MoveAssignmentBase const &) = default;
    MoveAssignmentBase(MoveAssignmentBase &&) = default;
    MoveAssignmentBase & operator=(MoveAssignmentBase const &) = default;
    MoveAssignmentBase & operator=(MoveAssignmentBase &&) = delete;
  };


  //====================================================================================
  // CopyAssignmentBase
  //====================================================================================

  // According to the standard, the copy assignment operator of optional should be defined as deleted if the
  // payload is not copy constructible or copy assignable. Similar to MoveConstructionBase, we need to use a dedicated
  // base class to actually implement the conditional deletion.

  // First version of CopyAssignmentBase if the payload is copy constructible and copy assignable.
  template <
      class StoredTypeDecomposition,
      class FlagManipulator,
      bool = std::is_copy_constructible_v<typename StoredTypeDecomposition::PayloadType> &&
          std::is_copy_assignable_v<typename StoredTypeDecomposition::PayloadType>>
  struct CopyAssignmentBase : MoveAssignmentBase<StoredTypeDecomposition, FlagManipulator>
  {
    using Base = MoveAssignmentBase<StoredTypeDecomposition, FlagManipulator>;
    using Base::Base;

    CopyAssignmentBase() = default;
    CopyAssignmentBase(CopyAssignmentBase &&) = default;
    CopyAssignmentBase(CopyAssignmentBase const &) = default;
    CopyAssignmentBase & operator=(CopyAssignmentBase &&) = default;

    // TODO: It should be trivial if certain conditions are met.
    CopyAssignmentBase & operator=(CopyAssignmentBase const & rhs)
    {
      if (rhs.has_value()) {
        this->AssignValue(rhs.GetPayload());
      }
      else {
        this->reset();
      }

      assert(this->has_value() == rhs.has_value());
      return *this;
    }
  };


  // Version with deleted assignment operator.
  template <class StoredTypeDecomposition, class FlagManipulator>
  struct CopyAssignmentBase<StoredTypeDecomposition, FlagManipulator, false>
    : MoveAssignmentBase<StoredTypeDecomposition, FlagManipulator>
  {
    using Base = MoveAssignmentBase<StoredTypeDecomposition, FlagManipulator>;
    using Base::Base;

    CopyAssignmentBase() = default;
    CopyAssignmentBase(CopyAssignmentBase &&) = default;
    CopyAssignmentBase(CopyAssignmentBase const &) = default;
    CopyAssignmentBase & operator=(CopyAssignmentBase &&) = default;

    CopyAssignmentBase & operator=(CopyAssignmentBase const & rhs) = delete;
  };


  //====================================================================================
  // TinyOptionalImpl
  //====================================================================================

  // Actual implementation of optional.
  template <class StoredTypeDecomposition, class FlagManipulator>
  class TinyOptionalImpl : private CopyAssignmentBase<StoredTypeDecomposition, FlagManipulator>
  {
  private:
    using Base = CopyAssignmentBase<StoredTypeDecomposition, FlagManipulator>;

    using PayloadType = typename Base::PayloadType;

    using Base::ConstructPayload;
    using Base::GetIsEmptyFlag;
    using Base::GetPayload;

    // Helper for the constructor taking a U&& value.
    // Compare the std::optional standard for the conditions.
    template <class U>
    using EnableConvertingConstructor = std::bool_constant<
      std::is_constructible_v<PayloadType,U> 
      && !std::is_same_v<my_remove_cvref_t<U>, std::in_place_t> 
      // The next ensures that the copy or move constructor is called instead.
      && !std::is_same_v<my_remove_cvref_t<U>, TinyOptionalImpl>
      // The following is not in the standard. But we need it because we derive from TinyOptionalImpl,
      // and the constructor where this is used is incorrectly inherited in some versions of MSVC (in which
      // case std::is_same is not sufficient because it does not recognize if U is derived from 
      // TinyOptionalImpl); compare https://stackoverflow.com/a/71010787.
      && !std::is_base_of_v<TinyOptionalImpl, my_remove_cvref_t<U>>
  >;


  protected:
    template <class TinyOptionalType, class U>
  using EnableConvertingAssignment = std::bool_constant<            
      !std::is_same_v<my_remove_cvref_t<U>, TinyOptionalType>
      && std::is_constructible_v<PayloadType, U>
      && std::is_assignable_v<PayloadType&, U>
      // The following ensures that, if e.g. PayloadType==int, "o = {};" does not call this assignment operator here
      // with int initialized to 0, but instead constructs and then assigns an empty optional.
      && (!std::is_scalar_v<PayloadType> || !std::is_same_v<std::decay_t<U>, PayloadType>)
  >;


  public:
    using value_type = PayloadType;
    using Base::has_value;
    using Base::reset;

    // Marker that can be useful to check if a given type is a TinyOptionalImpl.
    static constexpr bool is_tiny_optional = true;

  public:
    // Implemented in base classes.
    TinyOptionalImpl() = default;
    TinyOptionalImpl(TinyOptionalImpl const &) = default;
    TinyOptionalImpl(TinyOptionalImpl &&) = default;
    TinyOptionalImpl & operator=(TinyOptionalImpl const &) = default;
    TinyOptionalImpl & operator=(TinyOptionalImpl &&) = default;
    ~TinyOptionalImpl() = default;


    TinyOptionalImpl(std::nullopt_t) noexcept
      : TinyOptionalImpl()
    {
    }


    template <class... ArgsT, class = std::enable_if_t<std::is_constructible_v<PayloadType, ArgsT...>>>
    explicit TinyOptionalImpl(std::in_place_t, ArgsT &&... args)
      : Base(std::in_place, std::forward<ArgsT>(args)...)
    {
    }


    template <
        class U,
        class... ArgsT,
        class = std::enable_if_t<std::is_constructible_v<PayloadType, std::initializer_list<U> &, ArgsT...>>>
    explicit TinyOptionalImpl(std::in_place_t, std::initializer_list<U> ilist, ArgsT &&... args)
      : Base(std::in_place, ilist, std::forward<ArgsT>(args)...)
    {
    }


    // Non-explicit converting constructor for types U that are implicitly convertible to the payload.
    template <
        class U = PayloadType,
        std::enable_if_t<EnableConvertingConstructor<U>::value && std::is_convertible_v<U, PayloadType>, int> = 0>
    TinyOptionalImpl(U && v)
      : Base(std::in_place, std::forward<U>(v))
    {
    }

    // Explicit constructor for types U that are not implicitly convertible to the payload.
    template <
        class U = PayloadType,
        std::enable_if_t<EnableConvertingConstructor<U>::value && !std::is_convertible_v<U, PayloadType>, int> = 0>
    explicit TinyOptionalImpl(U && v)
      : Base(std::in_place, std::forward<U>(v))
    {
    }


    // TODO: What about the converting copy and move constructors and assignments?
    // Problem: Assume we have
    //    optional<unsigned, 1> o1;
    // So the value 1 is used to indicate an empty state. And we have
    //    optional<int, 42> o2 = 1;
    // So o2 is not empty and contains the value 1.
    // What should happen at 'o1 = o2'? o1 cannot contain the value 1 because it indicates an empty state,
    // but o2 is not empty, so o1 should not be empty, too?
    // - Throw an exception? But how to actually detect this? Querying that has_value() is the same afterwards
    //   can be dangerous: We could run into inconsistencies with FlagManipulator.
    // - Somehow defer to the FlagManipulator and/or StoredTypeDecomposition?
    // - Do not implement them?
    // - In principle we could allow all conversions if the rhs did not use any swallowed value
    //   (meaning either the rhs exploits unused bits or uses a separate bool or is a std::optional).
    //   If not, issue a static_assert. Or throw an exception?
    // For now we do not implement them.


    TinyOptionalImpl & operator=(std::nullopt_t) noexcept
    {
      reset();
      return *this;
    }


    template <class U = PayloadType, std::enable_if_t<EnableConvertingAssignment<TinyOptionalImpl, U>::value, int> = 0>
    TinyOptionalImpl & operator=(U && v)
    {
      this->AssignValue(std::forward<U>(v));
      return *this;
    }


    template <class... ArgsT>
    PayloadType & emplace(ArgsT &&... args)
    {
      reset();
      ConstructPayload(std::forward<ArgsT>(args)...);
      assert(has_value());
      return GetPayload();
    }


    template <
        class U,
        class... ArgsT,
        class = std::enable_if_t<std::is_constructible_v<PayloadType, std::initializer_list<U> &, ArgsT...>>>
    PayloadType & emplace(std::initializer_list<U> ilist, ArgsT &&... args)
    {
      reset();
      ConstructPayload(ilist, std::forward<ArgsT>(args)...);
      assert(has_value());
      return GetPayload();
    }


    explicit operator bool() const noexcept
    {
      return has_value();
    }


    PayloadType * operator->() noexcept
    {
      assert(has_value() && "operator->() called on an empty optional");
      return std::addressof(GetPayload());
    }

    PayloadType const * operator->() const noexcept
    {
      assert(has_value() && "operator->() called on an empty optional");
      return std::addressof(GetPayload());
    }


    PayloadType & operator*() & noexcept
    {
      assert(has_value() && "operator*() called on an empty optional");
      return GetPayload();
    }

    PayloadType const & operator*() const & noexcept
    {
      assert(has_value() && "operator*() called on an empty optional");
      return GetPayload();
    }

    PayloadType && operator*() && noexcept
    {
      assert(has_value() && "operator*() called on an empty optional");
      return std::move(GetPayload());
    }

    PayloadType const && operator*() const && noexcept
    {
      assert(has_value() && "operator*() called on an empty optional");
      return std::move(GetPayload());
    }


    PayloadType & value() &
    {
      if (!has_value()) {
        throw std::bad_optional_access{};
      }
      return GetPayload();
    }

    PayloadType const & value() const &
    {
      if (!has_value()) {
        throw std::bad_optional_access{};
      }
      return GetPayload();
    }

    PayloadType && value() &&
    {
      if (!has_value()) {
        throw std::bad_optional_access{};
      }
      return std::move(GetPayload());
    }

    PayloadType const && value() const &&
    {
      if (!has_value()) {
        throw std::bad_optional_access{};
      }
      return std::move(GetPayload());
    }


    template <class U>
    PayloadType value_or(U && defaultValue) const &
    {
      static_assert(
          std::is_copy_constructible_v<PayloadType>,
          "PayloadType must be copy constructible for value_or().");
      static_assert(std::is_convertible_v<U, PayloadType>, "U must be convertible to PayloadType for value_or().");

#if defined(__GNUG__) && !defined(__clang__)
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif
      return has_value() ? GetPayload() : static_cast<PayloadType>(std::forward<U>(defaultValue));
#if defined(__GNUG__) && !defined(__clang__)
  #pragma GCC diagnostic pop
#endif
    }

    template <class U>
    PayloadType value_or(U && defaultValue) &&
    {
      static_assert(
          std::is_move_constructible_v<PayloadType>,
          "PayloadType must be move constructible for value_or().");
      static_assert(std::is_convertible_v<U, PayloadType>, "U must be convertible to PayloadType for value_or().");

#if defined(__GNUG__) && !defined(__clang__)
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif
      return has_value() ? std::move(GetPayload()) : static_cast<PayloadType>(std::forward<U>(defaultValue));
#if defined(__GNUG__) && !defined(__clang__)
  #pragma GCC diagnostic pop
#endif
    }


    void swap(TinyOptionalImpl & other) noexcept(
        std::is_nothrow_move_constructible_v<PayloadType> && std::is_nothrow_swappable_v<PayloadType>)
    {
      static_assert(std::is_move_constructible_v<PayloadType> && std::is_swappable_v<PayloadType>);

      bool const thisHasValue = has_value();
      if (thisHasValue == other.has_value()) {
        if (thisHasValue) {
          using std::swap;
          swap(GetPayload(), other.GetPayload());
        }
      }
      else {
        if (thisHasValue) {
          other.ConstructPayload(std::move(GetPayload()));
          reset();
        }
        else {
          ConstructPayload(std::move(other.GetPayload()));
          other.reset();
        }
      }
    }
  };


  // clang-format off
  template <
      class StoredTypeDecomposition,
      class FlagManipulator,
      std::enable_if_t<
          std::is_move_constructible_v<typename StoredTypeDecomposition::PayloadType> 
          && std::is_swappable_v<typename StoredTypeDecomposition::PayloadType>,
        int> = 0>
  void swap(
      TinyOptionalImpl<StoredTypeDecomposition, FlagManipulator> & lhs,
      TinyOptionalImpl<StoredTypeDecomposition, FlagManipulator> & rhs) 
    noexcept(noexcept(lhs.swap(rhs)))
  {
    lhs.swap(rhs);
  }
  // clang-format on


  //====================================================================================
  // SelectDecomposition
  //====================================================================================


  // Since the template specialization of SelectDecomposition are rather non-trivial, we want
  // some easy direct way of testing if the correct one was selected (i.e. while we modify
  // the code of SelectDecomposition). To this end, each (valid) specialization gets its
  // own enum value assign that we can static_assert against.
  enum SelectedDecompositionTest
  {
    NoArgsAndBehavesAsStdOptional,
    NoArgsButExploitUnusedBits,
    EmptyValueSpecifiedForInplaceSwallowingForTypeWithUnusedBits,
    EmptyValueSpecifiedForInplaceSwallowing,
    MemPtrSpecifiedToVariableWithUnusedBits,
    EmptyValueAndMemPtrSpecifiedForInplaceSwallowing,
    EmptyValueAndMemPtrSpecifiedForInplaceSwallowingForTypeWithUnusedBits
  };


  // True if T is a type where the user can choose a specific value (e.g. MAX_INT) to indicate an empty state.
  // That value is no longer considered to be in the valid value range, i.e. it is 'swallowed'.
  template <class T>
  struct TypeSupportsInplaceWithSwallowing
    : std::integral_constant<bool, std::is_scalar_v<T> && !IsTypeWithUnusedBits<T>::value>
  {
  };


  // Given the options chosen by the user, selects the proper StoredTypeDecomposition and FlagManipulator
  // with which to instantiate the TinyOptionalImpl. I.e. this is responsible for choosing if the 'IsEmpty'
  // flag should be stored inplace or out-of-place, and how it should be manipulated.
  //
  // PayloadType: The actual value that the user wants to store in the optional.
  // EmptyValue: Either UseDefaultType to let the implementation here choose the most suitable value to indicate an
  // empty
  //             state. Otherwise, EmptyValue::value must be the value to use to indicate an empty state.
  // memPtrToFlag: Either UseDefaultValue if the 'IsEmpty'-flag should not be stored in a member variable of the
  // payload.
  //               Otherwise, this must be a member pointer to the member variable where to store the 'IsEmpty'-flag
  //               in-place.
  template <class PayloadType, class EmptyValue, auto memPtrToFlag, class = void>
  struct SelectDecomposition
  {
    static_assert(
        always_false<PayloadType>,
        "Failed to select proper specialization of decomposition for tiny optional.");
  };


  template <class PayloadType>
  struct SelectDecomposition<
      PayloadType,
      UseDefaultType,
      UseDefaultValue,
      std::enable_if_t<!IsTypeWithUnusedBits<PayloadType>::value>>
  {
    static constexpr auto test = SelectedDecompositionTest::NoArgsAndBehavesAsStdOptional;

    using StoredTypeDecomposition = DecompositionForSeparateFlag<PayloadType>;
    using FlagManipulator = OrdinaryBoolFlagManipulator;
  };


  template <class PayloadType>
  struct SelectDecomposition<
      PayloadType,
      UseDefaultType,
      UseDefaultValue,
      std::enable_if_t<IsTypeWithUnusedBits<PayloadType>::value>>
  {
    static constexpr auto test = SelectedDecompositionTest::NoArgsButExploitUnusedBits;

    using StoredTypeDecomposition = InplaceStoredTypeDecomposition<PayloadType>;
    using FlagManipulator = MemcpyAndCmpFlagManipulator<PayloadType, EmptyValueExploitingUnusedBits<PayloadType>>;
  };


  template <class PayloadType, class EmptyValue>
  struct SelectDecomposition<
      PayloadType,
      EmptyValue,
      UseDefaultValue,
      std::enable_if_t<!std::is_scalar_v<PayloadType> && !std::is_same_v<EmptyValue, UseDefaultType>>>
  {
    static_assert(
        always_false<PayloadType>,
        "The payload type does not support an inplace flag, and you also did not specify that the flag should be stored in a member of the payload. "
        "That means a separate bool needs to be used to store the flag (meaning the optional is no longer tiny). However, you specified an EmptyValue, "
        "which is inconistent and unnecessary.");
  };


  template <class PayloadType, class EmptyValue>
  struct SelectDecomposition<
      PayloadType,
      EmptyValue,
      UseDefaultValue,
      std::enable_if_t<IsTypeWithUnusedBits<PayloadType>::value && !std::is_same_v<EmptyValue, UseDefaultType>>>
  {
    // The user specified a value to swallow for a type that has unused bits.
    // So the swallowing is in principle unnecessary. But maybe the user deliberately wants to mark
    // the value as 'invalid', so we do not static_assert this but instead support it.

    static constexpr auto test
        = SelectedDecompositionTest::EmptyValueSpecifiedForInplaceSwallowingForTypeWithUnusedBits;

    using StoredTypeDecomposition = InplaceStoredTypeDecomposition<PayloadType>;
    using FlagManipulator = AssignmentFlagManipulator<PayloadType, EmptyValue>;
  };


  template <class PayloadType, class EmptyValue>
  struct SelectDecomposition<
      PayloadType,
      EmptyValue,
      UseDefaultValue,
      std::enable_if_t<
          TypeSupportsInplaceWithSwallowing<PayloadType>::value && !std::is_same_v<EmptyValue, UseDefaultType>>>
  {
    static constexpr auto test = SelectedDecompositionTest::EmptyValueSpecifiedForInplaceSwallowing;

    using StoredTypeDecomposition = InplaceStoredTypeDecomposition<PayloadType>;
    using FlagManipulator = AssignmentFlagManipulator<PayloadType, EmptyValue>;
  };


  // clang-format off
  template <class PayloadType, auto memPtrToFlag>
  struct SelectDecomposition<
      PayloadType,
      UseDefaultType,
      memPtrToFlag,
      std::enable_if_t<
          std::is_member_object_pointer_v<decltype(memPtrToFlag)> 
          && IsTypeWithUnusedBits<typename MemberPointerFragments<memPtrToFlag>::VariableType>::value>>
  // clang-format on
  {
    static constexpr auto test = SelectedDecompositionTest::MemPtrSpecifiedToVariableWithUnusedBits;

    static_assert(
        std::is_same_v<PayloadType, typename MemberPointerFragments<memPtrToFlag>::ClassType>,
        "The flag given by the member-pointer is not a member of the payload type.");
    using MemVarType = typename MemberPointerFragments<memPtrToFlag>::VariableType;

    using StoredTypeDecomposition = InplaceDecompositionViaMemPtr<PayloadType, memPtrToFlag>;
    using FlagManipulator = MemcpyAndCmpFlagManipulator<MemVarType, EmptyValueExploitingUnusedBits<MemVarType>>;
  };


  // clang-format off
  template <class PayloadType, auto memPtrToFlag>
  struct SelectDecomposition<
      PayloadType,
      UseDefaultType,
      memPtrToFlag,
      std::enable_if_t<
          std::is_member_object_pointer_v<decltype(memPtrToFlag)> 
          && !IsTypeWithUnusedBits<typename MemberPointerFragments<memPtrToFlag>::VariableType>::value>>
  // clang-format on
  {
    static_assert(
        always_false<PayloadType>,
        "The type of the member variable given by the member-pointer cannot be used as flag if you do not specify a custom EmptyValue.");
  };


  // clang-format off
  template <class PayloadType, class EmptyValue, auto memPtrToFlag>
  struct SelectDecomposition<
      PayloadType,
      EmptyValue,
      memPtrToFlag,
      std::enable_if_t<
          !std::is_same_v<EmptyValue, UseDefaultType> 
          && std::is_member_object_pointer_v<decltype(memPtrToFlag)>
          && IsTypeWithUnusedBits<typename MemberPointerFragments<memPtrToFlag>::VariableType>::value>>
  // clang-format on
  {
    // The user specified a value to swallow for a type that has unused bits.
    // So the swallowing is in principle unnecessary. But maybe the user deliberately wants to mark
    // the value as 'invalid', so we do not static_assert this but instead support it.

    static constexpr auto test
        = SelectedDecompositionTest::EmptyValueAndMemPtrSpecifiedForInplaceSwallowingForTypeWithUnusedBits;

    static_assert(
        std::is_same_v<PayloadType, typename MemberPointerFragments<memPtrToFlag>::ClassType>,
        "The flag given by the member-pointer is not a member of the payload type.");
    using MemVarType = typename MemberPointerFragments<memPtrToFlag>::VariableType;

    using StoredTypeDecomposition = InplaceDecompositionViaMemPtr<PayloadType, memPtrToFlag>;
    using FlagManipulator = MemcpyAndCmpFlagManipulator<MemVarType, EmptyValue>;
  };


  // clang-format off
  template <class PayloadType, class EmptyValue, auto memPtrToFlag>
  struct SelectDecomposition<
      PayloadType,
      EmptyValue,
      memPtrToFlag,
      std::enable_if_t<
          !std::is_same_v<EmptyValue, UseDefaultType> 
          && std::is_member_object_pointer_v<decltype(memPtrToFlag)> 
          && TypeSupportsInplaceWithSwallowing<typename MemberPointerFragments<memPtrToFlag>::VariableType>::value>>
  // clang-format on
  {
    static constexpr auto test = SelectedDecompositionTest::EmptyValueAndMemPtrSpecifiedForInplaceSwallowing;

    static_assert(
        std::is_same_v<PayloadType, typename MemberPointerFragments<memPtrToFlag>::ClassType>,
        "The flag given by the member-pointer is not a member of the payload type.");
    using MemVarType = typename MemberPointerFragments<memPtrToFlag>::VariableType;

    using StoredTypeDecomposition = InplaceDecompositionViaMemPtr<PayloadType, memPtrToFlag>;
    using FlagManipulator = AssignmentFlagManipulator<MemVarType, EmptyValue>;
  };


  //====================================================================================
  // SelectEmptyValueAndMemPtrFromConstants
  //====================================================================================

  // If the second template parameter of optional is a member-pointer, it indicates the position of the
  // 'IsEmpty'-flag, and the third parameter might contain the specific empty value.
  // However, if the second parameter is no a member-pointer, it contains the specific empty value (or UseDefaultValue).
  // Figuring out the member-pointer (if any) and the empty value (if any) is performed here.
  template <class PayloadType_, auto emptyValueOrMemPtr, auto irrelevantOrEmptyValue>
  struct SelectEmptyValueAndMemPtrFromConstants
  {
    using PayloadType = PayloadType_;

    using emptyValueOrMemPtrType = decltype(emptyValueOrMemPtr);
    using irrelevantOrEmptyValueType = decltype(irrelevantOrEmptyValue);

    // if (emptyValueOrMemPtr is a memPtr)
    //    if (irrelevantOrEmptyValue == UseDefaultValue)
    //        EmptyValue = UseDefaultType
    //    else
    //        EmptyValue = irrelevantOrEmptyValue
    // else
    //    if (emptyValueOrMemPtr == UseDefaultValue)
    //        EmptyValue = UseDefaultType
    //    else
    //        EmptyValue = emptyValueOrMemPtr
    using EmptyValue = std::conditional_t<
        std::is_member_object_pointer_v<emptyValueOrMemPtrType>,
        std::conditional_t<
            std::is_same_v<irrelevantOrEmptyValueType, UseDefaultType>,
            UseDefaultType,
            std::integral_constant<irrelevantOrEmptyValueType, irrelevantOrEmptyValue>>,
        std::conditional_t<
            std::is_same_v<emptyValueOrMemPtrType, UseDefaultType>,
            UseDefaultType,
            std::integral_constant<emptyValueOrMemPtrType, emptyValueOrMemPtr>>>;

    static constexpr auto memPtr = value_conditional<
        std::is_member_object_pointer_v<emptyValueOrMemPtrType>,
        emptyValueOrMemPtr,
        UseDefaultValue>::value;
  };
} // namespace impl


//====================================================================================
// optional_empty_via_type
//====================================================================================

namespace impl
{

  // Shortcut for the following type definitions where the two template parameters of TinyOptionalImpl
  // are combined in one type.
  template <class Options>
  using TinyOptionalImplCombined
      = TinyOptionalImpl<typename Options::StoredTypeDecomposition, typename Options::FlagManipulator>;
} // namespace impl

// Basically the same as optional, except that the value for the 'IsEmpty'-flag needs to be specified via a type
// (i.e. EmptyValue::value).
template <class PayloadType, class EmptyValue, auto memPtr = UseDefaultValue>
using optional_empty_via_type
    = impl::TinyOptionalImplCombined<impl::SelectDecomposition<PayloadType, EmptyValue, memPtr>>;


//====================================================================================
// optional
//====================================================================================

namespace impl
{

  // Shortcut for optional definition below so that the SelectEmptyValueAndMemPtrFromConstants
  // needs to be specified only once.
  template <class Selection>
  using TinyOptionalFromSelection
      = optional_empty_via_type<typename Selection::PayloadType, typename Selection::EmptyValue, Selection::memPtr>;
} // namespace impl


// Main tiny optional type to be used by users of the library.
// Optionally allows to specify the value for the 'IsEmpty'-flag via a literal, and a member-pointer to indicate the
// 'IsEmpty'-flag.
//
// Implementation note: Unfortunately, we cannot use a simple 'using optional = TinyOptionalFromSelection<...>'
// because such a optional would have no usable deduction guides. I.e. an expression such as
//   optional o{5};
// would not compile. This even holds for C++20 where certain aliases do get deduction guides, but fails here
// because ultimately the template arguments for TinyOptionalImpl are computed via
// SelectDecomposition<...>::StoredTypeDecomposition etc, which results in expression that prevent their generation.
//
// Moreover, we deliberately use public rather than private inheritance. Assigning a optional to a TinyOptionalImpl
// (which might happen because of the other typedefs for TinyOptionalImpl that the user is supposed to use, such as
// optional_empty_via_type) makes sense, especially since it only works if the template parameter of
// optional::Base and the other TinyOptionalImpl are the same. Splicing is irrelevant because optional does not
// contain additional data members. In fact, as explained above, we actually would like optional to be a typedef to
// TinyOptionalImpl, but which is not possible due to the deduction guides. Moreover, public inheritance allows to
// re-use various functions, such as the comparison operators, without re-defining them for all possible combinations.
template <class PayloadType, auto emptyValueOrMemPtr = UseDefaultValue, auto irrelevantOrEmptyValue = UseDefaultValue>
class optional
  : public impl::TinyOptionalFromSelection<
        impl::SelectEmptyValueAndMemPtrFromConstants<PayloadType, emptyValueOrMemPtr, irrelevantOrEmptyValue>>
{
private:
  using Base = impl::TinyOptionalFromSelection<
      impl::SelectEmptyValueAndMemPtrFromConstants<PayloadType, emptyValueOrMemPtr, irrelevantOrEmptyValue>>;

public:
  using typename Base::value_type;
  static_assert(std::is_same_v<PayloadType, value_type>);

  optional() = default;
  optional(optional const &) = default;
  optional(optional &&) = default;
  optional & operator=(optional const &) = default;
  optional & operator=(optional &&) = default;
  ~optional() = default;

  using Base::Base;

  using Base::operator->;
  using Base::operator*;
  using Base::operator bool;
  using Base::emplace;
  using Base::has_value;
  using Base::reset;
  using Base::swap;
  using Base::value;
  using Base::value_or;


  optional & operator=(std::nullopt_t) noexcept
  {
    Base::operator=(std::nullopt);
    return *this;
  }


  template <
      class U = PayloadType,
      std::enable_if_t<Base::template EnableConvertingAssignment<optional, U>::value, int> = 0>
  optional & operator=(U && v)
  {
    Base::operator=(std::forward<U>(v));
    return *this;
  }
};


// Deduction guide.
template <class T>
optional(T) -> optional<T, UseDefaultValue, UseDefaultValue>;


template <class PayloadType, auto emptyValueOrMemPtr = UseDefaultValue, auto irrelevantOrEmptyValue = UseDefaultValue>
constexpr optional<std::decay_t<PayloadType>, emptyValueOrMemPtr, irrelevantOrEmptyValue> make_optional(
    PayloadType && v)
{
  return optional<std::decay_t<PayloadType>, emptyValueOrMemPtr, irrelevantOrEmptyValue>{std::forward<PayloadType>(v)};
}


template <
    class PayloadType,
    auto emptyValueOrMemPtr = UseDefaultValue,
    auto irrelevantOrEmptyValue = UseDefaultValue,
    class... ArgsT>
constexpr optional<PayloadType, emptyValueOrMemPtr, irrelevantOrEmptyValue> make_optional(ArgsT &&... args)
{
  return optional<PayloadType, emptyValueOrMemPtr, irrelevantOrEmptyValue>{std::in_place, std::forward<ArgsT>(args)...};
}


template <
    class PayloadType,
    auto emptyValueOrMemPtr = UseDefaultValue,
    auto irrelevantOrEmptyValue = UseDefaultValue,
    class U,
    class... ArgsT>
constexpr optional<PayloadType, emptyValueOrMemPtr, irrelevantOrEmptyValue> make_optional(
    std::initializer_list<U> il,
    ArgsT &&... args)
{
  return optional<PayloadType, emptyValueOrMemPtr, irrelevantOrEmptyValue>{
      std::in_place,
      il,
      std::forward<ArgsT>(args)...};
}


//====================================================================================
// optional_inplace
//====================================================================================

// A tiny optional that always stores the value inplace, but the user needs to supply the logic to check and set the
// 'IsEmpty'-flag.
template <class PayloadType, class FlagManipulator>
using optional_inplace = impl::TinyOptionalImpl<impl::InplaceStoredTypeDecomposition<PayloadType>, FlagManipulator>;


//====================================================================================
// Comparison operators
//====================================================================================

// Unfortunately, we need quite a bunch of overloads for the comparison between optionals that are essentially the same.
// E.g. we need dedicated overloads of optional and std::optional. The ones for TinyOptionalImpl and std::optional
// are not sufficient. Without them, a comparison of optional and std::optional would select the standard operator
// that compares a std::optional with any value U.
// I guess, the amount of copy & paste code justifies a macro here.
#define TINY_OPTIONAL_IMPL_COMPARE_BETWEEN_OPTIONALS(Op, code)                                                         \
  namespace impl                                                                                                       \
  {                                                                                                                    \
    template <class D1, class F1, class D2, class F2>                                                                  \
    constexpr bool operator Op(TinyOptionalImpl<D1, F1> const & lhs, TinyOptionalImpl<D2, F2> const & rhs)             \
    {                                                                                                                  \
      code                                                                                                             \
    }                                                                                                                  \
                                                                                                                       \
    template <class D1, class F1, class U>                                                                             \
    constexpr bool operator Op(TinyOptionalImpl<D1, F1> const & lhs, std::optional<U> const & rhs)                     \
    {                                                                                                                  \
      code                                                                                                             \
    }                                                                                                                  \
                                                                                                                       \
    template <class U, class D1, class F1>                                                                             \
    constexpr bool operator Op(std::optional<U> const & lhs, TinyOptionalImpl<D1, F1> const & rhs)                     \
    {                                                                                                                  \
      code                                                                                                             \
    }                                                                                                                  \
  }                                                                                                                    \
                                                                                                                       \
  template <class P, auto e, auto i, class U>                                                                          \
  constexpr bool operator Op(optional<P, e, i> const & lhs, std::optional<U> const & rhs)                              \
  {                                                                                                                    \
    code                                                                                                               \
  }                                                                                                                    \
                                                                                                                       \
  template <class U, class P, auto e, auto i>                                                                          \
  constexpr bool operator Op(std::optional<U> const & lhs, optional<P, e, i> const & rhs)                              \
  {                                                                                                                    \
    code                                                                                                               \
  }


//-----------------------
// operator==

// clang-format off
TINY_OPTIONAL_IMPL_COMPARE_BETWEEN_OPTIONALS(
  ==, 
  bool const lhsHasValue = lhs.has_value();
  return lhsHasValue == rhs.has_value() && (!lhsHasValue || *lhs == *rhs);
)
// clang-format on

namespace impl
{
  template <class D1, class F1>
  constexpr bool operator==(TinyOptionalImpl<D1, F1> const & lhs, std::nullopt_t)
  {
    return !lhs.has_value();
  }

  template <class D1, class F1>
  constexpr bool operator==(std::nullopt_t, TinyOptionalImpl<D1, F1> const & rhs)
  {
    return !rhs.has_value();
  }

  template <class D1, class F1, class U>
  constexpr std::enable_if_t<EnableComparisonWithValue<U>(nullptr), bool> operator==(
      TinyOptionalImpl<D1, F1> const & lhs,
      U const & rhs)
  {
    return lhs.has_value() ? *lhs == rhs : false;
  }

  template <class U, class D1, class F1>
  constexpr std::enable_if_t<EnableComparisonWithValue<U>(nullptr), bool> operator==(
      U const & lhs,
      TinyOptionalImpl<D1, F1> const & rhs)
  {
    return rhs.has_value() ? lhs == *rhs : false;
  }
} // namespace impl


//-----------------------
// operator!=

// clang-format off
TINY_OPTIONAL_IMPL_COMPARE_BETWEEN_OPTIONALS(
  !=, 
  bool const lhsHasValue = lhs.has_value();
  return lhsHasValue != rhs.has_value() || (lhsHasValue && *lhs != *rhs);
)
// clang-format on

namespace impl
{
  template <class D1, class F1>
  constexpr bool operator!=(TinyOptionalImpl<D1, F1> const & lhs, std::nullopt_t)
  {
    return lhs.has_value();
  }

  template <class D1, class F1>
  constexpr bool operator!=(std::nullopt_t, TinyOptionalImpl<D1, F1> const & rhs)
  {
    return rhs.has_value();
  }

  template <class D1, class F1, class U>
  constexpr std::enable_if_t<EnableComparisonWithValue<U>(nullptr), bool> operator!=(
      TinyOptionalImpl<D1, F1> const & lhs,
      U const & rhs)
  {
    return lhs.has_value() ? *lhs != rhs : true;
  }

  template <class U, class D1, class F1>
  constexpr std::enable_if_t<EnableComparisonWithValue<U>(nullptr), bool> operator!=(
      U const & lhs,
      TinyOptionalImpl<D1, F1> const & rhs)
  {
    return rhs.has_value() ? lhs != *rhs : true;
  }
} // namespace impl


//-----------------------
// operator<

// clang-format off
TINY_OPTIONAL_IMPL_COMPARE_BETWEEN_OPTIONALS(
  <, 
  return rhs.has_value() && (!lhs.has_value() || *lhs < *rhs);
)
// clang-format on

namespace impl
{
  template <class D1, class F1>
  constexpr bool operator<(TinyOptionalImpl<D1, F1> const &, std::nullopt_t)
  {
    return false;
  }

  template <class D1, class F1>
  constexpr bool operator<(std::nullopt_t, TinyOptionalImpl<D1, F1> const & rhs)
  {
    return rhs.has_value();
  }

  template <class D1, class F1, class U>
  constexpr std::enable_if_t<EnableComparisonWithValue<U>(nullptr), bool> operator<(
      TinyOptionalImpl<D1, F1> const & lhs,
      U const & rhs)
  {
    return lhs.has_value() ? *lhs < rhs : true;
  }

  template <class U, class D1, class F1>
  constexpr std::enable_if_t<EnableComparisonWithValue<U>(nullptr), bool> operator<(
      U const & lhs,
      TinyOptionalImpl<D1, F1> const & rhs)
  {
    return rhs.has_value() ? lhs < *rhs : false;
  }
} // namespace impl


//-----------------------
// operator<=

// clang-format off
TINY_OPTIONAL_IMPL_COMPARE_BETWEEN_OPTIONALS(
  <=, 
  return !lhs.has_value() || (rhs.has_value() && *lhs <= *rhs);
)
// clang-format on

namespace impl
{
  template <class D1, class F1>
  constexpr bool operator<=(TinyOptionalImpl<D1, F1> const & lhs, std::nullopt_t)
  {
    return !lhs.has_value();
  }

  template <class D1, class F1>
  constexpr bool operator<=(std::nullopt_t, TinyOptionalImpl<D1, F1> const &)
  {
    return true;
  }

  template <class D1, class F1, class U>
  constexpr std::enable_if_t<EnableComparisonWithValue<U>(nullptr), bool> operator<=(
      TinyOptionalImpl<D1, F1> const & lhs,
      U const & rhs)
  {
    return lhs.has_value() ? *lhs <= rhs : true;
  }

  template <class U, class D1, class F1>
  constexpr std::enable_if_t<EnableComparisonWithValue<U>(nullptr), bool> operator<=(
      U const & lhs,
      TinyOptionalImpl<D1, F1> const & rhs)
  {
    return rhs.has_value() ? lhs <= *rhs : false;
  }
} // namespace impl


//-----------------------
// operator>

// clang-format off
TINY_OPTIONAL_IMPL_COMPARE_BETWEEN_OPTIONALS(
  >, 
  return lhs.has_value() && (!rhs.has_value() || *lhs > *rhs);
)
// clang-format on

namespace impl
{
  template <class D1, class F1>
  constexpr bool operator>(TinyOptionalImpl<D1, F1> const & lhs, std::nullopt_t)
  {
    return lhs.has_value();
  }

  template <class D1, class F1>
  constexpr bool operator>(std::nullopt_t, TinyOptionalImpl<D1, F1> const &)
  {
    return false;
  }

  template <class D1, class F1, class U>
  constexpr std::enable_if_t<EnableComparisonWithValue<U>(nullptr), bool> operator>(
      TinyOptionalImpl<D1, F1> const & lhs,
      U const & rhs)
  {
    return lhs.has_value() ? *lhs > rhs : false;
  }

  template <class U, class D1, class F1>
  constexpr std::enable_if_t<EnableComparisonWithValue<U>(nullptr), bool> operator>(
      U const & lhs,
      TinyOptionalImpl<D1, F1> const & rhs)
  {
    return rhs.has_value() ? lhs > *rhs : true;
  }
} // namespace impl


//-----------------------
// operator>=

// clang-format off
TINY_OPTIONAL_IMPL_COMPARE_BETWEEN_OPTIONALS(
  >=, 
  return !rhs.has_value() || (lhs.has_value() && *lhs >= *rhs);
)
// clang-format on

namespace impl
{
  template <class D1, class F1>
  constexpr bool operator>=(TinyOptionalImpl<D1, F1> const &, std::nullopt_t)
  {
    return true;
  }

  template <class D1, class F1>
  constexpr bool operator>=(std::nullopt_t, TinyOptionalImpl<D1, F1> const & rhs)
  {
    return !rhs.has_value();
  }

  template <class D1, class F1, class U>
  constexpr std::enable_if_t<EnableComparisonWithValue<U>(nullptr), bool> operator>=(
      TinyOptionalImpl<D1, F1> const & lhs,
      U const & rhs)
  {
    return lhs.has_value() ? *lhs >= rhs : false;
  }

  template <class U, class D1, class F1>
  constexpr std::enable_if_t<EnableComparisonWithValue<U>(nullptr), bool> operator>=(
      U const & lhs,
      TinyOptionalImpl<D1, F1> const & rhs)
  {
    return rhs.has_value() ? lhs >= *rhs : true;
  }
} // namespace impl

} // namespace tiny


//====================================================================================
// std::hash specializations
//====================================================================================

namespace std
{
// clang-format off
template <class StoredTypeDecomposition, class FlagManipulator>
struct hash<
  tiny::impl::EnableHashHelper<
    tiny::impl::TinyOptionalImpl<StoredTypeDecomposition, FlagManipulator>,
    typename StoredTypeDecomposition::PayloadType
  >
>
{
  size_t operator()(tiny::impl::TinyOptionalImpl<StoredTypeDecomposition, FlagManipulator> const & o) const
  {
    return o.has_value() ? hash<std::remove_const_t<typename StoredTypeDecomposition::PayloadType>>{}(*o) : 0;
  }
};

  
template <class PayloadType, auto emptyValueOrMemPtr, auto irrelevantOrEmptyValue>
struct hash<
  tiny::impl::EnableHashHelper<
    tiny::optional<PayloadType, emptyValueOrMemPtr, irrelevantOrEmptyValue>,
    PayloadType
  >
>
{
  size_t operator()(tiny::optional<PayloadType, emptyValueOrMemPtr, irrelevantOrEmptyValue> const & o) const
  {
    return o.has_value() ? hash<std::remove_const_t<PayloadType>>{}(*o) : 0;
  }
};

// clang-format on

} // namespace std
