import os


def get_class_name(id):
    return "S" + str(id)

     

def get_class_with_method_and_unique_type(id, optional_type):
    class_name = get_class_name(id)
    code = f'''
struct {class_name}
{{
    struct impl{{}};

    void test() {{
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{{}};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }}
    
    {optional_type}<impl> o;
}};
'''
    return code


def get_class_with_method_and_double(id, optional_type):
    class_name = get_class_name(id)
    code = f'''
struct {class_name}
{{
    void test() {{
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = 42.0;
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }}
    
    {optional_type}<double> o;
}};
'''
    return code


def get_class_no_method(id, optional_type):
    class_name = get_class_name(id)
    code = f'''
struct {class_name}
{{
    {optional_type}<double> o;
}};
'''
    return code


def write_code(file, count, header, optional_type, use_unique_type):
    file.write(f"#include {header}\n")
    for i in range(0, count):
        if use_unique_type:
            file.write(get_class_with_method_and_unique_type(i, optional_type))
        else:
            file.write(get_class_with_method_and_double(i, optional_type))
    file.write("\n")
    file.write("int main()\n{\n")
    for i in range(0, count):
        file.write(f"  {get_class_name(i)} s{str(i)};  s{str(i)}.test();\n")
    file.write("}\n")


def generate_all(num_classes, use_unique_type):
    with open("std.cpp", "w") as f:
        write_code(f, num_classes, "<optional>", "std::optional", use_unique_type)

    with open("tiny.cpp", "w") as f:
        write_code(f, num_classes, "\"tiny/optional.h\"", "tiny::optional", use_unique_type)


# Generates classes with optional<double> members.
#generate_all(1000, False)

# Generates classes with optional<impl> members, where impl is a class within each class.
generate_all(500, True)
