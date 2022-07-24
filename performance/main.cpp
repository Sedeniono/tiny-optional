#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <optional>
#include <random>
#include <sstream>
#include <string>
#include <tiny/optional.h>
#include <vector>

#if defined(__clang__)
  #define TINY_OPTIONAL_CLANG_BUILD
#elif defined(__GNUC__) || defined(__GNUG__)
  #define TINY_OPTIONAL_GCC_BUILD
#elif defined(_MSC_VER)
  #define TINY_OPTIONAL_MSVC_BUILD
#else
  #error Unknown compiler
#endif


#if defined(TINY_OPTIONAL_CLANG_BUILD) || defined(TINY_OPTIONAL_GCC_BUILD)
  #define TINY_OPTIONAL_NO_INLINE __attribute__((noinline))
#elif defined(TINY_OPTIONAL_MSVC_BUILD)
  #define TINY_OPTIONAL_NO_INLINE __declspec(noinline)
#else
  #error Unknown compiler
#endif
 

template <class T>
constexpr T Sqr(T v)
{
  return v*v;
}


template <class Optional>
class Tester
{
public:
  explicit Tester(size_t modulo, size_t numValues, size_t numIterations)
    : modulo(modulo)
    , numIterations(numIterations)
  {
    size_t const totalSize = numValues * sizeof(WeirdVector);
    std::cout << "\tCreating vector with " << numValues << " elements (" << sizeof(WeirdVector)
              << " bytes per element, total " << totalSize << "B=" << totalSize / 1024
              << "kB=" << totalSize / (1024 * 1024) << "MB)" << std::endl;
    auto const start = std::chrono::steady_clock::now();

    std::mt19937 rng(42);
    values.reserve(numValues);
    size_t numNullopts = 0;
    for (size_t i = 0; i < numValues; ++i) {
      auto const x = GenerateRandomOptional(rng);
      auto const y = GenerateRandomOptional(rng);
      auto const z = GenerateRandomOptional(rng);
      values.emplace_back(WeirdVector{x, y, z, std::nullopt});

      numNullopts += !x;
      numNullopts += !y;
      numNullopts += !z;
    }

    size_t const numOptionals = 3 * numValues;
    nulloptRatio = static_cast<double>(numNullopts) / numOptionals;

    double const duration = std::chrono::duration<double>(std::chrono::steady_clock::now() - start).count();
    std::cout << "\tCreated data in " << duration << "s, " << nulloptRatio * 100.0 << "% are nullopt" << std::endl;
  }

  double TestAndGetDuration()
  {
    auto const start = std::chrono::steady_clock::now();

    typename Optional::value_type totalLength = 0;
    for (size_t i = 0; i < numIterations; ++i) {
      totalLength += RunRawTest();
    }

    double const duration = std::chrono::duration<double>(std::chrono::steady_clock::now() - start).count();
    std::cout << "\tTesting finished. Took " << duration << "s. TotalLength = " << totalLength << std::endl;

    return duration;
  }

  double GetNulloptRatio() const
  {
    return nulloptRatio;
  }

private:
  struct WeirdVector
  {
    Optional x, y, z;
    Optional length2;
  };

  Optional GenerateRandomOptional(std::mt19937 & rng)
  {
    auto const value = rng();
    if (value % modulo == 0) {
      return std::nullopt;
    }
    else {
      return value;
    }
  }

  TINY_OPTIONAL_NO_INLINE auto RunRawTest()
  {
    for (WeirdVector & vec : values) {
      if (vec.x || vec.y || vec.z) {
        vec.length2.emplace(Sqr(vec.x.value_or(0)) + Sqr(vec.y.value_or(0)) + Sqr(vec.z.value_or(0)));
      }
    }

    typename Optional::value_type totalLength = 0;
    for (WeirdVector & vec : values) {
      totalLength += vec.length2.value_or(0);
    }
    return totalLength;
  }

  size_t const modulo;
  size_t const numIterations;
  std::vector<WeirdVector> values;
  double nulloptRatio;
};


struct Result
{
  size_t modulo = 0;
  size_t numValues = 0;
  double nulloptRatio = std::numeric_limits<double>::quiet_NaN();
  double durationTiny = std::numeric_limits<double>::quiet_NaN();
  double durationStd = std::numeric_limits<double>::quiet_NaN();
};


