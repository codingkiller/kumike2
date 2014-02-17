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
#include "BusGps.hpp"
#include "DBService.hpp"
using namespace bb::cascades;

class NetworkBus : public QObject{
    Q_OBJECT
    Q_PROPERTY(QString error READ error NOTIFY errorChanged)
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
 //   Q_PROPERTY(QString all_station READ all_station NOTIFY buslineChanged)
    Q_PROPERTY(bb::cascades::DataModel* dataModel READ dataModel  NOTIFY dataModelChanged)
//    Q_PROPERTY(bb::cascades::DataModel* gpsDataModel READ gpsDataModel  NOTIFY gpsDataModelChanged)
    Q_PROPERTY(bool process READ isProcess NOTIFY processChanged)
    Q_PROPERTY(bb::cascades::DataModel* localDataModel READ localDataModel  NOTIFY localDataModelChanged)
    Q_PROPERTY(bb::cascades::DataModel* alllineDataModel READ alllineDataModel  NOTIFY alllineDataModelChanged)

	private:
		QString m_city_id;
		QString m_eid;
		int m_isopen;
		QString m_error;
		QString m_all_station;
		int m_dir;
		busline *startLine;
		busline *endLine;
		bool m_process;
		QListDataModel<station*>* m_dataModel;
		QListDataModel<busline*>* m_alllineDataModel;
//		QListDataModel<busline*> m_localDataModel;
//		QListDataModel<BusGps*>* m_gpsDataModel;
	//	GroupDataModel *m_dataModel;
		DBService *dbService;
		QList<station*> *startStation;
		QList<station*> *endStation;
		void get_subline_inf(const QString sid);
		void get_lineisopen();
		void get_online_gps();
	//	void get_all_line(const QString city_id);
		void onError(){
			this->setProcess(false);
			emit processChanged();
			emit errorChanged();
		}
		void init(){
			m_error = "";
			m_all_station = "";
			m_dir = 0;
			m_process = false;
		//	m_city_id = "";
			reloadData();
			m_isopen = 0;
			m_eid = "";
			startLine = new busline;
			endLine = new busline;
			startStation = new QList<station*>;
			endStation = new QList<station*>;
			m_dataModel = new QListDataModel<station*>();
	//		m_gpsDataModel = new QListDataModel<BusGps*>();
		//	m_dataModel = new GroupDataModel(QStringList() << "id" << "name" << "code" << "lat" << "lng");
		//	m_dataModel->setGrouping(ItemGrouping::ByFirstChar);
		//	emit buslineChanged();
		}
		QString getSid(){
			return m_dir == 0 ? startLine->getId() : endLine->getId();
		}
		QString city_id(){
			return m_city_id;
		}
		QListDataModel<busline*>* localDataModel(){
			dbService->readRecords(this->city_id());
			qDebug() << "read records finished" ;
			return dbService->dataModel();
		}
		QListDataModel<busline*> *alllineDataModel(){
			return m_alllineDataModel;
		}


	public Q_SLOTS:
		void onBusLineFinished(QNetworkReply* reply);
		void get_lines_by_city(const QString city_id,const QString line_name);
		void get_all_line(const QString city_id);
		void onSublineInfFinished(QNetworkReply* reply);
		void onLineIsOpenFinished(QNetworkReply* reply);
		void get_online_gps_finished(QNetworkReply* reply);
		void changeCity(const QString newCity);
		void changeBusLine(const int m_dir);
		void deleteRecord(const int record_id);
		void reloadGPSData();
		void onAlllineDataModelFinished(QNetworkReply* reply);
	public:
		void reloadData();
		void locateBus();
		NetworkBus(){
			m_error = "";
						m_all_station = "";
						m_dir = 0;
						m_process = false;
				reloadData();
						//	m_city_id = "";
						m_isopen = 0;
						m_eid = "";
						startLine = new busline;
						endLine = new busline;
						startStation = new QList<station*>;
						endStation = new QList<station*>;
						m_dataModel = new QListDataModel<station*>();
						m_alllineDataModel = new QListDataModel<busline*>;
			dbService = new DBService;
		}
		QString error() const;
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
	//	QString all_station() const;
		QString subline_id() const{
			return m_dir == 0 ? startLine->getId() : endLine->getId();
		}
		QListDataModel<station*> *dataModel() const;
//		QListDataModel<BusGps*> *gpsDataModel() const;

	bool isProcess() const {
		return m_process;
	}

	void setProcess(bool process) {
		m_process = process;
	}


Q_SIGNALS:
			void buslineChanged();
			void stationChanged();
			void processChanged();
			void dataModelChanged();
			void errorChanged();
//			void gpsDataModelChanged();
			void busstateChanged();
			void localDataModelChanged();
			void alllineDataModelChanged();

};
const static QString get_lines_by_city_url = "http://busi.gpsoo.net/v1/bus/get_lines_by_city?type=handset&city_id=";
const static QString subline_inf_url = "http://busi.gpsoo.net/v1/bus/get_subline_inf?mapType=G_NORMAL_MAP&sid=";
const static QString t_lineisopen_url = "http://busi.gpsoo.net/v1/bus/t_lineisopen?code=";
const static QString get_online_gps_url = "http://busi.gpsoo.net/v1/bus/get_online_gps?mapType=BAIDU_MAP&school_id=";
#endif
