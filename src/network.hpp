#ifndef Network_BUS_
#define Network_BUS_
#include <QtCore/QObject>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include "busline.hpp"
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


	private:
		QString city_id;
		QString m_buslineText;
		int m_dir;
		busline startLine;
		busline endLine;
		static NetworkBus* m_networkbus;
	//	NetworkBus(){};

	public Q_SLOTS:
		void onBusLineFinished(QNetworkReply* reply);
		void get_lines_by_city(const QString city_id,const QString line_name);
		void changeCity(const QString newCity);
		void changeBusLine(const int m_dir);

//		NetworkBus();
	public:
//		~NetworkBus();
		void reloadData();
		void locateBus();
		static NetworkBus* instance(){
			if(!m_networkbus)
			m_networkbus = new NetworkBus;
			return m_networkbus;
		}
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

		Q_SIGNALS:
			void buslineChanged();

};
const static QString busurl = "http://busi.gpsoo.net/v1/bus/get_lines_by_city?type=handset";

#endif
