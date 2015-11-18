Using the make `initrd.img` utility
=====

Compile it normally (no `-ffrestanding`) and place files (not folders) as parameters twice like the following.

```
$ ./compiled_bin file1 file1 file2 file2
```

A file called `initrd.img` should appear. Copy that in the `kernel/q/boot/` directory before running the build.

But what is this `initrd.img` for anyway?
=====

Proof of a working `Virtual File System`. Currently does not do much...

Oh and also, you will be ASSERT-ed in runtime if you do not follow the instructions...

