
#include "../SmartDB/SmartDB.hpp"
#include "../SmartDB/JsonCpp.hpp"
#include "Timer.hpp"

void TestJson(SmartDB& db, const string& sqlinsert)
{
    //����ͨ��jsoncpp��װ������json����Ĵ���
    rapidjson::StringBuffer buf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buf);
    writer.StartArray();
    for (size_t i = 0; i < 10; i++)
    {
        writer.StartObject();
        writer.String("ID");
        writer.Int(i + 1);

        writer.String("Name");
        writer.String("Peter");

        writer.String("Address");
        writer.String("Zhuhai");
        writer.EndObject();
    }
    writer.EndArray();

    //auto r = db.ExcecuteJson(sqlinsert, buf.GetString());
}

void TestJsonCpp()
{
    SmartDB db;
    db.Open("test.db");
    const string sqlcreat = "CREATE TABLE if not exists TestInfoTable(ID INTEGER NOT NULL, KPIID INTEGER, CODE INTEGER, V1 INTEGER, V2 INTEGER, V3 REAL, V4 TEXT);";
    if (!db.Excecute(sqlcreat))
        return;

    Timer t;
    JsonCpp jcp;
    jcp.StartArray();
    for (size_t i = 0; i < 10; i++)
    {
        jcp.StartObject();
        jcp.WriteJson("ID", i);
        jcp.WriteJson("KPIID", i);
        jcp.WriteJson("CODE", i);
        jcp.WriteJson("V1", i);
        jcp.WriteJson("V2", i);
        jcp.WriteJson("V3", i + 1.25);
        jcp.WriteJson("V4", "it is a test");

        jcp.EndObject();
    }
    jcp.EndArray();
    const string sqlinsert = "INSERT INTO TestInfoTable(ID, KPIID, CODE, V1, V2, V3, V4) VALUES(?, ?, ?, ?, ?, ?, ?);";
    bool r = db.ExcecuteJson(sqlinsert, jcp.GetString());
    cout << t.elapsed() << endl;
    t.reset();
    //100w 3.5-4������

    auto p = db.Query("select * from TestInfoTable");
    cout << t.elapsed() << endl;
    t.reset();
	std::cout << typeid(p).name() << std::endl;
    rapidjson::Document& doc = *p;
	if (doc.IsArray()) {
		std::cout << "is array" << std::endl;
		for (auto& its : doc.GetArray()) {
			for (auto& it = its.MemberBegin(); it != its.MemberEnd(); ++it) {
				//std::cout << it->name.GetString() << ": " << it->value.GetType() << std::endl;
			}
		}
	}
	if (doc.IsObject()) {
		std::cout << "is object" << std::endl;
		for (auto& its : doc.GetObject()) {

		}
	}
    //for (size_t i = 0, len = doc.Size(); i < len; i++)
    //{
    //    for (size_t i = 0, size = doc[i].Size(); i < size; ++i)
    //    {

    //    }
    //}
    cout << t.elapsed() << endl;
    cout << "size: " << p->Size() << endl;
}

void TestCreateTable()
{
    SmartDB db;
    db.Open("test.db");

    const string sqlcreat = "CREATE TABLE if not exists PersonTable(ID INTEGER NOT NULL, Name Text, Address BLOB);";
    if (!db.Excecute(sqlcreat))
        return;

    const string sqlinsert = "INSERT INTO PersonTable(ID, Name, Address) VALUES(?, ?, ?);";
    int id = 2;
    string name = "Peter";
    string city = "zhuhai";
    blob bl = { city.c_str(), city.length() + 1 };
    if (!db.Excecute(sqlinsert, id, "Peter", nullptr))
        return;

    TestJson(db, sqlinsert);

    auto r = db.ExcecuteTuple(sqlinsert, std::forward_as_tuple(id, "Peter", bl));
    char* json;
    string strQery = "select * from PersonTable";
    //for (size_t i = 0; i < 10000; i++)
    //{
    //	db.Query(strQery, json);
    //}

    const string str = "select Address from PersonTable where ID=2";
    auto pname = db.ExecuteScalar<string>(str);
    auto l = strlen(pname.c_str());
    cout << pname << endl;
}

void TestPerformance()
{
    SmartDB db;
    db.Open("test.db");
    const string sqlcreat = "CREATE TABLE if not exists TestInfoTable(ID INTEGER NOT NULL, KPIID INTEGER, CODE INTEGER, V1 INTEGER, V2 INTEGER, V3 REAL, V4 TEXT);";
    if (!db.Excecute(sqlcreat))
        return;

    Timer t;
    const string sqlinsert = "INSERT INTO TestInfoTable(ID, KPIID, CODE, V1, V2, V3, V4) VALUES(?, ?, ?, ?, ?, ?, ?);";
    bool ret = db.Prepare(sqlinsert);
    db.Begin();
    for (size_t i = 0; i < 1000; i++)
    {
        ret = db.ExcecuteArgs(i, i, i, i, i, i + 1.25, "it is a test");
        if (!ret)
            break;
    }

    if (ret)
        db.Commit(); //�ύ����
    else
        db.RollBack(); //�ع�

    cout << t.elapsed() << endl;
    t.reset();
    //100w 3.5-4������

    auto p = db.Query("select * from TestInfoTable");

    cout << t.elapsed() << endl;
    cout << "size: " << p->Size() << endl;
    //100W 4������
}

int main(int argc, char* argv[])
{
    TestJsonCpp();
    TestPerformance();
    TestCreateTable();
    return 0;
}
