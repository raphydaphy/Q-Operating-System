// fs.c -- Defines the interface for and structures relating to the virtual file system.
//         Written for JamesM's kernel development tutorials.

#include "fs.h"

fs_node_t *fs_root = 0; // The root of the filesystem.

uint32 read_fs(fs_node_t *node, uint32 offset, uint32 size, uint8 *buffer)
{
    // Has the node got a read callback?
    if (node->read != 0)
        return node->read(node, offset, size, buffer);
    else
        return 0;
}

uint32 write_fs(fs_node_t *node, uint32 offset, uint32 size, uint8 *buffer)
{
    // Has the node got a write callback?
    if (node->write != 0)
        return node->write(node, offset, size, buffer);
    else
        return 0;
}

void open_fs(fs_node_t *node, uint8 read, uint8 write)
{
    UNUSED(read);
    UNUSED(write);
    // Has the node got an open callback?
    if (node->open != 0)
        node->open(node);
}

void close_fs(fs_node_t *node)
{
    // Has the node got a close callback?
    if (node->close != 0)
        node->close(node);
}

struct dirent *readdir_fs(fs_node_t *node, uint32 index)
{
    // Is the node a directory, and does it have a callback?
    if ( (node->flags&0x7) == FS_DIRECTORY &&
         node->readdir != 0 )
        return node->readdir(node, index);
    else
        return 0;
}

fs_node_t *finddir_fs(fs_node_t *node, char *name)
{
    // Is the node a directory, and does it have a callback?
    if ( (node->flags&0x7) == FS_DIRECTORY &&
         node->finddir != 0 )
        return node->finddir(node, name);
    else
        return 0;
}

