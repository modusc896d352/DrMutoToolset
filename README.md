# DrMutoToolset

## Introduction

**DrMutoToolset** is a set of programs (henceforth referred to as a "toolset") meant for dealing with asset files present in the multi-platform (for 2002) console game **Dr. Muto**.

As the whole repository in which this toolset is based on is WIP and I'm just barely started with C++ as a programming language, the whole thing will look barebones to you. No license, no "building" section, nothing.

I cannot give any building instructions at this time, but what you do need to know for now is that this was programmed in **Visual Studio 2022 Version 17.6.3**, with the **C++ desktop extension** installed to make this a reality.

You also need to set the **C++ language standard** to **C++17** or later. The entire toolset is being programmed with **C++17** (again) as a base since this is how things'll be done here from this point onwards.

The entire toolset was tested with **Windows 10 Pro 22H2** as its operating system, with **64-bit support** based on the **x86-64 instruction set**.

## The Titular Toolset

As of this writing, the toolset consists of the following programs:

- [**DrMutoPackTool**](DrMutoPackTool/README.md) - A tool for unpacking all files from bigfiles based on an input name. A good choice for dealing with files from the **PlayStation2** and **Xbox** versions of the game.

In their current state, said programs are all meant to be run on the command-line terminal. Running any of the programs without arguments will list a couple of parameters that the programs themselves support.

## Lasting Words

While I've made a lot of effort into ensuring the toolset itself is as bug-free as possible, there are times when you may happen to step in to some oversight I may not have considered when making said toolset. So, just in case you run into a bug with one of the tools outlined above, then by all means *do* open an issue about it! That would help me a lot.

If you intend to contribute more code, be it by adding new features, fixing bugs or just improving the overall code, please note that I haven't outlined anything that would get you up-to-speed with the ins-and-outs of the programs so I cannot give you the full picture of how you're going to contribute yet. That said, if you have something that enhances the already-existing codebase in some way, then by all means *do* open an pull request about it! Again, I'd be grateful for your help.

Happy tinkering!
