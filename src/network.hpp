#ifndef Network_BUS_
#define Network_BUS_
#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <bb/cascades/GroupDataModel>
#include <bb/cascades/QListDataModel>

#include "busline.hpp"
#include "station.hpp"
using namespace bb::cascades;

class NetworkBus : public QObject{
    Q_OBJECT
    Q_PROPERTY(QString buslineText READ buslineText NOTIFY buslineChanged)
    Q_PROPERTY(QString line_name READ line_name NOTIFY buslineChanged)
    Q_PROPERTY(QString begin_time READ begin_time NOTIFY buslineChanged)
    Q_PROPERTY(QString end_time READ end_time NOTIFY buslineChanged)
    Q_PROPERTY(QString start_station READ start_station NOTIFY buslineChanged)
    Q_PROPERTY(QString end_station READ end_station NOTIFY buslineChanged)
    Q_PROPERTY(QString price READ price NOTIFY buslineChanged)
    Q_PROPERTY(int isOpen READ isOpen NOTIFY buslineChanged)
    Q_PROPERTY(int dir READ dir NOTIFY buslineChanged)
    Q_PROPERTY(QString to_station_one READ to_station_one NOTIFY buslineChanged)
    Q_PROPERTY(QString to_station_two READ to_station_two NOTIFY buslineChanged)
    Q_PROPERTY(QString all_station READ all_station NOTIFY buslineChanged)
    Q_PROPERTY(bb::cascades::DataModel* dataModel READ dataModel  NOTIFY buslineChanged)

	private:
		QString city_id;
		QString m_buslineText;
		QString m_all_station;
		int m_dir;
		busline *startLine;
		busline *endLine;
		QListDataModel<station*>* m_dataModel;
	//	GroupDataModel *m_dataModel;
	//	QList<station> *startStation;
	//	QList<station> *endStation;
		void get_subline_inf(const QString sid);
		void init(){
			m_buslineText = "";
			m_all_station = "";
			m_dir = 0;
			city_id = "";
			startLine = new busline;
			endLine = new busline;
		//	startStation = new QList<station>;
		//	endStation = new QList<station>;
			m_dataModel = new QListDataModel<station*>();
		//	m_dataModel = new GroupDataModel(QStringList() << "id" << "name" << "code" << "lat" << "lng");
		//	m_dataModel->setGrouping(ItemGrouping::ByFirstChar);
		//	emit buslineChanged();
		}

	public Q_SLOTS:
		void onBusLineFinished(QNetworkReply* reply);
		void get_lines_by_city(const QString city_id,const QString line_name);
		void onSublineInfFinished(QNetworkReply* reply);
		void changeCity(const QString newCity);
		void changeBusLine(const int m_dir);

	public:
		void reloadData();
		void locateBus();

		QString buslineText() const;
		QString line_name() const;
		QString begin_time() const;
		QString end_time() const;
		QString start_station() const;
		QString end_station() const;
		QString price() const;
		int isOpen() const ;
		int dir() const;
		QString to_station_one() const;
		QString to_station_two() const;
		QString all_station() const;
		QListDataModel<station*> *dataModel() const;
		Q_SIGNALS:
			void buslineChanged();
			void stationChanged();

};
const static QString busurl = "http://busi.gpsoo.net/v1/bus/get_lines_by_city?type=handset";
const static QString subline_inf_url = "http://busi.gpsoo.net/v1/bus/get_subline_inf?mapType=G_NORMAL_MAP&sid=";
#endif
