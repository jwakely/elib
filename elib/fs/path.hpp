#ifndef ELIB_FS_PATH_HPP
#define ELIB_FS_PATH_HPP

#include <elib/fs/detail/path_converter.hpp>

#include <string>
#include <iterator>
#include <locale>
#include <cstddef>
#include <iostream>
#include <utility>

namespace elib 
{
  namespace fs 
  {
    
    class path 
    {
      public:
        typedef char value_type;
        typedef std::basic_string<value_type> string_type;
        
        static constexpr value_type preferred_separator = '/';
        
        // ctor & dtor
        // can't be default for some reason
        path() : m_pathname{}
        { }
        
        path(const path& p)
          { m_pathname = p.m_pathname; }
          
        path(path&& p) noexcept 
          { m_pathname = std::move(p.m_pathname); }
        
        template <typename Source>
        path(const Source& src)
        {
          m_pathname = detail::dispatch<string_type>(src);
        }
        
        template <typename InputIter>
        path(InputIter begin, InputIter end)
        {
          typedef typename std::iterator_traits<InputIter>::value_type vtype;
            
          if (begin != end) 
          {
            std::basic_string<vtype> s{begin, end};
            m_pathname = detail::convert<string_type>(s);
          }
        }
        
        //TODO
        template <typename Source>
        path(const Source& src, const std::locale& loc);
        
        //TODO
        template <typename InputIter>
        path(InputIter begin, InputIter end, const std::locale& loc);

        ~path()=  default;
        
      //assignments
        path& operator=(const path& p)
        {
          m_pathname = p.m_pathname;
          return *this;
        }
        
        path& operator=(path&& p) noexcept
        {
          m_pathname = std::move(p.m_pathname);
          return *this;
        }
        
        template <typename Source>
          detail::enable_if_convertible_t<Source, path>&
        operator=(const Source& src)
        { 
          return assign(src);
        }
        
        template <typename Source>
          detail::enable_if_convertible_t<Source, path>&
        assign(const Source& src)
        {
          m_pathname = detail::dispatch<string_type>(src);
          return *this;
        }
        
        template <typename InputIter>
        path& assign(InputIter begin, InputIter end)
        {
          typedef typename std::iterator_traits<InputIter>::value_type vtype;
          
          if (begin != end)
          {
            std::basic_string<vtype> s{begin, end};
            m_pathname = detail::convert<string_type>(s);
          }
            
          return *this;
        }
        
      //appends
        path& operator/=(const path& p)
        {
            bool append_sep = ( !empty() &&
                                !p.empty() &&
                                p.m_pathname[0] != preferred_separator &&
                                m_pathname.back() != preferred_separator);
            if (append_sep) 
                m_pathname += preferred_separator;
            
            m_pathname += p.native();
            return *this;
        }
        
        template <typename Source>
          detail::enable_if_convertible_t<Source, path>&
        operator/=(const Source& src)
        {
            path p{detail::dispatch<string_type>(src)};
            return this->operator/=(p);
        }
        
        template <typename Source>
          detail::enable_if_convertible_t<Source, path>&
        append(const Source& src)
        {
            path p{detail::dispatch<string_type>(src)};
            return this->operator/=(p);
        }
        
        template <typename InputIter>
        path& append(InputIter begin, InputIter end)
        {
          typedef typename std::iterator_traits<InputIter>::value_type vtype;
          
          if (begin != end) 
          {
            std::basic_string<vtype> str{begin, end};
            path p{detail::convert<string_type>(str)};
            this->operator/=(p);
          }
            
          return *this;
        }
        
      //concatenation
        path& operator+=(const path& p)
        {
          m_pathname += p.native();
          return *this;
        }
        
        path& operator+=(const string_type& str)
        {
          m_pathname += str;
          return *this;
        }
        
        path& operator+=(const value_type* str)
        { 
          m_pathname += str;
          return *this;
        }
        
        path& operator+=(value_type ch)
        {
          m_pathname += ch;
          return *this;
        }
        
        template <typename Source>
          detail::enable_if_convertible_t<Source, path>&
        operator+=(const Source& src)
        {
          return this->operator+=(detail::dispatch<string_type>(src));
        }
        
