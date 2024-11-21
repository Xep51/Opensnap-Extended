OPENSNAP
==========

What's that?
------------
Opensnap brings the Aero Snap feature to Openbox.

Fork goals
------------

* Full-fledged unsnapping
* Maximizing with consideration of windows borders
* Support for all keyboard layouts (currently only English and Russian)
* Detecting screen layout changes
*

Does this work with other window managers?
------------------------------------------
The author of the original project stated “The goal was to make it work with every EWMH compliant window manager.” but support for other WM's in this fork is not guaranteed.

Dependencies
-------------
Runtime:
* __wmctrl__ (for default configuration)

Build:
* __base-devel__
* __libx11__
* __gtk3__

Installing
----------
If you want to install opensnap from source first make sure you have git installed.

Fetch via git:

    git clone https://github.com/lawl/opensnap.git

Make sure you have all prerequisits:

In Arch:

	sudo apt-get install base-devel libx11 gtk3 wmctrl

In Debian:

    sudo apt-get install build-essential libx11-dev libgtk-3-dev wmctrl

And finally build and install it:

    cd opensnap*
    make
    sudo make install

And now start opensnap with

    opensnap

or

    opensnap --deamon

if you want it to deamonize.
    
Customizing the configuration
-----------------------------
By default opensnap stores its configuration files in /etc/opensnap if you've run `make install`.
If you want to customize these, you should copy the global configuration to your user directory.

    mkdir -p ~/.config/opensnap
    cp /etc/opensnap/* ~/.config/opensnap/

You can now edit the configuration files in `~/.config/opensnap/`. Make sure to restart opensnap for it to see the new configuration directory.

How can I use it?
-----------------
This should tell you all you need to know:

    opensnap --help

Copy the sample configs to ~/.config/opensnap/.


Unsnap workaround
-----------------

Unsnapping is planned to be added...
But as of now opensnap does not support unsnapping (see #4).
You can find a workaround here: https://github.com/lawl/opensnap/issues/4#issuecomment-23666097

Do note however that this does not perfect unsnapping. I.e. your cursor possition and the window you are dragging might get displaced a bit on unsnapping. But it does work well enough for daily use.
