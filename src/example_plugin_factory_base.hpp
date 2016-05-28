//  Copyright (c) 2016 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_EXAMPLE_PLUGIN_FACTORY_BASE)
#define HPX_EXAMPLE_PLUGIN_FACTORY_BASE

#include <hpx/config.hpp>
#include <hpx/plugins/plugin_factory_base.hpp>

#include <hpx/util/detail/pack.hpp>
#include <hpx/util/plugin.hpp>
#include <hpx/util/plugin/export_plugin.hpp>

#include "example_plugin_base.hpp"

///////////////////////////////////////////////////////////////////////////////
namespace example
{
    ///////////////////////////////////////////////////////////////////////////
    /// The \a plugin_factory_base has to be used as a base class for all
    /// plugin factories.
    struct example_plugin_factory_base : hpx::plugins::plugin_factory_base
    {
        virtual ~example_plugin_factory_base() {}

        /// Create a new instance of an example plugin
        ///
        /// return Returns the newly created instance of the message handler
        ///        supported by this factory
        virtual example_plugin_base* create() = 0;
    };
}

namespace hpx { namespace util { namespace plugin
{
    ///////////////////////////////////////////////////////////////////////////
    // The following specialization of the virtual_constructor template
    // defines the argument list for the constructor of the concrete plugin
    // factory (derived from the component_factory_base above). This magic is
    // needed because we use hpx::plugin for the creation of instances of
    // derived types using the example_plugin_factory_base virtual base class
    // only (essentially implementing a virtual constructor).
    //
    // All derived component factories have to expose a constructor with the
    // matching signature. For instance:
    //
    //     class my_factory : public example_plugin_factory_base
    //     {
    //     public:
    //         my_factory (hpx::util::section const*, hpx::util::section const*, bool)
    //         {}
    //     };
    //
    template <>
    struct virtual_constructor<example::example_plugin_factory_base>
    {
        typedef
            hpx::util::detail::pack<
                hpx::util::section const*, hpx::util::section const*, bool
            > type;
    };
}}}

///////////////////////////////////////////////////////////////////////////////
/// This macro is used to register the given component factory with
/// Hpx.Plugin. This macro has to be used for each of the component factories.
#define HPX_REGISTER_EXAMPLE_PLUGIN_FACTORY_BASE(FactoryType, pluginname)     \
    HPX_PLUGIN_EXPORT(HPX_PLUGIN_PLUGIN_PREFIX,                               \
        hpx::plugins::plugin_factory_base, FactoryType,                       \
        pluginname, factory)                                                  \
/**/

#endif

