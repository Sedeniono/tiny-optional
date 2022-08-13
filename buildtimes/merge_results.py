import csv


class ParsedFile:
    def __init__(self, filename, encoding):
        with open(filename, 'r', encoding=encoding, newline='') as f:
            reader = csv.reader(f, delimiter=';')
            
            rows = []
            for r in reader:
                rows.append(r)
            assert(len(rows) == 3)

            self.headers = rows[0]
            self.headers.pop(0)

            std_strings = rows[1]
            self.std = [float(v) for v in std_strings if v != "std.cpp"]
            
            tiny_strings = rows[2]
            self.tiny = [float(v) for v in tiny_strings if v != "tiny.cpp"]

            assert(len(self.headers) == len(self.std))
            assert(len(self.headers) == len(self.tiny))


linux = ParsedFile("result_linux.csv", "utf-8")
msvc = ParsedFile("result_msvc.csv", "utf-16")

with open("result_merged.csv", "w") as f:
    for i in range(0, len(linux.headers)):
        ratio = linux.tiny[i] / linux.std[i]
        f.write(f"{linux.headers[i]};{ratio}\n")
    for i in range(0, len(msvc.headers)):
        ratio = msvc.tiny[i] / msvc.std[i]
        f.write(f"{msvc.headers[i]};{ratio}\n")

