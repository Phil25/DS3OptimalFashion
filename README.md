# DS3OptimalFashion

*Most optimal armor for your favorite build looks like poop? Find the next best thing!*

This is basically Dark Souls III armor finder at [soulsplanner.com](soulsplanner.com) with some additional functionality.

## Differences from soulsplanner.com
* Allows to specify a whitelist for items you want to have.
* Allows to specify a blacklist for items you want to exclude.
* Allows to specify minimal difference from most optimal armor to find multiple sets.
* Is optimized a bit better (especially when specifying min limits for multiple params, which prolly nobody uses).
* Is not a website and ofc is still WIP.

## Features
* Eh, I'll think what to add when this is more complete.

## Thirdparty tools used
* [soulsplanner.com](soulsplanner.com)'s armor section for armor parameter tables.
* [Table Capture](https://chrome.google.com/webstore/detail/table-capture/iebpjdmgckacbodjpijphcplhebcmeop) Chrome extension to parse said tables.

## Building
This project uses the [Conan](https://docs.conan.io/en/latest/installation.html) package manager.
Since it's a Python-based tool, you might want to install it through `pip` in a [virtual environment](https://packaging.python.org/guides/installing-using-pip-and-virtual-environments/#creating-a-virtual-environment).
1. clone and cd to repo,
1. setup CMake and dependencies: `conan install .`,
    * optionally specify compiler by adding `-s compiler=clang -s compiler.version=11`,
1. build the project: `conan build .`,
    * add `-c` to only generate CMake files and a solution (if on Windows) without building.
