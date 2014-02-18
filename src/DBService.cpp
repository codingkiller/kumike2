#include "DBService.hpp"


#include <bb/cascades/AbstractPane>
#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/data/DataAccessError>
#include <bb/system/SystemDialog>

#include <QtSql/QtSql>
#include <QDebug>

using namespace bb::cascades;
using namespace bb::data;
using namespace bb::system;


/*App::App()
    : m_dataModel(0)
{
    initDataModel();
    QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);
    qml->setContextProperty("_app", this);
    AbstractPane *root = qml->createRootObject<AbstractPane>();
    Application::instance()->setScene(root);
    const bool dbInited = initDatabase();
    root->setProperty("databaseOpen", dbInited);
}*/
DBService::DBService(){
	DB_PATH = "./data/kumikeDatabase.db";
	initDataModel();
	initDatabase();
	//this->readRecords();
}
void DBService::initDataModel()
{
    m_dataModel = new QListDataModel<busline*>();
//    m_dataModel->setSortingKeys(QStringList() << "searchtime");
//    m_dataModel->setGrouping(ItemGrouping::None);
}
//! [1]
bool DBService::initDatabase()
{
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(DB_PATH);
    if (database.open() == false) {
        const QSqlError error = database.lastError();
   //     alert(tr("Error opening connection to the database: %1").arg(error.text()));
        qDebug() << "\nDatabase NOT opened.";
        return false; // return as if we cannot open a connection to the db, then below calls
                      // will also fail
    }
    sqlda = new SqlDataAccess(DB_PATH);
/*
    sqlda->execute("DROP TABLE IF EXISTS search_records");
        if(!sqlda->hasError()) {
            qDebug() << "Table dropped.";
        } else {
            const DataAccessError error = sqlda->error();
            alert(tr("Drop table error: %1").arg(error.errorMessage()));//.arg(error.text()));
        }
*/


    const QString createSQL = "CREATE TABLE if not exists search_records "
                              "  (record_id INTEGER PRIMARY KEY AUTOINCREMENT, "
                              "  line_name VARCHAR, "
    							"  start_station VARCHAR, "
    							"  end_station VARCHAR, "
    							"  price VARCHAR, "
    							"  search_time INTEGER, "
    						//	" sid VARCHAR, "
                                "  city_id VARCHAR);";//city_id line_name 加复合索引，search_time加单列索引
    sqlda->execute(createSQL);
    if(!sqlda->hasError()) {
       // qDebug() << "Table created.";
    } else {
        const DataAccessError error = sqlda->error();
   //     alert(tr("Create table error: %1").arg(error.errorMessage()));//.arg(error.text()));
        return false;
    }

    return true;
}
int DBService::findRecordId(const QString city_id,const QString line_name){
  //  SqlDataAccess *sqlda = new SqlDataAccess(DB_PATH);
    const QString sqlQuery = "SELECT record_id FROM search_records where city_id=:city_id  and line_name=:line_name";
    QVariantMap bindings;
        bindings["city_id"] = city_id;
        bindings["line_name"] = line_name;
    QVariant result = sqlda->execute(sqlQuery,bindings);
    if (!sqlda->hasError()) {
        int recordsRead = 0;
        if( !result.isNull() ) {
            QVariantList list = result.value<QVariantList>();

            recordsRead = list.size();
            for(int i = 0; i < recordsRead; i++) {
            	QVariantMap map = list.at(i).value<QVariantMap>();
            	return map["record_id"].toInt();
              //  return list.at(i).toInt();
            }
        }

        qDebug() << "findRecordId:find  " << recordsRead << " records succeeded";

        if (recordsRead == 0) {
         //   alert(tr("The customer table is empty."));
        }
    } else {
   //     alert(tr("Read records failed: %1").arg(sqlda->error().errorMessage()));
    }
    return 0;
}
bool DBService::createRecord(const busline* busline)
{
    if (busline->getLineName().trimmed().isEmpty() && busline->getEndStation().trimmed().isEmpty()) {
   //     alert(tr("You must provide a line_name or end_station."));
        return false;
    }
//    SqlDataAccess *sqlda = new SqlDataAccess(DB_PATH);
    QVariantList contact;
    contact << busline->getLineName() << busline->getStartStation() << busline->getEndStation() << busline->getPrice() << 1 << busline->getCityId();
    sqlda->execute("INSERT INTO search_records"
                  "    (line_name, start_station,end_station,price,search_time,city_id) "
                  "    VALUES (:line_name, :start_station,:end_station,:price,:search_time,:city_id)", contact);
    bool success = false;
    if(!sqlda->hasError()) {
     //   alert(tr("Create record succeeded."));
        success = true;
    } else {
        const DataAccessError error = sqlda->error();
   //     alert(tr("Create record error: %1").arg(error.errorMessage()));
    }
    return success;
}

