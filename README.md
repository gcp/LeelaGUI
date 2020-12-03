About
=====

This is the original source of the Go/Baduk program 'Leela'.

The engine itself is in the [Leela repo](https://github.com/gcp/Leela). This one contains the graphical user interface.

Screenshot
==========
![Screenshot of LeelaGUI](https://sjeng.org/leelaviz8.png "Leela")

Building
========

The engine needs boost and OpenCL libraries and development headers (and/or OpenBLAS) to compile. The GUI was built in wxWidgets, using wxFormBuilder for layouts. The installer
requires NSIS.

The included Makefile likely needs some modification to work on random Linux systems. Likewise the Visual Studio projects will need their include and lib directories modified.

The GUI assumes the engine source has been unpacked alongside it, in an "engine" subdir
on Linux, or in a dir set in Visual Studio configuration on Visual Studio. The engine's repository is [here on Github as well](https://github.com/gcp/Leela).

Contributing
============

I do not accept contributions to or bug reports about this code. Maintaining an open source effort is a lot of work, and I do not have the time and energy to maintain the project at this point in time. If you wish to improve it, feel free to fork the repostiory and make your fork the best one there is. But do me **ONE** favor, and do keep Leela's name in your fork..

License
=======

The code is licensed under the MIT license.
