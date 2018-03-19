
Debian
====================
This directory contains files used to package Dealtokend/Dealtoken-qt
for Debian-based Linux systems. If you compile Dealtokend/Dealtoken-qt yourself, there are some useful files here.

## Dealtoken: URI support ##


Dealtoken-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install Dealtoken-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your Dealtoken-qt binary to `/usr/bin`
and the `../../share/pixmaps/Dealtoken128.png` to `/usr/share/pixmaps`

Dealtoken-qt.protocol (KDE)

