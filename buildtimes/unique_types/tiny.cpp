#include "tiny/optional.h"

struct S0
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S1
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S2
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S3
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S4
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S5
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S6
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S7
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S8
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S9
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S10
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S11
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S12
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S13
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S14
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S15
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S16
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S17
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S18
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S19
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S20
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S21
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S22
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S23
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S24
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S25
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S26
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S27
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S28
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S29
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S30
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S31
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S32
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S33
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S34
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S35
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S36
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S37
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S38
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S39
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S40
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S41
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S42
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S43
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S44
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S45
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S46
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S47
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S48
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S49
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S50
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S51
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S52
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S53
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S54
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S55
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S56
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S57
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S58
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S59
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S60
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S61
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S62
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S63
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S64
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S65
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S66
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S67
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S68
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S69
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S70
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S71
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S72
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S73
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S74
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S75
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S76
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S77
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S78
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S79
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S80
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S81
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S82
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S83
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S84
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S85
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S86
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S87
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S88
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S89
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S90
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S91
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S92
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S93
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S94
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S95
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S96
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S97
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S98
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S99
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S100
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S101
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S102
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S103
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S104
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S105
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S106
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S107
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S108
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S109
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S110
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S111
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S112
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S113
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S114
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S115
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S116
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S117
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S118
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S119
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S120
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S121
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S122
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S123
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S124
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S125
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S126
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S127
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S128
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S129
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S130
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S131
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S132
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S133
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S134
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S135
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S136
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S137
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S138
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S139
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S140
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S141
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S142
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S143
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S144
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S145
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S146
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S147
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S148
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S149
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S150
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S151
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S152
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S153
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S154
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S155
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S156
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S157
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S158
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S159
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S160
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S161
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S162
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S163
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S164
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S165
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S166
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S167
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S168
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S169
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S170
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S171
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S172
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S173
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S174
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S175
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S176
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S177
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S178
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S179
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S180
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S181
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S182
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S183
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S184
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S185
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S186
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S187
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S188
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S189
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S190
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S191
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S192
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S193
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S194
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S195
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S196
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S197
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S198
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S199
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S200
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S201
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S202
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S203
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S204
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S205
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S206
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S207
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S208
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S209
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S210
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S211
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S212
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S213
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S214
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S215
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S216
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S217
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S218
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S219
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S220
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S221
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S222
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S223
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S224
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S225
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S226
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S227
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S228
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S229
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S230
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S231
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S232
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S233
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S234
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S235
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S236
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S237
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S238
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S239
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S240
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S241
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S242
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S243
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S244
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S245
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S246
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S247
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S248
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S249
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S250
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S251
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S252
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S253
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S254
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S255
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S256
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S257
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S258
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S259
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S260
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S261
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S262
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S263
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S264
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S265
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S266
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S267
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S268
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S269
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S270
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S271
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S272
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S273
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S274
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S275
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S276
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S277
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S278
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S279
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S280
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S281
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S282
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S283
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S284
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S285
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S286
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S287
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S288
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S289
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S290
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S291
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S292
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S293
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S294
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S295
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S296
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S297
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S298
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S299
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S300
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S301
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S302
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S303
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S304
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S305
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S306
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S307
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S308
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S309
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S310
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S311
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S312
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S313
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S314
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S315
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S316
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S317
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S318
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S319
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S320
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S321
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S322
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S323
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S324
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S325
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S326
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S327
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S328
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S329
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S330
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S331
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S332
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S333
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S334
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S335
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S336
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S337
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S338
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S339
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S340
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S341
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S342
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S343
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S344
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S345
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S346
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S347
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S348
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S349
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S350
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S351
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S352
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S353
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S354
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S355
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S356
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S357
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S358
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S359
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S360
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S361
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S362
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S363
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S364
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S365
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S366
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S367
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S368
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S369
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S370
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S371
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S372
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S373
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S374
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S375
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S376
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S377
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S378
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S379
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S380
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S381
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S382
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S383
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S384
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S385
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S386
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S387
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S388
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S389
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S390
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S391
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S392
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S393
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S394
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S395
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S396
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S397
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S398
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S399
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S400
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S401
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S402
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S403
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S404
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S405
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S406
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S407
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S408
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S409
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S410
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S411
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S412
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S413
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S414
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S415
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S416
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S417
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S418
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S419
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S420
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S421
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S422
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S423
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S424
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S425
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S426
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S427
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S428
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S429
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S430
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S431
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S432
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S433
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S434
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S435
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S436
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S437
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S438
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S439
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S440
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S441
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S442
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S443
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S444
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S445
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S446
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S447
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S448
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S449
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S450
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S451
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S452
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S453
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S454
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S455
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S456
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S457
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S458
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S459
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S460
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S461
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S462
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S463
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S464
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S465
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S466
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S467
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S468
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S469
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S470
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S471
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S472
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S473
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S474
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S475
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S476
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S477
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S478
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S479
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S480
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S481
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S482
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S483
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S484
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S485
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S486
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S487
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S488
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S489
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S490
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S491
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S492
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S493
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S494
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S495
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S496
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S497
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S498
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

