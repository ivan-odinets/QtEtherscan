## Introduction

Qt5 library to work with the [Etherscan API](https://docs.etherscan.io/).

## Adding QtEtherscan to yout project

Using Project include files (QtEtherscan.pri)
```bash
mkdir lib && cd lib
git clone https://github.com/ivan-odinets/QtEtherscan.git
```
Alternatively you can add QtEtherscan as a git submodule:
```bash
mkdir lib && cd lib
git submodule add https://github.com/ivan-odinets/QtEtherscan.git
```
In your project file (*project*.pro) add this include:
```qmake
include($$PWD/lib/QtEtherscan/QtEtherscan.pri)
```
Somewhere in your code add this include:
```c++
#include "QtEtherscan.h"
```

## Examples

Some examples showing how to do simple stuff with this library can be found in the examples directory.
- examples/balance_monitor
- examples/error_handling

## License
[GNU Lesser General Public License v3.0](https://choosealicense.com/licenses/lgpl-3.0/)
