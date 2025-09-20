import csv
import re

class OneResult:
    def __init__(self, header: str, std_timing: float, tiny_timing: float):
        self.header = header
        self.std = std_timing # build time in seconds
        self.tiny = tiny_timing # build time in seconds
        self.tiny_to_std_ratio = tiny_timing / std_timing
        
        raw_flags = header.split(" ")
        assert(raw_flags[0] in ["g++", "clang++", "cl.exe"])
        self.compiler_and_flags = set(raw_flags)


class ParsedFile:
    def __init__(self, filename: str, encoding: str):
        with open(filename, 'r', encoding=encoding, newline='') as f:
            reader = csv.reader(f, delimiter=';')
            
            rows = []
            for r in reader:
                rows.append(r)
            assert(len(rows) == 3)

            self.headers: list[str] = rows[0]
            self.headers.pop(0)
            self.headers = [re.sub(" +", " ", h).strip() for h in self.headers]

            std_strings = rows[1]
            self.std_rows = [float(v) for v in std_strings if v != "std.cpp"]
            
            tiny_strings = rows[2]
            self.tiny_rows = [float(v) for v in tiny_strings if v != "tiny.cpp"]

            assert(len(self.headers) == len(self.std_rows))
            assert(len(self.headers) == len(self.tiny_rows))

            self.column_results: list[OneResult] = []
            for i in range(0, len(self.headers)):
                self.column_results.append(OneResult(self.headers[i], self.std_rows[i], self.tiny_rows[i]))


def find_result(compiler_and_flags: set[str], results: ParsedFile) -> OneResult:
    for r in results.column_results:
        if r.compiler_and_flags == compiler_and_flags:
            return r
    raise Exception(f"No result found for: {compiler_and_flags}")


linux = ParsedFile("result_linux.csv", "utf-8")
msvc = ParsedFile("result_msvc.csv", "utf-16")

NO_CONCEPT = "TINY_OPTIONAL_NO_TRIVIAL_SPECIAL_MEMBER_FUNCTIONS"


def write_result_for_cpp_standard(standard: str, filename: str):
    with open(filename, "w") as f:
        linux_relevant = [r for r in linux.column_results if NO_CONCEPT not in r.header and standard in r.header]
        msvc_relevant = [r for r in msvc.column_results if NO_CONCEPT not in r.header and standard in r.header]
        for r in linux_relevant:
            f.write(f"{r.header};{r.tiny_to_std_ratio}\n")
        for r in msvc_relevant:
            f.write(f"{r.header};{r.tiny_to_std_ratio}\n")


write_result_for_cpp_standard("c++17", "result_tiny_vs_std_cpp17.csv")
write_result_for_cpp_standard("c++20", "result_tiny_vs_std_cpp20.csv")


with open("result_tiny_concept_vs_no_concept.csv", "w") as f:
    clang_cpp20_dbg_flags = {"clang++", "-std=c++20"}
    clang_cpp20_dbg_with_concept = find_result(clang_cpp20_dbg_flags, linux)
    clang_cpp20_dbg_no_concept = find_result(clang_cpp20_dbg_flags | {f"-D{NO_CONCEPT}"}, linux)
    f.write(f"clang++ -std=c++20 debug;{clang_cpp20_dbg_no_concept.tiny / clang_cpp20_dbg_with_concept.tiny}\n")

    clang_cpp20_rel_flags = {"clang++", "-std=c++20", "-O3", "-DNDEBUG"}
    clang_cpp20_rel_with_concept = find_result(clang_cpp20_rel_flags, linux)
    clang_cpp20_rel_no_concept = find_result(clang_cpp20_rel_flags | {f"-D{NO_CONCEPT}"}, linux)
    f.write(f"clang++ -std:c++20 release;{clang_cpp20_rel_no_concept.tiny / clang_cpp20_rel_with_concept.tiny}\n")

    clang_cpp20_libcpp_dbg_flags = {"clang++", "-std=c++20", "-stdlib=libc++"}
    clang_cpp20_libcpp_dbg_with_concept = find_result(clang_cpp20_libcpp_dbg_flags, linux)
    clang_cpp20_libcpp_dbg_no_concept = find_result(clang_cpp20_libcpp_dbg_flags | {f"-D{NO_CONCEPT}"}, linux)
    f.write(f"clang++ -std=c++20 libc++ debug;{clang_cpp20_libcpp_dbg_no_concept.tiny / clang_cpp20_libcpp_dbg_with_concept.tiny}\n")

    clang_cpp20_libcpp_rel_flags = {"clang++", "-std=c++20", "-stdlib=libc++", "-O3", "-DNDEBUG"}
    clang_cpp20_libcpp_rel_with_concept = find_result(clang_cpp20_libcpp_rel_flags, linux)
    clang_cpp20_libcpp_rel_no_concept = find_result(clang_cpp20_libcpp_rel_flags | {f"-D{NO_CONCEPT}"}, linux)
    f.write(f"clang++ -std:c++20 libc++ release;{clang_cpp20_libcpp_rel_no_concept.tiny / clang_cpp20_libcpp_rel_with_concept.tiny}\n")

    gcc_cpp20_dbg_flags = {"g++", "-std=c++20"}
    gcc_cpp20_dbg_with_concept = find_result(gcc_cpp20_dbg_flags, linux)
    gcc_cpp20_dbg_no_concept = find_result(gcc_cpp20_dbg_flags | {f"-D{NO_CONCEPT}"}, linux)
    f.write(f"g++ -std=c++20 debug;{gcc_cpp20_dbg_no_concept.tiny / gcc_cpp20_dbg_with_concept.tiny}\n")

    gcc_cpp20_rel_flags = {"g++", "-std=c++20", "-O3", "-DNDEBUG"}
    gcc_cpp20_rel_with_concept = find_result(gcc_cpp20_rel_flags, linux)
    gcc_cpp20_rel_no_concept = find_result(gcc_cpp20_rel_flags | {f"-D{NO_CONCEPT}"}, linux)
    f.write(f"g++ -std=c++20 release;{gcc_cpp20_rel_no_concept.tiny / gcc_cpp20_rel_with_concept.tiny}\n")

    msvc_cpp20_dbg_flags = {"cl.exe", "/std:c++20"}
    msvc_cpp20_dbg_with_concept = find_result(msvc_cpp20_dbg_flags, msvc)
    msvc_cpp20_dbg_no_concept = find_result(msvc_cpp20_dbg_flags | {f"/D{NO_CONCEPT}"}, msvc)
    f.write(f"cl.exe /std:c++20 debug;{msvc_cpp20_dbg_no_concept.tiny / msvc_cpp20_dbg_with_concept.tiny}\n")

    msvc_cpp20_rel_flags = {"cl.exe", "/std:c++20", "/O2", "/DNDEBUG"}
    msvc_cpp20_rel_with_concept = find_result(msvc_cpp20_rel_flags, msvc)
    msvc_cpp20_rel_no_concept = find_result(msvc_cpp20_rel_flags | {f"/D{NO_CONCEPT}"}, msvc)
    f.write(f"cl.exe /std:c++20 release;{msvc_cpp20_rel_no_concept.tiny / msvc_cpp20_rel_with_concept.tiny}\n")
