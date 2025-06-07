# WALL-E (2008, PC/Macintosh) decompilation project

This is the GitHub repository that contains all the decompiled code for WALL-E (2008), the video game. Specifically, it's the Macintosh version of the game.

The PC and Macintosh versions of the game are virtually indistinguishable, say for the Macintosh version being compiled and suited for running on Macintoshes in 2008, both PowerPC and Intel x86 variants.

## Contribution

There are no decompilation tools available to the public yet. They are simply not written to be easily distributable. 

**If you are interested in contributing to this project and want to get your hands on the tools used for decompiling this game, please message theb4n4n4 (actual name: b4n4n4) on Discord.** You do not have to add me as a friend if you join the [Zouna Underground Discord server](https://discord.gg/CQgMNbYeUR).

## Build

If you want to build this project, you'll need to have the following:
- A machine with OS X 10.4 (Tiger) installed. 10.5 and 10.6 might also work.
- Xcode 2.4 (not 2.4.1!). In Xcode, the only parts that are necessary are Apple's fork of gcc (version 5363), Apple's own linker (`ld`), assembler (`as`), strip tool (`strip`), and Make.
Once you have all of that, copy the contents of this repository over to the OS X machine, open the Terminal app on the OS X machine, navigate to the directory of the copied repository and do this:
`make`
You should now have two binaries: `ZOUNA.executable` and `ZOUNA.stripped.executable`. You'll probably want to match against `ZOUNA.executable`, as `ZOUNA.stripped.executable` has the exact same `strip -x` command ran on it as WALL-E Mac's game executable that was RtM.

