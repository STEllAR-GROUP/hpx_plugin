//  Copyright (c) 2016 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_EXAMPLE_PLUGIN_FACTORY)
#define HPX_EXAMPLE_PLUGIN_FACTORY

#include <hpx/config.hpp>
#include <hpx/plugins/unique_plugin_name.hpp>
#include <hpx/plugins/plugin_registry.hpp>

#include "../example_plugin_base.hpp"
#include "../example_plugin_factory_base.hpp"

///////////////////////////////////////////////////////////////////////////////
namespace example
{
    ///////////////////////////////////////////////////////////////////////////
    template <typename ExamplePlugin>
    struct example_plugin_factory : public example_plugin_factory_base
    {
        example_plugin_factory(hpx::util::section const* global_cfg,
            hpx::util::section const* plugin_cfg, bool is_enabled)
          : is_enabled_(is_enabled)
        {
            // store the configuration settings
            if (NULL != global_cfg)
                global_settings_ = *global_cfg;
            if (NULL != plugin_cfg)
                local_settings_ = *plugin_cfg;
        }

        /// Create a new instance of a example_plugin
        ///
        /// \returns Returns the newly created instance of the plugin
        ///          supported by this factory
        example_plugin_base* create()
        {
            if (is_enabled_)
                return new ExamplePlugin();
            return 0;
        }

    protected:
        hpx::util::section global_settings_;
        hpx::util::section local_settings_;
        bool is_enabled_;
    };
}

///////////////////////////////////////////////////////////////////////////////
/// This macro is used create and to register a minimal example factory with
/// Hpx.Plugin.
#define HPX_REGISTER_EXAMPLE_PLUGIN_FACTORY(ExamplePlugin, pluginname)        \
    HPX_REGISTER_EXAMPLE_PLUGIN_FACTORY_BASE(                                 \
        example::example_plugin_factory<ExamplePlugin>, pluginname)           \
    HPX_DEF_UNIQUE_PLUGIN_NAME(                                               \
        example::example_plugin_factory<ExamplePlugin>, pluginname)           \
    template struct example::example_plugin_factory<ExamplePlugin>;           \
    HPX_REGISTER_PLUGIN_REGISTRY_2(ExamplePlugin, pluginname)                 \
/**/

#endif

