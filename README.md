# smb4kctl
simple console application to mount samba shares using [smb4k](smb4k) library

Mount with
```bash
$ smb4kctl mount smb://server/share
```
Unmount with
```bash
$ smb4kctl umount smb://server/share
```
That's all :)

You need smb4k headers to build this.

[smb4k]: http://sourceforge.net/projects/smb4k/