bool DBService::updateRecord(const int record_id)
{
  //  SqlDataAccess *sqlda = new SqlDataAccess(DB_PATH);
    const QString sqlCommand = "UPDATE search_records "
                               "    SET search_time = search_time+1"
                               "    WHERE record_id = :record_id";
    QVariantMap bindings;
    bindings["record_id"] = record_id;
    bool updated = false;
    sqlda->execute(sqlCommand, bindings);
    if (!sqlda->hasError()) {
    	updated = true;
    	//alert(tr("Customer with id=%1 was updated.").arg(record_id));
    	/*
        // 5. Verify that a customer with that ID exists.
        const QString sqlVerify = "SELECT firstName FROM customers WHERE customerID = :customerID";
        QVariantList args;
        args << customerIDKey;
        QVariant result = sqlda->execute(sqlVerify, args);
        if (!result.isNull() && result.value<QVariantList>().size() > 0) {
            alert(tr("Customer with id=%1 was updated.").arg(customerID));
            updated = true;
        } else {
            alert(tr("Customer with id=%1 was not found.").arg(customerID));
        }
    */} else {
   //     alert(tr("SQL error: %1").arg(sqlda->error().errorMessage()));
    }

    return updated;
}

bool DBService::deleteRecord(const int record_id)
{
  //  SqlDataAccess *sqlda = new SqlDataAccess(DB_PATH);
    /*const QString sqlVerify = "SELECT firstName FROM customers WHERE customerID = :customerID";
    QVariantList argsList;
    argsList << customerIDnumber;
    QVariant verificationResult = sqlda->execute(sqlVerify, argsList);
    if(verificationResult.isNull() || verificationResult.value<QVariantList>().size() == 0) {
        alert(tr("Customer with id=%1 was not found.").arg(customerID));
        return false;
    }*/
    QVariantMap bindings;
    bindings["record_id"] = record_id;
    sqlda->execute("DELETE FROM search_records WHERE record_id=:record_id", bindings);
    bool deleted = false;
    if (!sqlda->hasError()) {
    	deleted = true;
    //	alert(tr("Customer with id=%1 was deleted.").arg(record_id));
        /*verificationResult = sqlda->execute(sqlVerify, argsList);
        if (!verificationResult.isNull() && verificationResult.value<QVariantList>().size() == 0) {
            alert(tr("Customer with id=%1 was deleted.").arg(customerID));
            deleted = true;
        } else {
            alert(tr("Customer with id=%1 was not found.").arg(customerID));
        }*/
    } else {
   //     alert(tr("SQL error: %1").arg(sqlda->error().errorMessage()));
    }
    return deleted;
}

void DBService::readRecords(const QString city_id)
{
//    SqlDataAccess *sqlda = new SqlDataAccess(DB_PATH);
    const QString sqlQuery = "SELECT record_id,line_name, start_station,end_station,price,search_time,city_id FROM search_records where city_id=:city_id order by search_time desc limit 10";
    QVariantMap bindings;
    bindings["city_id"] = city_id;
    QVariant result = sqlda->execute(sqlQuery,bindings);
    if (!sqlda->hasError()) {
        int recordsRead = 0;
        m_dataModel->clear();
        if( !result.isNull() ) {
            QVariantList list = result.value<QVariantList>();
            recordsRead = list.size();
            for(int i = 0; i < recordsRead; i++) {
                QVariantMap map = list.at(i).value<QVariantMap>();
                busline *line = new busline;
                line->setCityId(map["city_id"].toString());
                line->setEndStation(map["end_station"].toString());
                line->setSearchTime(map["search_time"].toString());
                line->setStartStation(map["start_station"].toString());
                line->setLineName(map["line_name"].toString());
                line->setPrice(map["price"].toString());
                line->setRecordId(map["record_id"].toString());
                Q_UNUSED(line);
                m_dataModel->append(line);
            }
        }

        qDebug() << "Read " << recordsRead << " records succeeded";

        if (recordsRead == 0) {
      //      alert(QString::fromUtf8("无常用线路信息."));
        }
    } else {
     //   alert(tr("Read records failed: %1").arg(sqlda->error().errorMessage()));
    }
}
QListDataModel<busline*>* DBService::dataModel() const
{
    return m_dataModel;
}
/*void DBService::alert(const QString &message)
{
    SystemDialog *dialog; // SystemDialog uses the BB10 native dialog.
    dialog = new SystemDialog(tr("OK"), 0); // New dialog with on 'Ok' button, no 'Cancel' button
    dialog->setTitle(tr("Alert")); // set a title for the message
    dialog->setBody(message); // set the message itself
    dialog->setDismissAutomatically(true); // Hides the dialog when a button is pressed.
    bool ok = connect(dialog, SIGNAL(finished(bb::system::SystemUiResult::Type)), dialog, SLOT(deleteLater()));
    Q_UNUSED(ok);
    Q_ASSERT(ok);
    dialog->show();
}*/
