//  Copyright (c) 2016 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// This executable dynamically loads a shared library and asks it to create
// one instance for each of the factory types it supports. It then uses each of
// the factories to create a corresponding plugin instance. The plugin is
// used to perform some plugin-specific task.
//
// Note that this executable has no knowledge about what plugin types are
// exposed by the loaded shared library. All of this information is dynamically
// discovered at runtime.

#include <hpx/hpx_main.hpp>
#include <hpx/util/plugin.hpp>

#include "example_plugin_factory_base.hpp"

#include <boost/filesystem.hpp>
#include <boost/algorithm/string/case_conv.hpp>

#include <memory>
#include <string>
#include <vector>

///////////////////////////////////////////////////////////////////////////////
void load_registries(hpx::util::plugin::dll& module, hpx::util::section& ini)
{
    // find where the HPX core libraries are located
    boost::filesystem::path plugin_name = hpx::util::find_prefix();
    plugin_name /= "bin";
    plugin_name /= "hpx";
    plugin_name /= HPX_MAKE_DLL_STRING(std::string("hpx_loaded_plugin"));

    // load shared library
    module = hpx::util::plugin::dll(plugin_name.string());

    typedef hpx::plugins::plugin_registry_base plugin_registry_base;

    // create an example plugin
    hpx::util::plugin::plugin_factory<plugin_registry_base> pf(module, "plugin");

    // retrieve the names of all known registries in this shared library
    std::vector<std::string> names;
    pf.get_names(names);

    std::vector<std::string> ini_data;
    if (!names.empty())
    {
        // ask all registries
        for (std::string const& s : names)
        {
            // create the plugin registry object
            std::shared_ptr<plugin_registry_base> registry(pf.create(s));

            // query the configuration information for this registry entry
            registry->get_plugin_info(ini_data);
        }
    }

    // incorporate all information from this module's registry into the ini
    ini.parse("<plugin registry>", ini_data, false, false);
}

///////////////////////////////////////////////////////////////////////////////
bool load_plugins(hpx::util::plugin::dll& module, hpx::util::section& ini)
{
    // load all components as described in the configuration information
    if (!ini.has_section("hpx.plugins"))
    {
        std::cout << "No plugins found/loaded." << std::endl;
        return true;     // no plugins to load
    }

    // each shared library containing plugins may have an ini section
    //
    // # mandatory section describing the component module
    // [hpx.plugins.instance_name]
    //  name = ...           # the name of this component module
    //  path = ...           # the path where to find this component module
    //  enabled = false      # optional (default is assumed to be true)
    //
    // # optional section defining additional properties for this module
    // [hpx.plugins.instance_name.settings]
    //  key = value
    //
    hpx::util::section* sec = ini.get_section("hpx.plugins");
    if (NULL == sec)
    {
        std::cout << "NULL section found" << std::endl;
        return false;     // something bad happened
    }

    hpx::util::section::section_map const& s = (*sec).get_sections();
    typedef hpx::util::section::section_map::const_iterator iterator;

    iterator end = s.end();
    for (iterator i = s.begin (); i != end; ++i)
    {
        // the section name is the instance name of the component
        hpx::util::section const& sect = i->second;
        std::string instance (sect.get_name());
        std::string component;

        if (i->second.has_entry("name"))
            component = sect.get_entry("name");
        else
            component = instance;

        if (sect.has_entry("enabled"))
        {
            std::string tmp = sect.get_entry("enabled");
            boost::algorithm::to_lower(tmp);
            if (tmp == "no" || tmp == "false" || tmp == "0")
            {
                std::cout << "plugin factory disabled: " << instance << std::endl;
                continue;     // this plugin has been disabled
            }
        }

        // initialize the factory instance using the preferences from the
        // ini files
        hpx::util::section const* glob_ini = NULL;
        if (ini.has_section("settings"))
            glob_ini = ini.get_section("settings");

        hpx::util::section const* plugin_ini = NULL;
        std::string plugin_section("hpx.plugins." + instance);
        if (ini.has_section(plugin_section))
            plugin_ini = ini.get_section(plugin_section);

        // get the factory
        hpx::util::plugin::plugin_factory<
                example::example_plugin_factory_base
            > pf(module, "factory");

        // create the plugin factory object, if not disabled
        std::shared_ptr<example::example_plugin_factory_base> factory (
            pf.create(instance, glob_ini, plugin_ini, true));

        // use factory to create an instance of the plugin
        std::shared_ptr<example::example_plugin_base> plugin(factory->create());

        // now use plugin to do something useful
        plugin->do_something_useful();
    }
    return true;
}

int main(int argc, char* argv[])
{
    hpx::util::plugin::dll module;
    hpx::util::section ini;

    // load plugin registry, gather configuration data
    load_registries(module, ini);

    // load plugins based on registry and configuration information
    load_plugins(module, ini);

    return 0;
}