Result RunOneTest(size_t modulo, size_t numValues, size_t numIterations)
{
  Result result;
  result.modulo = modulo;
  result.numValues = numValues;

  {
    std::cout << "tiny::optional:" << std::endl;
    Tester<tiny::optional<double>> tinyTest(modulo, numValues, numIterations);
    result.nulloptRatio = tinyTest.GetNulloptRatio();
    result.durationTiny = tinyTest.TestAndGetDuration();
  }
  {
    std::cout << "std::optional:" << std::endl;
    Tester<std::optional<double>> stdTest(modulo, numValues, numIterations);
    result.durationStd = stdTest.TestAndGetDuration();
  }

  return result;
}


std::vector<Result> RunMultipleTests(
    std::vector<size_t> modulos,
    std::vector<std::pair<size_t /*numValues*/, size_t /*numIterations*/>> numValues)
{
  static constexpr size_t cAdditionalIterMultiplier = 2;

  std::vector<Result> results;
  results.reserve(modulos.size());
  for (size_t const modulo : modulos) {
    for (auto const & [numVals, numIterationsBase] : numValues) {
      size_t const numIterations = numIterationsBase * cAdditionalIterMultiplier;
      std::cout << "====== modulo=" << modulo << ", numVals=" << numVals << ", numIter=" << numIterations
                << " ======" << std::endl;
      results.emplace_back(RunOneTest(modulo, numVals, numIterations));
    }
  }
  return results;
}


std::string CreatePrintableResultString(std::vector<Result> const & results)
{
  std::stringstream o;
  o << std::setw(6) << "Modulo"
    << "  " << std::setw(10) << "numVals"
    << "  " << std::setw(9) << "Nullopts"
    << "  " << std::setw(8) << "std[s]"
    << "  " << std::setw(8) << "tiny[s]"
    << "  " << std::setw(8) << "std/tiny" << std::endl;
  for (Result const & result : results) {
    o << std::setw(6) << result.modulo << "  " << std::setw(10) << result.numValues << "  " << std::setprecision(3)
      << std::setw(9) << result.nulloptRatio << "  " << std::setprecision(5) << std::setw(8) << result.durationStd
      << "  " << std::setw(8) << result.durationTiny << "  " << std::setprecision(4) << std::setw(8)
      << result.durationStd / result.durationTiny << std::endl;
  }
  return o.str();
}


std::string GetCompilerName()
{
#if defined(TINY_OPTIONAL_CLANG_BUILD)
  return "clang";
#elif defined(TINY_OPTIONAL_GCC_BUILD)
  return "gcc";
#elif defined(TINY_OPTIONAL_MSVC_BUILD)
  return "msvc";
#else
  #error Unknown compiler
#endif
}


int main()
{
  std::string const compilerName = GetCompilerName();
  std::cout << "Running tests on compiler: " << compilerName << std::endl;

  // clang-format off
  std::vector<Result> results = RunMultipleTests(
      {8192}, // Most optionals have a value ==> branch prediction is correct in most cases
      {
          {1, 3000000000}, // tiny and std fit into cache line
          {2, 1000000000}, // 2 elements: All tiny fit into cache line, but not std

          {3, 900000000},
          {4, 600000000},
          {8, 400000000},
          {32, 70000000},
          {128, 20000000},
          {512, 4000000},
          {1024, 2000000},
          {2048, 1000000},
          {4096, 600000}, // All tiny and std fit into L1
          {8192, 300000}, // All tiny just fit into L1 but not std

          {16384, 200000}, // All tiny and std fit into L2
          {32768, 100000}, // All tiny fit just into L2 but not std

          {65536, 40000}, // Neither all tiny nor std fit into L2
          {80000, 35000},
          {98304, 30000},
          {110000, 25000},
          {131072, 20000}, // All tiny and std just fit into L3

          {196608, 15000}, // All tiny fit into L3 but not std
          {262144, 10000}, // All tiny fit just into L3 but not std

          {393216, 7500}, // Neither all tiny nor std fit into L3
          {524288, 5000},
          {786432, 2500},
          {1048576, 1000}, // Neither all tiny nor std fit into L3
          {2097152, 500}, // Neither all tiny nor std fit into L3
          {5000000, 250},
          {10000000, 100}
      });
  // clang-format on

  std::cout << std::endl;
  std::cout << "========= Summary for " << compilerName << " =========" << std::endl;
  std::string const resultsStr = CreatePrintableResultString(results);
  std::cout << resultsStr;

  std::ofstream out("results_" + GetCompilerName() + ".dat");
  out << resultsStr;
}


