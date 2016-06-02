//  Copyright (c) 2016 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "example_plugin_factory.hpp"
#include "example_plugin1.hpp"
#include "example_plugin2.hpp"

///////////////////////////////////////////////////////////////////////////////
// Add this once for each module
HPX_REGISTER_EXAMPLE_PLUGIN_MODULE_DYNAMIC();

// Add this once for each supported plugin type
HPX_REGISTER_EXAMPLE_PLUGIN_FACTORY(example::example_plugin1, example_plugin1);
HPX_REGISTER_EXAMPLE_PLUGIN_FACTORY(example::example_plugin2, example_plugin2);

