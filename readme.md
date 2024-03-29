# fs (filesystem)

## Overview
This is a clone of the `ls` tool in Linux, written in C++. There is no reason to use this, it's a simple project to serve as an example of using the C++ std::filesystem library and use of GitHub Actions.

## Usage
```
Usage: lspp arguments [--help] [path [PATH ...]]

Positional Arguments:
path: Path(s) to list.

Optional Arguments:
-h, --help: Show this help message and exit.
```

Example output:

```
Total Files: 10 (4 files, 6 dirs)
Permissions        Last Write  Size   Name
___________  ________________  ____   ____
 drwxrwxrwx  2024-02-20 09:22     0   .git
 drwxrwxrwx  2024-02-20 09:22     0   .github
 -rwxrwxrwx  2024-02-20 09:22    24   .gitignore
 -rwxrwxrwx  2024-02-20 09:22    92   .gitmodules
 drwxrwxrwx  2024-02-20 09:28     0   .idea
 drwxrwxrwx  2024-02-20 09:25     0   cmake-build-debug
 -rwxrwxrwx  2024-02-20 09:22   396   CMakeLists.txt
 drwxrwxrwx  2024-02-20 09:22     0   fs
 -rwxrwxrwx  2024-02-20 09:22   781   readme.md
 drwxrwxrwx  2024-02-20 09:22     0   vendor
```

## Binaries
[![Continuous Build](https://github.com/pmann84/fs/actions/workflows/continuous_build.yml/badge.svg)](https://github.com/pmann84/fs/actions/workflows/continuous_build.yml)
[![Release Build](https://github.com/pmann84/fs/actions/workflows/release_build.yml/badge.svg)](https://github.com/pmann84/fs/actions/workflows/release_build.yml)
