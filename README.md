OPENSNAP
==========

What's that?
------------
Opensnap brings the Aero Snap feature to Openbox.

Fork goals
------------

* Full-fledged unsnapping ___(Done! Mostly..)___
* Maximizing with consideration of windows borders __(Done!)__
* Support for all keyboard layouts __(Done!)__
* Detecting screen layout changes
* Сreate a fully functional configuration file
* Add a corner snapping function
* Fix windows not snapping if they are grabbed near the screen edge __(Done!)__
* Get rid of the wmctrl dependency

Does this work with other window managers?
------------------------------------------
The author of the original project stated “The goal was to make it work with every EWMH compliant window manager.” but support for other WM's in this fork is not guaranteed.

Dependencies
-------------
Runtime:
* __wmctrl__ (for default configuration)

Build:
* __Xlib__ (dev package)
* __gtk3__ (dev package)
* __gcc__
* __make__

Installing
----------
If you want to install opensnap from source first make sure you have git installed.

Fetch via git:

    git clone https://github.com/Xep51/Opensnap-Extended.git

Build and install it:

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

If you are using window borders, set the `WINDOW_BORDERS` variable in the config to the value specified in `border.Width` in `themerc`. 

How can I use it?
-----------------
This should tell you all you need to know:

    opensnap --help

Copy the sample configs to ~/.config/opensnap/.

Unsnapping
-----------------
Unsnapping was added. But it works a bit less than ideal: due to Openbox architecture it is impossible to change window geometry and run Move action at the same time - the geometry must be changed first and then Move is run, otherwise the geometry change will be simply lost.
Attempts to run a unsnap script from the Openbox config before Move did not lead to anything.

How was this solved? Opensnap reads the window grabbing (not moving) and changes its geometry. Grabbing happens when the title bar or modkey is pressed, but Move happens when the mouse is moved from the initial grabbing location. So first the geometry is changed, and then Move is started.

The problem is that if you start moving too quickly after grabbing, the geometry change will happen after it starts, so before you move the window, you need to grab it and wait a few fractions of a second.
 
To work perfectly, it is required to either move all Openbox code related to moving to Opensnap, or modify the source code of Openbox itself.

If you use modification key to move windows, you need to put this into mousebind config block in `~/.config/openbox/rc.xml` (replacing the default move bind):
```
<mousebind button="W-Left" action="Drag">
  <action name="if">
    <maximizedvertical>yes</maximizedvertical>
    <then>
      <action name="Unmaximize"/>
        <direction>vertical</direction>
      </action>
    </then>
  <else>
    <action name="Move"/>
  </else>
  </action>
</mousebind>
```
Also.... in the case of the shortcut when unsnapping it seemed to me to make the most sense to teleport the center of window to the pointer, but this also happens in the case of the title bar, maybe I'll fix it later.

Known issues
-------------
* The active window will be snapped even if the mouse and modifier key were pressed outside of it. The same will happen if the mouse was pressed on the title of another window and the focus when clicking on the window is disabled in the Openbox config. There is no way to fix this, for that you have to create a fork of Openbox itself... maybe someday I will do it.
* Windows with non-WM borders (as easyeffects) snapping as if they have a WM border in addition to their own, so there will be a gap on the side. Will this be fixed? idk.
