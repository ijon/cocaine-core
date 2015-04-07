/*
    Copyright (c) 2011-2014 Andrey Sibiryov <me@kobology.ru>
    Copyright (c) 2011-2014 Other contributors as noted in the AUTHORS file.

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

#ifndef COCAINE_ENGINE_INTERFACE_HPP
#define COCAINE_ENGINE_INTERFACE_HPP

#include "cocaine/rpc/protocol.hpp"

namespace cocaine { namespace io {

struct rpc_tag;
struct control_tag;

struct rpc {

struct handshake {
    typedef rpc_tag tag;

    static const char* alias() noexcept {
        return "handshake";
    }

    typedef control_tag dispatch_type;
    typedef control_tag upstream_type;

    typedef boost::mpl::list<
        /* peer id */ std::string
    > argument_type;
};

//struct terminate {
//    typedef rpc_tag tag;

//    static const char* alias() noexcept {
//        return "terminate";
//    }

//    enum code: int {
//        normal = 1,
//        abnormal
//    };

//    typedef boost::mpl::list<
//        /* code */   code,
//        /* reason */ std::string
//    > argument_type;
//};

//struct invoke {
//    typedef rpc_tag tag;

//    static const char* alias() noexcept {
//        return "invoke";
//    }

//    typedef boost::mpl::list<
//        /* event */ std::string
//    > argument_type;
//};

//struct chunk {
//    typedef rpc_tag tag;

//    static const char* alias() noexcept {
//        return "chunk";
//    }

//    typedef boost::mpl::list<
//        /* chunk */ std::string
//    > argument_type;
//};

//struct error {
//    typedef rpc_tag tag;

//    static const char* alias() noexcept {
//        return "error";
//    }

//    typedef boost::mpl::list<
//        /* code */   int,
//        /* reason */ std::string
//    > argument_type;
//};

//struct choke {
//    typedef rpc_tag tag;

//    static const char* alias() noexcept {
//        return "choke";
//    }
//};

}; // struct rpc

template<>
struct protocol<rpc_tag> {
    typedef boost::mpl::int_<
        1
    >::type version;

    typedef boost::mpl::list<
        rpc::handshake
//        rpc::heartbeat,
//        rpc::terminate,
//        rpc::invoke,
//        rpc::chunk,
//        rpc::error,
//        rpc::choke
    > messages;

    typedef rpc scope;
};

struct control {

struct heartbeat {
    typedef control_tag tag;

    static const char* alias() noexcept {
        return "heartbeat";
    }

    typedef control_tag dispatch_type;
    typedef void        upstream_type;
};

}; // struct control

template<>
struct protocol<control_tag> {
    typedef boost::mpl::int_<
        1
    >::type version;

    typedef boost::mpl::list<
        control::heartbeat
    >::type messages;

    typedef control scope;
};

}} // namespace cocaine::io

#endif