        template <typename CharT>
          detail::enable_if_convertible_t<std::basic_string<CharT>, path>&
        operator+=(CharT ch)
        {
          std::basic_string<CharT> tmp{};
          tmp += ch;
          return this->operator+=(detail::convert<string_type>(tmp));
        }
        
        template <typename Source>
          detail::enable_if_convertible_t<Source, path>& 
        concat(const Source& src)
        {
          return this->operator+=(detail::dispatch<string_type>(src));
        }
        
        template <typename InputIter>
        path& concat(InputIter begin, InputIter end)
        {
          typedef typename std::iterator_traits<InputIter>::value_type vtype;
          if (begin != end) 
          {
            std::basic_string<vtype> tmp{begin, end};
            this->operator+=(detail::convert<string_type>(tmp));
          }
          return *this;
        }
        
        
      // modifiers
        void clear() noexcept
        { 
          m_pathname.clear(); 
        }
        
        path& make_preferred()
        {
          value_type other_sep;
          if (preferred_separator == '/')
            other_sep = '\\';
          else
            other_sep = '/';
          for (auto& ch : m_pathname) 
          {
            if (ch == other_sep)
              ch = preferred_separator;
          }
          return *this;
        } 
        
        path& remove_filename()
        {
          return *this = parent_path();
        }
        
        
        path& replace_filename(const path& replacement)
        {
          remove_filename();
          return *this /= replacement;
        }
        
        path& replace_extension(const path& replacement = path())
        {
          path p = extension();
          if (!p.empty())
            m_pathname.erase(m_pathname.size() - p.native().size());
          if (!replacement.empty())
          {
            if (replacement.native()[0] != '.')
              m_pathname += ".";
            m_pathname.append(replacement.m_pathname);
          }
          return *this;
        }
        
        void swap(path& rhs) noexcept
        {
          m_pathname.swap(rhs.m_pathname);
        }

    //native format observers
        const string_type& native() const noexcept
        { 
          return m_pathname; 
        }
        
        //EXTENSION
        const string_type& str() const noexcept
        { 
          return m_pathname; 
        }
        
        const value_type* c_str() const noexcept
        { 
          return m_pathname.c_str(); 
        }
        
        operator string_type() const
        { 
          return m_pathname; 
        }
        
        template <class CharT, class Traits = std::char_traits<CharT>,
            class Allocator = std::allocator<CharT>>
          std::basic_string<CharT, Traits, Allocator>
        string(const Allocator& a = Allocator()) const; //TODO
        
        std::string string() const
        { 
          return m_pathname; 
        }
        
        std::wstring wstring() const; //TODO
        std::string u8string() const; //TODO
        std::u16string u16string() const; //TODO
        std::u32string u32string() const; //TODO
        
        
    //generic format observers
        template <class CharT, class Traits = std::char_traits<CharT>,
            class Allocator = std::allocator<CharT>>
          std::basic_string<CharT, Traits, Allocator>
        generic_string(const Allocator& a = Allocator()) const; //TODO
        
        std::string generic_string() const; //TODO
        std::wstring generic_wstring() const; //TODO
        std::string generic_u8string() const; //TODO
        std::u16string generic_u16string() const; //TODO
        std::u32string generic_u32string() const; //TODO
        
        
    // comparision
        int compare(const path& p) const noexcept;
        
        int compare(const string_type& str) const
        { 
          return compare(path(str)); 
        }
        
        int compare(const value_type* str) const
        { 
          return compare(path(str)); 
        }
        
        
    //decompasition
        path root_name() const;
        path root_directory() const;
        path root_path() const;
        path relative_path() const;
        path parent_path() const;
        path filename() const;
        path stem() const;
        path extension() const;
        
        
    // query
        bool empty() const noexcept
          { return m_pathname.empty(); }
        
        bool has_root_name() const
          { return !root_name().empty(); }
        
        bool has_root_directory() const
          { return !root_directory().empty(); }
        
        bool has_root_path() const
          { return !root_path().empty(); }
        
        bool has_relative_path() const
          { return !relative_path().empty(); }
        
        bool has_parent_path() const
          { return !parent_path().empty();}
        
        bool has_filename() const
          { return !filename().empty(); }
        
        bool has_stem() const
          { return !stem().empty();}
          
        bool has_extension() const
          { return !extension().empty(); }
        
        bool is_absolute() const
          { return !root_directory().empty();}
        
