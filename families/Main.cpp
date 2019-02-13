
#include <QDir>
#include <TextLoader.h>
#include <Words.h>
#include <iostream>

int main( int /*argc*/, char** /*argv*/ )
{
    /*
    TextLoader loader;
    loader.Load(QDir::currentPath()+"/families.txt");
    QString str;
    std::cout << "Max length = " << loader.CalcMaxLength(&str) << std::endl;
    std::cout << "Max length arg = " << str.toStdString() << std::endl;

    Words words;
    loader.ConvertToWords(words);
    words.Save(QDir::currentPath()+"/families.dat");*/


    Words words;
    words.Load(QDir::currentPath()+"/families.dat");
    std::cout << words.Initial("coming").join(" ").toStdString() << std::endl;
    QStringList ww = words.CheckText("D:\\asl\\lang3\\lang\\texts\\The Wonderful Wizard of Oz.txt");
    std::cout << "There are " << ww.size() << " words:" << std::endl;
    std::cout << ww.join(", ").toStdString() << std::endl;

    return 0;
}
