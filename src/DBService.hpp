/* Copyright (c) 2012, 2013  BlackBerry Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef DBSERVICE_HPP
#define DBSERVICE_HPP

#include <bb/cascades/QListDataModel>
#include <bb/data/SqlDataAccess>

#include "busline.hpp"

using namespace bb::cascades;
using namespace bb::data;

/*
 * @brief Declaration of our application's class (as opposed to the BB Cascades
 *  application class that contains our application).
 */
class DBService: public QObject
{
    // Classes that inherit from QObject must have the Q_OBJECT macro so
    // the meta-object compiler (MOC) can add supporting code to the application.
    Q_OBJECT

    // A property that is used by the list view in QML
    Q_PROPERTY(bb::cascades::DataModel* dataModel READ dataModel CONSTANT)

public:
    // "Q_INVOKABLE" allows these functions to be called from main.qml
    bool createRecord(const busline* busline);
    void readRecords(const QString city_id);
    bool updateRecord(const int record_id);
    bool deleteRecord(const int record_id);
    int findRecordId(const QString city_id,const QString line_name);
    DBService();
    bb::cascades::QListDataModel<busline*>* dataModel() const;

private:
    // Functions to call upon initialization to setup the model and database
    void initDataModel();
    bool initDatabase();

    // To alert the user if something has gone wrong
    void alert(const QString &message);

    // The getter method for the property

    // The data shown by the list view.
    QListDataModel<busline*>* m_dataModel;
    QString DB_PATH;
    SqlDataAccess *sqlda;
};

#endif
