# small kernel

## Building
The build system isn't cursed, but the toolchain and OS tuple is: you need an AArch64 OS (kernel and userspace) and ARM's toolchain.
The instructions in this section cover RPiOS.

### Installing the userspace
The easiest way to do this is by installing `raspbian-nspawn-64`:
```sh
sudo apt-get update
sudo apt-get install -y raspbian-nspawn-64
```

You might have to reboot your system to complete the instalation. After that, install the build and testing dependencies:
```sh
sudo apt-get install -y make qemu-system-aarch64 tar
```

The following steps should be performed **inside** the container.

### Installing the toolcahin
Download the [GNU Toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-a/downloads)
provided by ARM (`aarch64-none-elf` target) for AArch64 hosts, and untar it under a `toolchain` directory:
```sh
tar -xJf gcc-arm-10.*-aarch64-aarch64-none-elf.tar.xz -C toolchain
```

### Configuring
Copy `config.def.mk` to `config.mk` and edit it as needed. For example, edit the `PREFIX` variable to the path to your toolchain and its prefix:
```makefile
PREFIX:=/path/to/toolchain/gcc/aarch64-none-elf-
```

And finally, to actually build the kernel, simply do `make`.

## Testing
To test the kernel, do `make test`.

## License
The optimized routines (located under `arm-routines`) by Arm Limited are licensed under a [MIT license](https://github.com/Alvarito050506/smol-kernel/blob/master/arm-routines/LICENSE). The rest of the code is licensed under the same [MIT license](https://github.com/Alvarito050506/smol-kernel/blob/master/LICENSE).

Great part of the current code is based on the [`raspberry-pi-os`](https://s-matyukevich.github.io/raspberry-pi-os/) tutorial by @s-matyukevich and the [`raspi3-tutorial`](https://github.com/bztsrc/raspi3-tutorial) by @btzsrc.
