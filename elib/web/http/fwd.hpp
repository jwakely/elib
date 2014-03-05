#ifndef ELIB_WEB_HTTP_FWD_HPP
#define ELIB_WEB_HTTP_FWD_HPP

# include <string>
# include <vector>
# include <utility>

namespace elib { namespace web { namespace http
{

    enum class version;
    enum class method;
    enum class status;
    
    using data_type = std::vector<char>;
    using field_type = std::pair<std::string, std::string>;
    
    template <class EnumType>
    struct message_header;
    
    using request_header = message_header<method>;
    using response_header = message_header<status>;
    
    template <class Header>
    struct message;
    
    using request = message<request_header>;
    using response = message<response_header>;
    
    data_type serialize(request_header const &);
    data_type serialize(response_header const &);
    data_type serialize(field_type const &);
    data_type serialize(std::vector<field_type> const &);
    
    template <class HeaderType>
    data_type serialize(message<HeaderType> const & m)
    {
        data_type dt;
        
        data_type tmp = serialize(m.header);
        dt.insert(dt.end(), tmp.begin(), tmp.end());
        
        tmp = serialize(m.fields);
        dt.insert(dt.end(), tmp.begin(), tmp.end());
        
        dt.push_back(newl[0]);
        dt.push_back(newl[1]);
        
        dt.insert(dt.end(), m.data.begin(), m.data.end());
        
        return dt;
    }
    
    data_type::const_iterator 
    parse(
        data_type::const_iterator begin
      , data_type::const_iterator const & end
      , request_header & dest
    );
    
    data_type::const_iterator 
    parse(
        data_type::const_iterator begin
      , data_type::const_iterator const & end
      , response_header & dest
    );
    
    data_type::const_iterator 
    parse(
        data_type::const_iterator begin
      , data_type::const_iterator const & end
      , field_type & dest
    );
    
    data_type::const_iterator 
    parse(
        data_type::const_iterator begin
      , data_type::const_iterator const & end
      , std::vector<field_type> & dest
    );
    
    data_type::const_iterator 
    parse_newl(
        data_type::const_iterator begin
      , data_type::const_iterator const & end
    );
    
    template <class Header>
    data_type::const_iterator
    parse(
        data_type::const_iterator begin
      , data_type::const_iterator const & end
      , message<Header> & dest
    )
    
    
}}}                                                         // namespace elib
#endif /* ELIB_WEB_HTTP_FWD_HPP */
