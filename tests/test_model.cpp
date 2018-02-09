#include <QString>
#include <QtTest>

class TestModel : public QObject
{
    Q_OBJECT

public:
    TestModel();

private Q_SLOTS:
    void test_load();
};

TestModel::TestModel()
{
}

void TestModel::test_load()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(TestModel)

#include "test_model.moc"
