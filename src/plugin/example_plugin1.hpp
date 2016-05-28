//  Copyright (c) 2016 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_EXAMPLE_PLUGIN1)
#define HPX_EXAMPLE_PLUGIN1

#include <hpx/config.hpp>
#include <hpx/util/ini.hpp>

#include "../example_plugin_base.hpp"

#include <iostream>

///////////////////////////////////////////////////////////////////////////////
namespace example
{
    ///////////////////////////////////////////////////////////////////////////
    struct example_plugin1 : public example_plugin_base
    {
        void do_something_useful()
        {
            std::cout << "This is example_plugin1!" << std::endl;
        }
    };
}

#endif

