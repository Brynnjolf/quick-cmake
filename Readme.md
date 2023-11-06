I made this when switching to vim so that I can quickly generate cmake project structures from the cmd line.

usage: `quick-cmake <path> [-l] [<name>]`

`-l` creates a library, if omited, creates an executable.
optional `<name>` sets the library/executable/project name. If omitted, will simply use the name of the `<path>` directory
