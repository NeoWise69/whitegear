
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_STRING_HPP
#define WHITEGEAR_STRING_HPP

#include <core/typedefs.hpp>
#include "string_view.hpp"
#include "core/ref_counted.hpp"

namespace wg {
    struct string_impl;

    class string {
    public:
        virtual ~string() noexcept;
        string() noexcept;

        string(const string&);
        string(string&&) noexcept;
        string& operator=(const string&);
        string& operator=(string&&) noexcept;

        string(const char* s) noexcept;
        string& operator=(const char* s) noexcept;
        string(const char* s, u64 len) noexcept;
        string(const string_view& sv) noexcept;

        // access/write
        string& append(const char* s) noexcept;
        string& append(const char* s, u64 len) noexcept;
        string& append(const char c, u64 len = 1) noexcept;
        string& append(const string& o) noexcept;
        string& append(string&& o) noexcept;

        string& operator+=(const char* s) noexcept;
        string& operator+=(const char c) noexcept;
        string& operator+=(const string& o) noexcept;
        string& operator+=(string&& o) noexcept;

        const char& operator[](i64 i) const;
        char& operator[](i64 i);
        // !access/write

        // getters
        const u64 size() const noexcept;
        const u64 capacity() const noexcept;
        bool empty() const noexcept;
        const char* c_str() const noexcept;
        char* data() const noexcept;
        // !getters

        // iterator operators
        char* begin() noexcept;
        const char* begin() const noexcept;
        char* end() noexcept;
        const char* end() const noexcept;
        // !iterator operators

        // misc
        static u64 length(const char* s) noexcept;
        static u64 length(const string& s) noexcept;

        static bool compare(const char* a, const char* b) noexcept;
        bool compare(const char* s) const noexcept;
        bool compare(const char* s, u64 len) const noexcept;
        bool compare(const string& s) const noexcept;

        static char lower(const char c) noexcept;
        static char upper(const char c) noexcept;
        static string lower(const char* c) noexcept;
        static string lower(const char* c, u64 len) noexcept;
        static string upper(const char* c) noexcept;
        static string upper(const char* c, u64 len) noexcept;

        static char* copy(char* dst, const char* src, uint len);
        static char* copy(char* dst, const string_view& src);
        static char* copy(char* dst, const string& src);

        static void u8_to_u16(const string& str8, wchar_t* p_buffer, uint count) noexcept;
        // !misc

    private:
        string clone() const;
        char* get_ptr() noexcept;
        char* get_ptr() const noexcept;
        u64 get_size() const noexcept;
        u64 get_alloc_size(u64 minimal) const noexcept;

        explicit string(string_impl*);

        string_impl* mImpl;
    };

    bool operator==(const string& a, const string& b) noexcept;
    bool operator!=(const string& a, const string& b) noexcept;

    string operator+(const string& a, const string& b);
    string operator+(const string& a, const char& b);
    string operator+(const string& a, const char* b);

    string stringify(i8  v);
    string stringify(u8  v);
    string stringify(i16 v);
    string stringify(u16 v);
    string stringify(i32 v);
    string stringify(u32 v);
    string stringify(i64 v);
    string stringify(u64 v);
    string stringify(float v);
    string stringify(double v);

    /**
     * Special string class variant for ref_counted pointers.
     */
    class rc_string : public ref_counted, public string {
    public:
        using string::string;
    };
}

#endif //WHITEGEAR_STRING_HPP
