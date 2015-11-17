// fs.h -- Defines the interface for and structures relating to the virtual file system.
//         Written for JamesM's kernel development tutorials.

#ifndef FS_H
#define FS_H

#include "intTypeDefs.h"

#define FS_FILE        0x01
#define FS_DIRECTORY   0x02
#define FS_CHARDEVICE  0x03
#define FS_BLOCKDEVICE 0x04
#define FS_PIPE        0x05
#define FS_SYMLINK     0x06
#define FS_MOUNTPOINT  0x08 // Is the file an active mountpoint?

#define MAX_FNAME_LEN  128

struct fs_node;

// These typedefs define the type of callbacks - called when read/write/open/close
// are called.
typedef uint32 (*read_type_t)(struct fs_node*,uint32,uint32,uint8*);
typedef uint32 (*write_type_t)(struct fs_node*,uint32,uint32,uint8*);
typedef void (*open_type_t)(struct fs_node*);
typedef void (*close_type_t)(struct fs_node*);
typedef struct dirent * (*readdir_type_t)(struct fs_node*,uint32);
typedef struct fs_node * (*finddir_type_t)(struct fs_node*,char *name);

typedef struct fs_node
{
    char name[MAX_FNAME_LEN]; // The filename.
    uint32 mask;        // The permissions mask.
    uint32 uid;         // The owning user.
    uint32 gid;         // The owning group.
    uint32 flags;       // Includes the node type. See #defines above.
    uint32 inode;       // This is device-specific - provides a way for a filesystem to identify files.
    uint32 length;      // Size of the file, in bytes.
    uint32 impl;        // An implementation-defined number.
    read_type_t read;
    write_type_t write;
    open_type_t open;
    close_type_t close;
    readdir_type_t readdir;
    finddir_type_t finddir;
    struct fs_node *ptr; // Used by mountpoints and symlinks.
} fs_node_t;

struct dirent
{
    char name[128]; // Filename.
    uint32 ino;     // Inode number. Required by POSIX.
};

extern fs_node_t *fs_root; // The root of the filesystem.

// Standard read/write/open/close functions. Note that these are all suffixed with
// _fs to distinguish them from the read/write/open/close which deal with file descriptors
// , not file nodes.
uint32 read_fs(fs_node_t *node, uint32 offset, uint32 size, uint8 *buffer);
uint32 write_fs(fs_node_t *node, uint32 offset, uint32 size, uint8 *buffer);
void open_fs(fs_node_t *node, uint8 read, uint8 write);
void close_fs(fs_node_t *node);
struct dirent *readdir_fs(fs_node_t *node, uint32 index);
fs_node_t *finddir_fs(fs_node_t *node, char *name);

#endif
