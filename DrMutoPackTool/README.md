# DrMutoPackTool

What this is is (as of this writing) an unpacking tool, meant to be used with bigfiles ranging from 150MB to under 2GB *max*. Meant for use with the **PlayStation2** and **Xbox** versions of **Dr. Muto**.

## Usage Instructions

The tool itself requires one argument. That can take form of an input file, an input folder, or a simple phrase that the tool supports. See [**Usage Examples**](#usage-examples) below for more.

### Usage Examples

To use the tool on an input file.

~~~
DrMutoPackTool path/to/DRMUTO.000
~~~

To use the tool on an input folder.

~~~
DrMutoPackTool path/to/drmuto_folder
~~~

To learn more about how the tool handles either of them, see [**Further Usage**](#further-usage) down below.

Beyond the above, the tool supports at least three parameters. If you run the tool from the command-line without any parameter, it will print out all of them. Let's go over them one-by-one.

- **help** - prints out a simple help message that shows the user how to use the tool.
- **more-help** - prints out an elaborate help message that gives more insight into how the tool should be used.
- **behind-the-scenes** - prints out an detailed message explaining the ins-and-outs of this tool.

So, if (for example) you want to read a help message, you'd type this in.

~~~
DrMutoPackTool help
~~~

## Additional Info

Here are additional insights into the ins-and-outs of the tool.

### Further Usage

When the first argument takes the form of an input file or folder, the tool itself will check for the TOC file (DRMUTO.000) and will see if it exists on the same place said file or folder is in.

If it does, it will load that first and will upload as much of that data into memory for further usage. At which point said uploaded data will be prepared for further usage.

When all is said and done, the tool will then show you two modes and ask you to type only one. Let's go over them one-by-one.

- **list** - prints out basic info of all existing files with the uploaded TOC data as a base.
- **x** - extracts all existing files into individual files of their own from the bigfiles with the uploaded TOC data as a base.
