# DS3OptimalFashion

*Most optimal armor for your favorite build looks like poop? Find the next best thing!*

This is basically Dark Souls III armor finder at [soulsplanner.com](soulsplanner.com) with some additional functionality.

## Differences from soulsplanner.com
* Preview armor icons.
* Whitelist for items you want to have.
* Blacklist for items you want to exclude.
* Minimal difference from most optimal set to find similarly optimized ones more easily.

## Features
* Rich armor search options:
    * Select desired weight percentage based on current load (weapons + rings) and full load (VIT + multipliers).
    * Parameter you want to maximize and acceptable value difference from the most optimized one found.
    * Minimal constraints for each parameter.
    * Whitelist and blacklist any item.
* Simple preview of the selected set which updates dynamically.
* Easily whitelist and blacklist items with left/middle click.
* Available on all systems.

## Legal and thirdparty
* Armor item names and images are properties of FromSoftware Inc.
* [wxWidgets](www.wxwidgets.org) for cross-platform native GUI.
* [soulsplanner.com](soulsplanner.com)'s armor section for armor parameter tables.
* [Table Capture](https://chrome.google.com/webstore/detail/table-capture/iebpjdmgckacbodjpijphcplhebcmeop) Chrome extension to parse said tables.

## Building
This project uses the [Conan](https://docs.conan.io/en/latest/installation.html) package manager.
Since it's a Python-based tool, you might want to install it through `pip` in a [virtual environment](https://packaging.python.org/guides/installing-using-pip-and-virtual-environments/#creating-a-virtual-environment).
1. clone and cd to repo,
1. add Bincrafters remote: `conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan`
1. setup CMake and dependencies: `conan install .`,
    * optionally specify compiler by adding `-s compiler=clang -s compiler.version=11`,
    * optionally specify build type by adding `--build_type=Debug`,
    * might require `--build missing` when prebuilt dependencies are not found,
1. build the project: `conan build .`,
    * add `-c` to only generate CMake files and a solution (if on Windows) without building.