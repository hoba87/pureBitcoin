pureBitcoin Project
===================

Why another Bitcoin implementation?
-----------------------------------
First of all I want to learn how bitcoin works on the low level. When I have a
look into the bitcoin core code, I get the impression that the structure is
somehow confusing. That's why I'm starting a new implementation from scratch.
Perhaps these efforts will also lead to improvements of the bitcoin core code.

What is the aim of this project?
--------------------------------
The aim of this project is to write a clearly structured, well documented
implementation of the bitcoin protocol. Any unnecessary overhead should be
avoided.

Code style guidelines
---------------------
At first look at existing code to follow the style guidelines.

Pull requests
-------------
Pull requests should contain a single commit, which adds or changes one specific unit.

Build system
------------
A C++11 compiler is required. At first the code is developed using the IDE Code::Blocks with gcc-4.8.1. Using autotools later is planned.

Dependencies
------------
The project needs the boost library, at the moment version 1.55.0 is used.

Roadmap
-------
- write test code (ongoing)
- communication with peers
- download and verification of blockchain
- wallet, create transactions
- rpc server
- ...

License
-------
The project is released under the terms of the MIT license. See LICENSE for
more information.
