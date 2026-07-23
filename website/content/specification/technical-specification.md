---
author: Ivan Hawkes
date: '2026-05-07'
description: Technical Specification
title: Technical Specification
type: specification
---

# Technical Specification

Explain the purpose of a technical specification.

## Build Tools

The Space Truckers SDK will be written in c++ and using Unreal
Engine 5.7.x for the framework.

The team will use JetBrains Rider IDE version 2026.1.x.

The team will use the recommended build tools and compilers for an Unreal
Engine 5.7.x project. At the time of writing this is the Microsoft MS Build
tool and the v134 series of libraries for the compiler.

The build will produce 64 bit binaries.

## Build Environment

In order to start building the project each team member will need to install
a build environment on their local machine.

[Git](https://git-scm.com/install/windows)

[Microsoft Visual Studio 2022](https://visualstudio.microsoft.com/vs/older-downloads/)

[JetBrains Rider 2026.1](https://www.jetbrains.com/rider/)

You **must** install VS 2022 first and be sure to follow the instructions
for an installation which can be used to build Unreal Engine projects.

At a minimum this means installing the c++ build tools, and the c++ tools
for game programming. There are other requirements you will need to research.

You are advised to install
[Microsoft Terminal](https://apps.microsoft.com/detail/9n0dx20hk701?hl=en-GB&gl=AU)
which is an improved terminal client for Windows.

Microsoft made a slightly less terrible shell called
[Powershell 7](https://learn.microsoft.com/en-us/powershell/scripting/install/install-powershell-on-windows?view=powershell-7.6)
which you are advised to install.

Finally, for the diehard Linux users, get back some of that lost control by 
installing [Windows Subsystem for Linux](https://learn.microsoft.com/en-us/windows/wsl/install)
You can host several popular Linux distributions inside of Windows and 
access the Windows filesystem whilst using your beloved shells, aliases and 
scripts.

## Documentation

The documentation is produced by [HUGO](https://gohugo.io/) a static site
generator. This is a standalone executable written in [Go](https://go.dev/),
also known as Golang (so search engines can find it).

You are advised to have both installed, though only HUGO is strictly
required, and only if you plan to update the static website. These tools
will work on Linux and Windows.

The best way to get both up to date is to [download](https://go.dev/dl/) and
install Go first. After that you can use the go tools to download and
install the latest version of HUGO. Make sure you follow the Go installation
guides, since Go relies on environment variables being set.

It is advised that you follow standard practice. The GOPATH is typically
installed in your home folder. Be sure to add the GOPATH/bin folder to your
PATH environment variable so it's available to execute without typing in a
fully qualified path filename.

The data files for the project are written using YAML. They are kept in separate YAML files that are then merged together to form an uber YAML file. This is done so we can keep the file sizes manageable and make it easier for team members to make changes without overwriting each other's efforts. The files are then merged so we can apply the DRY principle, which needs the YAML anchor and references to be in the same file.

The processing is performed by [yq](https://github.com/mikefarah/yq). It is available for Windows and Linux.

```
# Install yq
go install github.com/mikefarah/yq/v4@latest
```
