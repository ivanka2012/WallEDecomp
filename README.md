# WALL-E (2008, PC/Macintosh) decompilation project

This is the GitHub repository that contains all the decompiled code for WALL-E (2008), the video game. Specifically, for the Macintosh version of the game.

Watch snippets of [this video](https://www.youtube.com/watch?v=vGgQldClnlU) to get an idea of this game. Here's the [best any% speedrun](https://www.youtube.com/watch?v=djjySx_QwxQ) of the PC version of this game.

The PC and Macintosh versions of the WALL-E game are virtually indistinguishable, say for the Macintosh version being compiled and suited for running on Macintoshes in 2008, both the PowerPC and Intel x86 variants.

And if you wonder, the Mac build of this game is so obscure that it's usually left out from the list of platforms that the game is available on or considered the same to the PC version. *[I](https://github.com/ivanka2012) wouldn't fault those who forget about this version of the game.*

## The big why

It's the thrill of understanding something you are not meant to, and [I](https://github.com/ivanka2012) really want to understand the game that I have spent so much time with when I was a lot younger.

In addition to that, the insurmountable goal of decompiling ~17000 functions will always keep [me](https://github.com/ivanka2012) occupied. There will always be a milestone to reach, and never a "where now?"

## Contribution

You'll need the WALL-E disc released in the UK. Open the HFS+ partition on it and extract the x86 game executable from WALL-E.pkg.

There are no tools available to the public yet. Tools like tracking progress and seeing differences between disassemblies, not the disassembler used. They are simply not written to be easily distributable. 

This project needs people who can grab a disassembler and start decompiling. **If you are interested in contributing to this project and want to get your hands on the tools used for decompiling this game, please message theb4n4n4 (actual name: b4n4n4) on Discord.** You do not have to add me as a friend if you join the [Zouna Underground Discord server](https://discord.gg/CQgMNbYeUR).

## Dictionary

There are a few words that might confuse newcomers. Here are they:

| **Term** | **What do *we* mean by it** |
| --- | --- |
| **Asobo** | The principal developer behind this game. In this project, the code is the most interesting part of the game, and they were responsible for the code of the WALL-E game on the PC, the Mac and the PS2. |
| **THQ** | The original publisher of the WALL-E game. |
| **Disney** | Currently the publishers of the WALL-E game on Steam. If there's an entity legally concerned with this effort, it's them. |
| **ZOUNA** | This is the game engine of WALL-E. It powers most of Asobo's games, including their most recent releases as of date, Microsoft Flight Simulator 2020 and 2024 and the "A Plague Tale" series. [Read this](https://github.com/widberg/fmtk/wiki/TotemTech-ToonTech-Zouna-ACE-BSSTech-Opal-Timeline) to get a full rundown. | 

## Build

If you want to build this project, you'll need to have the following:
- A machine with OS X 10.4 (Tiger) installed. You'll probably want an x86 machine. Newer version might also work, like 10.5 and 10.6.
- Xcode 2.4 (not 2.4.1!). In Xcode, the only parts that are necessary are the OS X SDK, Apple's fork of gcc (version 5363), Apple's own linker (`ld`), assembler (`as`), strip tool (`strip`), and Make. These may or may not have toggleable options in the Xcode installer.

Once you have all of that, copy the contents of this repository to the OS X machine, open the Terminal app on the OS X machine, navigate to the directory of the copied repository and do this:

`make`

You should now have two binaries: `ZOUNA.executable` and `ZOUNA.stripped.executable`. These binaries, if everything went right, should have been compiled for the Intel x86 architecture. You'll probably want to match against `ZOUNA.executable`, as `ZOUNA.stripped.executable` has the exact same `strip -x` command ran on it as WALL-E Mac's game executable that was RtM.

## License

**The decompiled source code in this repository is non-free.** [I](https://github.com/ivanka2012) have no idea who it belongs to. Disney? Asobo? THQ's liquidators? *[me](https://github.com/ivanka2012)*?

Parts of the source code are from the [Microsoft Mixed Reality Toolkit](https://github.com/microsoft/MixedRealityToolkit/tree/main/SpatialUnderstanding/Src/Engine), which uses the MIT license. This contains a bunch of snippets from an early 2010's version of Asobo's ZOUNA fork. It has a few minor changes but it's very close to WALL-E's ZOUNA. How that got uploaded there, slapped on an MIT license and still be up 10 years later is beyond [me](https://github.com/ivanka2012). [I](https://github.com/ivanka2012) like this reference the most because it's straight from the horse's mouth.

Parts of the source code are lifted from [the Ratatouille (GBC) decompilation project](github.com/ZounaDecomp/RatDecomp). Thanks Vi and Sabe!

Parts of the source code are from ZOUNA.rar which contains most of the engine source code for [Shaun White Snowboarding](https://en.wikipedia.org/wiki/Shaun_White_Snowboarding). It also uses ZOUNA, the game engine for WALL-E. *Before you get your hopes up too high, this game has way too many differences compared to WALL-E because it's Ubisoft's fork, not Asobo's. It's a useful reference, but personally [I](https://github.com/ivanka2012) wouldn't bet my life on decompiling WALL-E on this reference alone.*