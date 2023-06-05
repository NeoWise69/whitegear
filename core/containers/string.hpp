
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

namespace wg {
    struct string_impl;

    class string {
    public:
        virtual ~string();
        string();

        string(const string&);
        string(string&&) noexcept;
        string& operator=(const string&);
        string& operator=(string&&) noexcept;

        string(const char* s);
        string& operator=(const char* s);
        string(const char* s, u64 len);
        string(const string_view& sv);

        // access/write
        string& append(const char* s);
        string& append(const char* s, u64 len);
        string& append(const char c, u64 len = 1);
        string& append(const string& o);
        string& append(string&& o);

        string& operator+=(const char* s);
        string& operator+=(const char c);
        string& operator+=(const string& o);
        string& operator+=(string&& o);

        const char& operator[](i64 i) const;
        char& operator[](i64 i);
        // !access/write

        // getters
        const u64 size() const;
        const u64 capacity() const;
        bool empty() const;
        const char* c_str() const;
        char* data() const;
        // !getters

        // iterator operators
        char* begin();
        const char* begin() const;
        char* end();
        const char* end() const;
        // !iterator operators

        // misc
        static u64 length(const char* s);
        static u64 length(const string& s);

        static bool compare(const char* a, const char* b);
        bool compare(const char* s) const;
        bool compare(const char* s, u64 len) const;
        bool compare(const string& s) const;

        static char lower(const char c);
        static char upper(const char c);
        static string lower(const char* c);
        static string lower(const char* c, u64 len);
        static string upper(const char* c);
        static string upper(const char* c, u64 len);

        static char* copy(char* dst, const char* src, uint len);
        static char* copy(char* dst, const string_view& src);
        static char* copy(char* dst, const string& src);

        static void u8_to_u16(const string& str8, wchar_t* p_buffer, uint count);
        // !misc

    private:
        string clone() const;
        char* get_ptr();
        char* get_ptr() const;
        u64 get_size() const;
        u64 get_alloc_size(u64 minimal) const;

        explicit string(string_impl*);

        string_impl* mImpl;
    };

    bool operator==(const string& a, const string& b);
    bool operator!=(const string& a, const string& b);

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

}

#endif //WHITEGEAR_STRING_HPP
