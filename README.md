# Kontain

![License](https://img.shields.io/badge/license-LICENSE-green)

## 📝 Description

Kontain is a streamlined Linux container utility designed to simplify the management and validation of containerized environments. Optimized for performance and ease of use, it provides developers with a robust toolset for testing container behavior, ensuring that applications run reliably across diverse Linux distributions.

## ✨ Features
- Ease-of-access for Linux container deployment
- Test case for ensured practical-use

## Why?
This was really just to refine my understanding of containerization on UNIX systems as well as becoming
more familiar with the Linux kernel process' involved around securing container enviroments

## 🚀 Run Commands

- **default_target**: `make default_target`
- **cmake_force**: `make cmake_force`
- **edit_cache**: `make edit_cache`
- **rebuild_cache**: `make rebuild_cache`
- **all**: `make all`
- **clean**: `make clean`
- **preinstall**: `make preinstall`
- **depend**: `make depend`
- **kontain**: `make kontain`
- **help**: `make help`
- **cmake_check_build_system**: `make cmake_check_build_system`


## 📁 Project Structure

```
.
├── CMakeLists.txt
├── LICENSE
├── Makefile
├── kernel
│   ├── kernel.c
│   └── kernel.h
├── kontain.c
├── kontain.h
├── resources.c
├── syscalls.c
└── test
    ├── subverting_networking.c
    ├── subverting_setfcap,c
    └── subverting_setfcap.c
```
