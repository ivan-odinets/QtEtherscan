## QtEtherscan

This is a relatively small wrapper to work with the [Etherscan API](https://docs.etherscan.io/).
Written on c++ using Qt.

Tested using Qt 5.15.8 and 6.4.2

## Available features

Currently almost all free methods and all PRO methods from etherscan.io api are implemened.
This includes following submodules:
- [Accounts](https://docs.etherscan.io/api-endpoints/accounts)
- [Contracts](https://docs.etherscan.io/api-endpoints/contracts) All methods, with the exception of 
  [Verify Source Code](https://docs.etherscan.io/api-endpoints/contracts#verify-source-code) and
  [Verify Proxy Contract](https://docs.etherscan.io/api-endpoints/contracts#verify-proxy-contract) methods.
- [Transactions](https://docs.etherscan.io/api-endpoints/stats)
- [Blocks](https://docs.etherscan.io/api-endpoints/blocks)
- [Logs](https://docs.etherscan.io/api-endpoints/logs)
- [Geth/Parity proxy](https://docs.etherscan.io/api-endpoints/geth-parity-proxy)
- [Tokens](https://docs.etherscan.io/api-endpoints/tokens)
- [Gas Tracker](https://docs.etherscan.io/api-endpoints/gas-tracker)
- [Stats](https://docs.etherscan.io/api-endpoints/stats-1)

**NOTE** Although, PRO methods are implemented they are not tested yet!

Current version: 0.0.4

## Adding QtEtherscan to yout project

In order to use this lirary, first you should register an account on etherscan.io and generate a personal API key to use.
Than you can use project include files (QtEtherscan.pri) to add QtEtherscan to your project.

Download QtEtherscan from github
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
```cpp
#include "QtEtherscan.h"
```
And than you can use etherscan.io api methods in the following manner:
```cpp
QtEtherscan::API etherscan;                                // Create QtEtherscan::API object
etherscan.setApiKey(TOKEN);                                // Set ypur API access token
etherscan.setEtheriumNetwork(QtEtherscan::API::Mainnet);   // Set etherium network with which you would like to work

// Just call needed method and handle results
QtEtherscan::EtherBalance balance = etherscan.getEtherBalance("0xde0b295669a9fd93d5f28d9ec85e40f4cb697bae");
qDebug() << "Result: "<<balance;

// Or alternatively you can use QtEherscan::API::call method (e.g. for calling PRO methods
QJsonObject result = etherscan.call({
    { QLatin1String("module"),     QLatin1String("account") },
    { QLatin1String("action"),     QLatin1String("balance") },
    { QLatin1String("tag"),        QLatin1String("latest") },
    { QLatin1String("address"),    "0xde0b295669a9fd93d5f28d9ec85e40f4cb697bae" }
});
```

## Examples & Documentation

Documentation can be generated in the docs folder using doxygen
```bash
doxygen Doxyfile
```

Some examples showing how to do simple stuff with this library can be found in the examples directory.
- examples/balance_monitor - simple example how to use QtEtherscan
- examples/error_handling - how to handle errors on etherscan.io layer
- examples/proxy - how to use methods from "proxy" etherscan.io module

## Usefull links

- [Etherium development documentation](https://ethereum.org/en/developers/docs/)
- [Etherium JSON-RPC API](https://ethereum.org/en/developers/docs/)
- [Etherscan API docs](https://docs.etherscan.io/)

## Donations

Donations are optional, but highly appriciated. So if you like this software and you want to say thanks - feel free to send any amount of crypto to one of the addresses below:
- BTC - bc1qc8nj8swjxtu0fpfsxspv2k49np56u8h86mgy0e
- ETH - 0x903Fd8C2cE645cB6B6F38e7465728c49170d5530
- USDT (ETH Network) - 0x903Fd8C2cE645cB6B6F38e7465728c49170d5530
- XMR - 893ipCFWQXjhXAyMXaryu4RofqZQzpH1nBZDsN9nA6c5BwK79Ae48Ci4rtRoyTi5nAHrpTqbVMPDkXgnHswha2a5F2y62mG

## License
[GNU Lesser General Public License v3.0](https://choosealicense.com/licenses/lgpl-3.0/)
