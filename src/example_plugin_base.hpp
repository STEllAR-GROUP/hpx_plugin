//  Copyright (c) 2016 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_EXAMPLE_PLUGIN_BASE)
#define HPX_EXAMPLE_PLUGIN_BASE

#include <hpx/config.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace example
{
    struct example_plugin_base
    {
        virtual ~example_plugin_base() {}

        /// Exposed functionality of this plugin type
        virtual void do_something_useful() = 0;
    };
}

#endif

