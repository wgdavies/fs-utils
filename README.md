# FSLS - Fast/Filesystem List

This is a fast file/directory lister/stats tool that [will] feature the rapid collection of directory information. For example, a common usage is to print the number of files under a given directory, where the number is expected to exceed e.g 100,000. Using traditional filesystem tools (`ls`, `find`, &c) may yield results in hours whereas `fsls` should be able to yield results in minutes (given minimal processing, &c).
