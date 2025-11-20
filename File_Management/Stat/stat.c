/*


✅ What is stat()?

stat() is a system call that retrieves information about a file using its filename/path.


It gives you:

file size
file permissions
owner
inode number
timestamps
file type (directory, regular file, symlink, etc.)


❓ Why we have to use stat()?
Because you cannot get file information using open(), read(), or write().

Only stat() provides complete metadata.


🔧 How to use stat()?

stat("file.txt", &info);

filename (path)
a pointer to struct stat


📌 Where to use stat()?

Check if file exists
Check file type (directory? regular file?)
Get file size
Implement commands like ls, find, cp, mv, rm
Before reading the file


*/