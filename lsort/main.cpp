
#include <QDebug>
#include <sorttool.h>

int main(int, char*[])
{
    qDebug() << "Sort tool";

    SortTool st;
    st.perform("D:/lang/progress/french/fr.nouns.lang");

    return 0;
}