        bool is_relative() const
          { return !is_absolute(); }
        
      // iterators
        class iterator;
        typedef iterator const_iterator;
        
        iterator begin() const;
        iterator end() const;
        
        
        //
      private:
        //

      
        string_type m_pathname{};
      
    }; // class path

////////////////////////////////////////////////////////////////////////////////
//                        path functions                                                  
////////////////////////////////////////////////////////////////////////////////

    inline void swap(path& lhs, path& rhs) noexcept
      { lhs.swap(rhs); }

      
    inline bool operator<(const path& lhs, const path& rhs) noexcept
      { return (lhs.compare(rhs) < 0); }

    inline bool operator<=(const path& lhs, const path& rhs) noexcept
      { return (lhs.compare(rhs) <= 0); }
      
    inline bool operator>(const path& lhs, const path& rhs) noexcept
      { return (lhs.compare(rhs) > 0); }
      
    inline bool operator>=(const path& lhs, const path& rhs) noexcept
      { return (lhs.compare(rhs) >= 0); }
      
    inline bool operator==(const path& lhs, const path& rhs) noexcept
      { return (lhs.compare(rhs) == 0); }
      
    inline bool operator!=(const path& lhs, const path& rhs) noexcept
      { return (lhs.compare(rhs) != 0); }

    
    inline path operator/(const path& lhs, const path& rhs)
      { return path(lhs) /= rhs;}

    //TODO 
    template <class CharT, class Traits>
      inline std::basic_ostream<CharT, Traits>&
    operator<<(std::basic_ostream<CharT, Traits>& os, const path& p)
    {
      os << p.native();
      return os;
    }
    
    //TODO
    template <class CharT, class Traits>
      inline std::basic_istream<CharT, Traits>&
    operator>>(std::basic_istream<CharT, Traits>& is, path& p)
    {
      path::string_type tmp;
      is >> tmp;
      p = tmp;
      return is;
    }

    template <class Source>
    path u8path(const Source& src);  //TODO

    template <class InputIter>
    path u8path(InputIter begin, InputIter end); //TODO

    std::size_t hash_value(const path& p) noexcept; //TODO

    
////////////////////////////////////////////////////////////////////////////////
//                        path::iterator                                                 
////////////////////////////////////////////////////////////////////////////////


    class path::iterator 
      : public std::iterator<std::bidirectional_iterator_tag, path> 
    {
      public:
        
      // ctor & dtor
        iterator() = default;
        iterator(const iterator&) = default;
        iterator(iterator&&) noexcept = default;
        ~iterator() = default;
        
      //assignments
        iterator& operator=(const iterator&) = default;
        iterator& operator=(iterator&&) = default;
        
      // iterator functionality
        const path& operator*() const
        { return m_element; }
        
        const path* operator->() const
        { return &m_element; }
        
      // forward iterator requirements
        iterator& operator++()
        { return increment(); }
        
        iterator
        operator++(int)
        {
          iterator it{*this};
          increment();
          return it;
        }
        
      // bidirectional iterator requirements
        iterator& operator--()
        { return decrement(); }
        
        iterator operator--(int)
        {
          iterator it{*this};
          decrement();
          return it;
        }
        
        // logic for traversal is here
        iterator& increment();
        iterator& decrement();

    // equality comparable     
        bool operator==(const iterator& other) const
        { 
          return (m_path_ptr == other.m_path_ptr && m_pos == other.m_pos);
        }
        
        bool operator!=(const iterator& other) const
        { 
          return !(this->operator==(other)); 
        }
        
        //
      private:
        //
        
        // for begin() and end()
        friend class path;
        
        // check if the element is a valid iterator element,
        // ie. check it is not a (non-trailing/root) separator
        bool m_valid_iterator_position() const;
        
        // parse the token at pos & set the iterator to said element
        // return the result of valid_iterator_position() after
        // setting the element
        bool m_set_position(std::size_t pos);
        
        // return the string for the assocated path
        // as if by path::native()
        const string_type&
        m_path_str() const;
      
        path m_element;
        const path *m_path_ptr{nullptr};
        std::size_t m_pos;
        
    }; // class path::iterator
   
    
  } /* namespace fs */
} /* namespace elib */
#endif /* ELIB_FS_PATH_HPP */