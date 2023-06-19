# DrMutoPackTool

What this is is (as of this writing) an unpacking tool, meant to be used with bigfiles ranging from 150MB to under 2GB *max*.

## Usage Instructions

The tool itself requires one argument. That can take form of an input file, an input folder, or a simple phrase that the tool supports. See **Usage Examples** below for more.

### Usage Examples

To use the tool on an input file.

~~~
DrMutoPackTool path/to/DRMUTO.000
~~~

To use the tool on an input folder.

~~~
DrMutoPackTool path/to/drmuto_folder
~~~

Beyond the above, the tool supports at least three parameters. If you run the tool from the command-line without any parameter, it will print out all of them. Let's go over them one-by-one.

- **help** - prints out a simple help message that shows the user how to use the tool.
- **more-help** - prints out an elaborate help message that gives more insight into how the tool should be used.
- **behind-the-scenes** - prints out an detailed message explaining the ins-and-outs of this tool.

So, if (for example) you want to read a help message, you'd type this in.

~~~
DrMutoPackTool help
~~~

