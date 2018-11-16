# Rocket Launcher 2.0

Rocket Launcher 2.0 is a cross platform front end for all DOOM source ports. This is an open source GPL licensed cross platform sequel to the original Rocket Launcher front end, adding extended functionality.

Features:

### Easy to Add files

![Alt text](/RLPics/LaunchDrop.png?raw=true "Drag, Drop & Launch")

With Rocket Launcher 2.0, you can easily add files to the load list. You can directly drag multiple files on any of the list boxes on the Launch Wad tab, you can drag and drop files between each list box internally, and you can associate Rocket Launcher with wad/pk3 files so that double clicking on a wad/pk3 opens Rocket Launcher with the files in the 'files to load box', ready to be loaded into your source port of choice.

### Easy to save and load configurations

![Alt text](/RLPics/LoadSaveConf.png?raw=true "Drag, Drop & Launch")

If you're pleased with your particular combination of files to load, engine selection and launch options and wish to quickly recall this configuration for a later time, you can easily do so in the Load / Save Configs tab, where you can save the current configuration to your Favorites list, and with a click of a button, recall all your other saved configurations exactly as they were by selecting any item on the list and clicking "load selected". As before, you can also save configurations to external *.rocket files.

### DOSBox support

![Alt text](/RLPics/DOSBox.png?raw=true "Drag, Drop & Launch")

As with the original Rocket Launcher: adding DOSBox as an engine, and the path to your original iD executable, will enable Rocket Launcher 2's DOSBox mode, which will pump in the necessary DOS commands into DOSBox, instantly launching Doom (or any other iD tech 1 engine you provided) along with the options you selected and files added to load. This allows you to quickly launch any pwad with Doom in DOSBOx without having to fiddle around with DOS command line.

Note that it is recommended that your path to your original Doom executable and additional pwads contain no directory names longer than 8 characters, as this is the form DOS expects - additionally, the original executable can only load the IWAD contained in its folder, rather than the one you selected.

### Extended Engine customization

![Alt text](/RLPics/Engine Setup.png?raw=true "Drag, Drop & Launch")

Rocket Launcher 2.0 also features a new tab allowing you to configure each engine that you added individually, as well as allowing you to add your own 'custom engine', which is particularly useful for when you wish to add multiple beta versions of the same engine.

### Qt Framework

This allows for this project to be cross platform, including support for Linux and OSX. For windows I provide a static build, which means it's provided as a single executable with no additional DLL's required or frameworks to install.

### Installation

#### Windows 

Download executable here: https://github.com/paynworth/RocketLauncher2/releases/download/1.0-32/RocketLauncherPW32_v1.zip

#### Linux

No binaries available as of yet. To compile, simply grab Qt5-default package, then run qmake, followed by make, on the source code.

#### Mac

Coming soon.

### Thanks to:
<br>
Blzut3: for helping me with some Qt queries.<br>
Arkore: for testing on Windows.<br>
DevilHunter: for testing on Windows.<br>
TerminusEst13: for originally coming up with the name 'Rocket Launcher' for the front end.<br>
