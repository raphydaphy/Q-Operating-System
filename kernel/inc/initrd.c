#include "initrd.h"

initrd_header_t *initrd_header;     // The header.
initrd_file_header_t *file_headers; // The list of file headers.
fs_node_t *initrd_root;             // Our root directory node.
fs_node_t *initrd_dev;              // We also add a directory node for /dev, so we can mount devfs later on.
fs_node_t *initrd_tmp;              // We also add a directory node for /tmp
fs_node_t *root_nodes;              // List of file nodes.
uint16 nroot_nodes;                 // Number of file nodes.
fs_node_t writerFile;

struct dirent dirent;

static uint32 initrd_read(fs_node_t *node, uint32 offset, uint32 size, uint8 *buffer)
{
    initrd_file_header_t header = file_headers[node->inode];
    if (offset > header.length)
    {
        return 0;
    }
    if (offset+size > header.length)
    {
        size = header.length-offset;
    }
    memcpy(buffer, (uint8*) (header.offset+offset), size);
    return size;
}

static uint32 initrd_write(fs_node_t *node, uint32 offset, uint32 size, uint8 *buffer)
{
    initrd_file_header_t header = file_headers[node->inode];

    /*
    if (offset > header.length)
    {
        return 0;
    }
    */

    if (offset+size > header.length)
    {
        size = header.length-offset;
    }


    //print(file_headers[node->inode],red);

    // file_headers[node->inode] = (uint8) *buffer;
    printint(buffer[0], blue);
    makeFile("Writer", size);

    // memcpy(file_headers[node->inode], (uint8*) (header.offset+offset), size);
    return size;
}



static struct dirent *initrd_readdir(fs_node_t *node, uint32 index)
{
    if (node == initrd_root)
    {
        switch(index)
        {
        case 0:
            strcpy(dirent.name, "dev");
            dirent.name[3] = 0;
            dirent.ino = 0;
            return &dirent;
        case 1:
            strcpy(dirent.name, "tmp");
            dirent.name[3] = 0;
            dirent.ino = 1;
            return &dirent;
        }
    }

    if (index-1 >= nroot_nodes)
    {
        return 0;
    }
    strcpy(dirent.name, root_nodes[index-1].name);
    dirent.name[strlen(root_nodes[index-1].name)] = 0;
    dirent.ino = root_nodes[index-1].inode;
    return &dirent;
}

static fs_node_t *initrd_finddir(fs_node_t *node, char *name)
{
    if (node == initrd_root)
    {
        if(streql(name, "dev"))
            return initrd_dev;
        if(streql(name, "tmp"))
            return initrd_tmp;
    }
    int i;
    for (i = 0; i < nroot_nodes; i++)
    {
        if (streql(name, root_nodes[i].name))
        {
            return &root_nodes[i];
        }
    }
    return 0;
}

fs_node_t* makeFile(string name, uint32 size) {
    fs_node_t* newDoc = (fs_node_t*)kmalloc(sizeof(fs_node_t));
    strcpy(newDoc->name, name);
    newDoc->mask = newDoc->uid = newDoc->gid = 0;
    newDoc->length = size; // Good idea...
    newDoc->inode = initrd_header->nfiles + 1;
    newDoc->flags = FS_FILE;
    newDoc->read = &initrd_read;
    newDoc->write = &initrd_write;
    newDoc->readdir = 0;
    newDoc->finddir = 0;
    newDoc->open = 0;
    newDoc->close = 0;
    newDoc->impl = 0;
    newDoc->ptr = 0;
    return newDoc;
}

fs_node_t* makeDir(string name) {
    fs_node_t* newDir = (fs_node_t*)kmalloc(sizeof(fs_node_t));
    strcpy(newDir->name, name);
    newDir->mask = newDir->uid = newDir->gid = newDir->inode = newDir->length = 0;
    newDir->flags = FS_DIRECTORY;
    newDir->read = 0;
    newDir->write = 0;
    newDir->open = 0;
    newDir->close = 0;
    newDir->readdir = &initrd_readdir;
    newDir->finddir = &initrd_finddir;
    newDir->ptr = 0;
    newDir->impl = 0;
    return newDir;
}

fs_node_t *initialize_initrd(uint32 location)
{
    // Initialise the main and file header pointers and populate the root directory.
    initrd_header = (initrd_header_t *)location;
    file_headers = (initrd_file_header_t *) (location+sizeof(initrd_header_t));

    // Initialise the root directory.
    initrd_root = makeDir("initrd.img");

    // Initialise the /dev directory (required!)
    initrd_dev = makeDir("dev");
    
    // Initialise the /tmp directory (Just cuz!)
    initrd_tmp = makeDir("tmp");

    root_nodes = (fs_node_t*)kmalloc(sizeof(fs_node_t) * initrd_header->nfiles);
    nroot_nodes = initrd_header->nfiles;

    // For every file...
    uint32 i;
    for (i = 0; i < initrd_header->nfiles; i++)
    {
        // Edit the file's header - currently it holds the file offset
        // relative to the start of the ramdisk. We want it relative to the start
        // of memory.
        file_headers[i].offset += location;
        // Create a new file node.
        strcpy((string)root_nodes[i].name, (string)&file_headers[i].name);
        root_nodes[i].mask = root_nodes[i].uid = root_nodes[i].gid = 0;
        root_nodes[i].length = file_headers[i].length;
        root_nodes[i].inode = i;
        root_nodes[i].flags = FS_FILE;
        root_nodes[i].read = &initrd_read;
        root_nodes[i].write = &initrd_write;
        root_nodes[i].readdir = 0;
        root_nodes[i].finddir = 0;
        root_nodes[i].open = 0;
        root_nodes[i].close = 0;
        root_nodes[i].impl = 0;
    }
    return initrd_root;
}
