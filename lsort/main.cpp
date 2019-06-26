
#include <QDebug>
#include <sorttool.h>

int main(int, char*[])
{
    qDebug() << "Sort tool";

    SortTool st;
    //st.perform("D:/lang/progress/french/fr.nouns.lang");
    st.perform("D:/lang/progress/french/fr.verbs.lang");

    return 0;
}
