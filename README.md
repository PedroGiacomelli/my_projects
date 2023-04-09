# my_projects

The aim of this project is creating a program that can convert from excel to csv, and maintain the folder structure while convert it. Thus, it has to unwrape the folder, convert the file, if needed, and then pack it again. To do it, first, it is checked the item type in open_folders and, if the object is not a file, that is, a folder, a recursion takes over and repeats the process. When a folder is found, the unwrapper function acts convert the files.\
\
Some limitations are that it does not detect files when .xlsx or .xls does not support the operation and also when files has names that break commands. In the second case, to avoid this type of error, a filter of strings that may act like PS commands have to be performed.\
