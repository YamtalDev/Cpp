/******************************************************************************

    Writer: Tal Aharon

    Reviewer: Yotam.

    Date: 02.08.2023

******************************************************************************/
#include <iostream>             /* std::           */

#include "composite.hpp"        /* Internal API    */
/*****************************************************************************/
using namespace ilrd_rd141;
void AddFilesAndPrintTest(void);
void AddFilesAndCloneTest(void);
void AddFilesAndRemoveTest(void);
/*****************************************************************************/
int main(void)
{
    AddFilesAndPrintTest();
    AddFilesAndCloneTest();
    AddFilesAndRemoveTest();
    std::cout << "Passed" << std::endl;
    return (0);
}
/*****************************************************************************/
void AddFilesAndPrintTest(void)
{
    std::cout << "==== AddFilesAndPrintTest ====\n" << std::endl;
    
    File file1("file1.txt");
    File file2("file2.txt");
    Dir dir1("dir1");
    Dir dir2("dir2");

    dir1.AddIEntry(file1);
    dir1.AddIEntry(file2);

    dir2.AddIEntry(file1);
    dir2.AddIEntry(dir1);

    dir2.Print();
}
/*****************************************************************************/
void AddFilesAndRemoveTest(void)
{
    std::cout << "\n======= AddFilesAndRemoveTest ========\n" << std::endl;

    File file1("file1.txt");
    File file2("file2.txt");
    Dir dir1("dir1");
    Dir dir2("dir2");

    dir1.AddIEntry(file1);
    dir1.AddIEntry(file2);

    dir2.AddIEntry(file1);
    dir2.AddIEntry(dir1);

    dir2.Print();

    std::cout << "\n---- Removing file1.txt from dir2 ----\n" << std::endl;
    dir2.RemoveIEntry("file1.txt");
    dir2.Print();
    std::cout << "\n------- Removing dir1 from dir2 ------\n" << std::endl;
    dir2.RemoveIEntry("dir1");
    dir2.Print();
    std::cout << "\n======================================\n" << std::endl;

}
/*****************************************************************************/
void AddFilesAndCloneTest(void)
{
    std::cout << "\n======= Clone dirs and files test =====\n" << std::endl;
    File file1("file1.txt");
    File file2("file2.txt");
    Dir dir1("dir1");
    Dir dir2("dir2");

    dir1.AddIEntry(file1);
    dir1.AddIEntry(file2);

    dir2.AddIEntry(file1);
    dir2.AddIEntry(dir1);

    std::cout << "Original directory:" << std::endl;
    dir2.Print();

    Dir* clonedDir = dir2.clone();

    std::cout << "\nCloned directory:" << std::endl;
    clonedDir->Print();
    delete clonedDir;
}
/*****************************************************************************/