struct S499
{
    struct impl{};

    void test() {
        o = std::nullopt;
        [[maybe_unused]] bool v1 = o.has_value();
        o = impl{};
        [[maybe_unused]] auto v2 = o.value();
        v2 = *o;
        o.reset();
        o.emplace(v2);
        [[maybe_unused]] bool v3 = static_cast<bool>(o);
    }
    
    tiny::optional<impl> o;
};

int main()
{
  S0 s0;  s0.test();
  S1 s1;  s1.test();
  S2 s2;  s2.test();
  S3 s3;  s3.test();
  S4 s4;  s4.test();
  S5 s5;  s5.test();
  S6 s6;  s6.test();
  S7 s7;  s7.test();
  S8 s8;  s8.test();
  S9 s9;  s9.test();
  S10 s10;  s10.test();
  S11 s11;  s11.test();
  S12 s12;  s12.test();
  S13 s13;  s13.test();
  S14 s14;  s14.test();
  S15 s15;  s15.test();
  S16 s16;  s16.test();
  S17 s17;  s17.test();
  S18 s18;  s18.test();
  S19 s19;  s19.test();
  S20 s20;  s20.test();
  S21 s21;  s21.test();
  S22 s22;  s22.test();
  S23 s23;  s23.test();
  S24 s24;  s24.test();
  S25 s25;  s25.test();
  S26 s26;  s26.test();
  S27 s27;  s27.test();
  S28 s28;  s28.test();
  S29 s29;  s29.test();
  S30 s30;  s30.test();
  S31 s31;  s31.test();
  S32 s32;  s32.test();
  S33 s33;  s33.test();
  S34 s34;  s34.test();
  S35 s35;  s35.test();
  S36 s36;  s36.test();
  S37 s37;  s37.test();
  S38 s38;  s38.test();
  S39 s39;  s39.test();
  S40 s40;  s40.test();
  S41 s41;  s41.test();
  S42 s42;  s42.test();
  S43 s43;  s43.test();
  S44 s44;  s44.test();
  S45 s45;  s45.test();
  S46 s46;  s46.test();
  S47 s47;  s47.test();
  S48 s48;  s48.test();
  S49 s49;  s49.test();
  S50 s50;  s50.test();
  S51 s51;  s51.test();
  S52 s52;  s52.test();
  S53 s53;  s53.test();
  S54 s54;  s54.test();
  S55 s55;  s55.test();
  S56 s56;  s56.test();
  S57 s57;  s57.test();
  S58 s58;  s58.test();
  S59 s59;  s59.test();
  S60 s60;  s60.test();
  S61 s61;  s61.test();
  S62 s62;  s62.test();
  S63 s63;  s63.test();
  S64 s64;  s64.test();
  S65 s65;  s65.test();
  S66 s66;  s66.test();
  S67 s67;  s67.test();
  S68 s68;  s68.test();
  S69 s69;  s69.test();
  S70 s70;  s70.test();
  S71 s71;  s71.test();
  S72 s72;  s72.test();
  S73 s73;  s73.test();
  S74 s74;  s74.test();
  S75 s75;  s75.test();
  S76 s76;  s76.test();
  S77 s77;  s77.test();
  S78 s78;  s78.test();
  S79 s79;  s79.test();
  S80 s80;  s80.test();
  S81 s81;  s81.test();
  S82 s82;  s82.test();
  S83 s83;  s83.test();
  S84 s84;  s84.test();
  S85 s85;  s85.test();
  S86 s86;  s86.test();
  S87 s87;  s87.test();
  S88 s88;  s88.test();
  S89 s89;  s89.test();
  S90 s90;  s90.test();
  S91 s91;  s91.test();
  S92 s92;  s92.test();
  S93 s93;  s93.test();
  S94 s94;  s94.test();
  S95 s95;  s95.test();
  S96 s96;  s96.test();
  S97 s97;  s97.test();
  S98 s98;  s98.test();
  S99 s99;  s99.test();
  S100 s100;  s100.test();
  S101 s101;  s101.test();
  S102 s102;  s102.test();
  S103 s103;  s103.test();
  S104 s104;  s104.test();
  S105 s105;  s105.test();
  S106 s106;  s106.test();
  S107 s107;  s107.test();
  S108 s108;  s108.test();
  S109 s109;  s109.test();
  S110 s110;  s110.test();
  S111 s111;  s111.test();
  S112 s112;  s112.test();
  S113 s113;  s113.test();
  S114 s114;  s114.test();
  S115 s115;  s115.test();
  S116 s116;  s116.test();
  S117 s117;  s117.test();
  S118 s118;  s118.test();
  S119 s119;  s119.test();
  S120 s120;  s120.test();
  S121 s121;  s121.test();
  S122 s122;  s122.test();
  S123 s123;  s123.test();
  S124 s124;  s124.test();
  S125 s125;  s125.test();
  S126 s126;  s126.test();
  S127 s127;  s127.test();
  S128 s128;  s128.test();
  S129 s129;  s129.test();
  S130 s130;  s130.test();
  S131 s131;  s131.test();
  S132 s132;  s132.test();
  S133 s133;  s133.test();
  S134 s134;  s134.test();
  S135 s135;  s135.test();
  S136 s136;  s136.test();
  S137 s137;  s137.test();
  S138 s138;  s138.test();
  S139 s139;  s139.test();
  S140 s140;  s140.test();
  S141 s141;  s141.test();
  S142 s142;  s142.test();
  S143 s143;  s143.test();
  S144 s144;  s144.test();
  S145 s145;  s145.test();
  S146 s146;  s146.test();
  S147 s147;  s147.test();
  S148 s148;  s148.test();
  S149 s149;  s149.test();
  S150 s150;  s150.test();
  S151 s151;  s151.test();
  S152 s152;  s152.test();
  S153 s153;  s153.test();
  S154 s154;  s154.test();
  S155 s155;  s155.test();
  S156 s156;  s156.test();
  S157 s157;  s157.test();
  S158 s158;  s158.test();
  S159 s159;  s159.test();
  S160 s160;  s160.test();
  S161 s161;  s161.test();
  S162 s162;  s162.test();
  S163 s163;  s163.test();
  S164 s164;  s164.test();
  S165 s165;  s165.test();
  S166 s166;  s166.test();
  S167 s167;  s167.test();
  S168 s168;  s168.test();
  S169 s169;  s169.test();
  S170 s170;  s170.test();
  S171 s171;  s171.test();
  S172 s172;  s172.test();
  S173 s173;  s173.test();
  S174 s174;  s174.test();
  S175 s175;  s175.test();
  S176 s176;  s176.test();
  S177 s177;  s177.test();
  S178 s178;  s178.test();
  S179 s179;  s179.test();
  S180 s180;  s180.test();
  S181 s181;  s181.test();
  S182 s182;  s182.test();
  S183 s183;  s183.test();
  S184 s184;  s184.test();
  S185 s185;  s185.test();
  S186 s186;  s186.test();
  S187 s187;  s187.test();
  S188 s188;  s188.test();
  S189 s189;  s189.test();
  S190 s190;  s190.test();
  S191 s191;  s191.test();
  S192 s192;  s192.test();
  S193 s193;  s193.test();
  S194 s194;  s194.test();
  S195 s195;  s195.test();
  S196 s196;  s196.test();
  S197 s197;  s197.test();
  S198 s198;  s198.test();
  S199 s199;  s199.test();
  S200 s200;  s200.test();
  S201 s201;  s201.test();
  S202 s202;  s202.test();
  S203 s203;  s203.test();
  S204 s204;  s204.test();
  S205 s205;  s205.test();
  S206 s206;  s206.test();
  S207 s207;  s207.test();
  S208 s208;  s208.test();
  S209 s209;  s209.test();
  S210 s210;  s210.test();
  S211 s211;  s211.test();
  S212 s212;  s212.test();
  S213 s213;  s213.test();
  S214 s214;  s214.test();
  S215 s215;  s215.test();
  S216 s216;  s216.test();
  S217 s217;  s217.test();
  S218 s218;  s218.test();
  S219 s219;  s219.test();
  S220 s220;  s220.test();
  S221 s221;  s221.test();
  S222 s222;  s222.test();
  S223 s223;  s223.test();
  S224 s224;  s224.test();
  S225 s225;  s225.test();
  S226 s226;  s226.test();
  S227 s227;  s227.test();
  S228 s228;  s228.test();
  S229 s229;  s229.test();
  S230 s230;  s230.test();
  S231 s231;  s231.test();
  S232 s232;  s232.test();
  S233 s233;  s233.test();
  S234 s234;  s234.test();
  S235 s235;  s235.test();
  S236 s236;  s236.test();
  S237 s237;  s237.test();
  S238 s238;  s238.test();
  S239 s239;  s239.test();
  S240 s240;  s240.test();
  S241 s241;  s241.test();
  S242 s242;  s242.test();
  S243 s243;  s243.test();
  S244 s244;  s244.test();
  S245 s245;  s245.test();
  S246 s246;  s246.test();
  S247 s247;  s247.test();
  S248 s248;  s248.test();
  S249 s249;  s249.test();
  S250 s250;  s250.test();
  S251 s251;  s251.test();
  S252 s252;  s252.test();
  S253 s253;  s253.test();
  S254 s254;  s254.test();
  S255 s255;  s255.test();
  S256 s256;  s256.test();
  S257 s257;  s257.test();
  S258 s258;  s258.test();
  S259 s259;  s259.test();
  S260 s260;  s260.test();
  S261 s261;  s261.test();
  S262 s262;  s262.test();
  S263 s263;  s263.test();
  S264 s264;  s264.test();
  S265 s265;  s265.test();
  S266 s266;  s266.test();
  S267 s267;  s267.test();
  S268 s268;  s268.test();
  S269 s269;  s269.test();
  S270 s270;  s270.test();
  S271 s271;  s271.test();
  S272 s272;  s272.test();
  S273 s273;  s273.test();
  S274 s274;  s274.test();
  S275 s275;  s275.test();
  S276 s276;  s276.test();
  S277 s277;  s277.test();
  S278 s278;  s278.test();
  S279 s279;  s279.test();
  S280 s280;  s280.test();
  S281 s281;  s281.test();
  S282 s282;  s282.test();
  S283 s283;  s283.test();
  S284 s284;  s284.test();
  S285 s285;  s285.test();
  S286 s286;  s286.test();
  S287 s287;  s287.test();
  S288 s288;  s288.test();
  S289 s289;  s289.test();
  S290 s290;  s290.test();
  S291 s291;  s291.test();
  S292 s292;  s292.test();
  S293 s293;  s293.test();
  S294 s294;  s294.test();
  S295 s295;  s295.test();
  S296 s296;  s296.test();
  S297 s297;  s297.test();
  S298 s298;  s298.test();
  S299 s299;  s299.test();
  S300 s300;  s300.test();
  S301 s301;  s301.test();
  S302 s302;  s302.test();
  S303 s303;  s303.test();
  S304 s304;  s304.test();
  S305 s305;  s305.test();
  S306 s306;  s306.test();
  S307 s307;  s307.test();
  S308 s308;  s308.test();
  S309 s309;  s309.test();
  S310 s310;  s310.test();
  S311 s311;  s311.test();
  S312 s312;  s312.test();
  S313 s313;  s313.test();
  S314 s314;  s314.test();
  S315 s315;  s315.test();
  S316 s316;  s316.test();
  S317 s317;  s317.test();
  S318 s318;  s318.test();
  S319 s319;  s319.test();
  S320 s320;  s320.test();
  S321 s321;  s321.test();
  S322 s322;  s322.test();
  S323 s323;  s323.test();
  S324 s324;  s324.test();
  S325 s325;  s325.test();
  S326 s326;  s326.test();
  S327 s327;  s327.test();
  S328 s328;  s328.test();
  S329 s329;  s329.test();
  S330 s330;  s330.test();
  S331 s331;  s331.test();
  S332 s332;  s332.test();
  S333 s333;  s333.test();
  S334 s334;  s334.test();
  S335 s335;  s335.test();
  S336 s336;  s336.test();
  S337 s337;  s337.test();
  S338 s338;  s338.test();
  S339 s339;  s339.test();
  S340 s340;  s340.test();
  S341 s341;  s341.test();
  S342 s342;  s342.test();
  S343 s343;  s343.test();
  S344 s344;  s344.test();
  S345 s345;  s345.test();
  S346 s346;  s346.test();
  S347 s347;  s347.test();
  S348 s348;  s348.test();
  S349 s349;  s349.test();
  S350 s350;  s350.test();
  S351 s351;  s351.test();
  S352 s352;  s352.test();
  S353 s353;  s353.test();
  S354 s354;  s354.test();
  S355 s355;  s355.test();
  S356 s356;  s356.test();
  S357 s357;  s357.test();
  S358 s358;  s358.test();
  S359 s359;  s359.test();
  S360 s360;  s360.test();
  S361 s361;  s361.test();
  S362 s362;  s362.test();
  S363 s363;  s363.test();
  S364 s364;  s364.test();
  S365 s365;  s365.test();
  S366 s366;  s366.test();
  S367 s367;  s367.test();
  S368 s368;  s368.test();
  S369 s369;  s369.test();
  S370 s370;  s370.test();
  S371 s371;  s371.test();
  S372 s372;  s372.test();
  S373 s373;  s373.test();
  S374 s374;  s374.test();
  S375 s375;  s375.test();
  S376 s376;  s376.test();
  S377 s377;  s377.test();
  S378 s378;  s378.test();
  S379 s379;  s379.test();
  S380 s380;  s380.test();
  S381 s381;  s381.test();
  S382 s382;  s382.test();
  S383 s383;  s383.test();
  S384 s384;  s384.test();
  S385 s385;  s385.test();
  S386 s386;  s386.test();
  S387 s387;  s387.test();
  S388 s388;  s388.test();
  S389 s389;  s389.test();
  S390 s390;  s390.test();
  S391 s391;  s391.test();
  S392 s392;  s392.test();
  S393 s393;  s393.test();
  S394 s394;  s394.test();
  S395 s395;  s395.test();
  S396 s396;  s396.test();
  S397 s397;  s397.test();
  S398 s398;  s398.test();
  S399 s399;  s399.test();
  S400 s400;  s400.test();
  S401 s401;  s401.test();
  S402 s402;  s402.test();
  S403 s403;  s403.test();
  S404 s404;  s404.test();
  S405 s405;  s405.test();
  S406 s406;  s406.test();
  S407 s407;  s407.test();
  S408 s408;  s408.test();
  S409 s409;  s409.test();
  S410 s410;  s410.test();
  S411 s411;  s411.test();
  S412 s412;  s412.test();
  S413 s413;  s413.test();
  S414 s414;  s414.test();
  S415 s415;  s415.test();
  S416 s416;  s416.test();
  S417 s417;  s417.test();
  S418 s418;  s418.test();
  S419 s419;  s419.test();
  S420 s420;  s420.test();
  S421 s421;  s421.test();
  S422 s422;  s422.test();
  S423 s423;  s423.test();
  S424 s424;  s424.test();
  S425 s425;  s425.test();
  S426 s426;  s426.test();
  S427 s427;  s427.test();
  S428 s428;  s428.test();
  S429 s429;  s429.test();
  S430 s430;  s430.test();
  S431 s431;  s431.test();
  S432 s432;  s432.test();
  S433 s433;  s433.test();
  S434 s434;  s434.test();
  S435 s435;  s435.test();
  S436 s436;  s436.test();
  S437 s437;  s437.test();
  S438 s438;  s438.test();
  S439 s439;  s439.test();
  S440 s440;  s440.test();
  S441 s441;  s441.test();
  S442 s442;  s442.test();
  S443 s443;  s443.test();
  S444 s444;  s444.test();
  S445 s445;  s445.test();
  S446 s446;  s446.test();
  S447 s447;  s447.test();
  S448 s448;  s448.test();
  S449 s449;  s449.test();
  S450 s450;  s450.test();
  S451 s451;  s451.test();
  S452 s452;  s452.test();
  S453 s453;  s453.test();
  S454 s454;  s454.test();
  S455 s455;  s455.test();
  S456 s456;  s456.test();
  S457 s457;  s457.test();
  S458 s458;  s458.test();
  S459 s459;  s459.test();
  S460 s460;  s460.test();
  S461 s461;  s461.test();
  S462 s462;  s462.test();
  S463 s463;  s463.test();
  S464 s464;  s464.test();
  S465 s465;  s465.test();
  S466 s466;  s466.test();
  S467 s467;  s467.test();
  S468 s468;  s468.test();
  S469 s469;  s469.test();
  S470 s470;  s470.test();
  S471 s471;  s471.test();
  S472 s472;  s472.test();
  S473 s473;  s473.test();
  S474 s474;  s474.test();
  S475 s475;  s475.test();
  S476 s476;  s476.test();
  S477 s477;  s477.test();
  S478 s478;  s478.test();
  S479 s479;  s479.test();
  S480 s480;  s480.test();
  S481 s481;  s481.test();
  S482 s482;  s482.test();
  S483 s483;  s483.test();
  S484 s484;  s484.test();
  S485 s485;  s485.test();
  S486 s486;  s486.test();
  S487 s487;  s487.test();
  S488 s488;  s488.test();
  S489 s489;  s489.test();
  S490 s490;  s490.test();
  S491 s491;  s491.test();
  S492 s492;  s492.test();
  S493 s493;  s493.test();
  S494 s494;  s494.test();
  S495 s495;  s495.test();
  S496 s496;  s496.test();
  S497 s497;  s497.test();
  S498 s498;  s498.test();
  S499 s499;  s499.test();
}
