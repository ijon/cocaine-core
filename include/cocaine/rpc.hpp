/*
    Copyright (c) 2011-2012 Andrey Sibiryov <me@kobology.ru>
    Copyright (c) 2011-2012 Other contributors as noted in the AUTHORS file.

    This file is part of Cocaine.

    Cocaine is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    Cocaine is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>. 
*/

#ifndef COCAINE_RPC_HPP
#define COCAINE_RPC_HPP

#include "cocaine/io.hpp"

namespace cocaine { namespace rpc {    
    
enum {
    heartbeat = 1,
    terminate,
    invoke,
    chunk,
    error,
    choke
};

// Generic packer
// --------------

template<int Code> 
struct packed:
    public boost::tuple<>
{
    typedef boost::tuple<> tuple_type;
};

// Specific packers
// ----------------

template<>
struct packed<invoke>:
    public boost::tuple<const std::string&, zmq::message_t&>
{
    typedef boost::tuple<const std::string&, zmq::message_t&> tuple_type;

    packed(const std::string& event, const void * data, size_t size):
        tuple_type(event, message),
        message(size)
    {
        memcpy(
            message.data(),
            data,
            size
        );
    }

private:
    zmq::message_t message;
};

template<>
struct packed<chunk>:
    public boost::tuple<zmq::message_t&>
{
    typedef boost::tuple<zmq::message_t&> tuple_type;

    packed(const void * data, size_t size):
        tuple_type(message),
        message(size)
    {
        memcpy(
            message.data(),
            data,
            size
        );
    }

    packed(zmq::message_t& message_):
        tuple_type(message)
    {
        message.move(&message_);
    }

private:
    zmq::message_t message;
};

template<>
struct packed<error>:
    // NOTE: Not a string reference to allow literal error messages.
    public boost::tuple<int, std::string>
{
    typedef boost::tuple<int, std::string> tuple_type;

    packed(int code, const std::string& message):
        tuple_type(code, message)
    { }
};
    
}}

#endif
